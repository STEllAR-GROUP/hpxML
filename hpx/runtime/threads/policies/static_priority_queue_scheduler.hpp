//  Copyright (c)      2013 Thomas Heller
//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_THREADMANAGER_SCHEDULING_STATIC_PRIOTITY_QUEUE_HPP)
#define HPX_THREADMANAGER_SCHEDULING_STATIC_PRIOTITY_QUEUE_HPP

#include <hpx/config.hpp>
#include <hpx/runtime/threads/policies/local_priority_queue_scheduler.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace threads { namespace policies
{
    ///////////////////////////////////////////////////////////////////////////
    /// The static_priority_queue_scheduler maintains exactly one queue of work
    /// items (threads) per OS thread, where this OS thread pulls its next work
    /// from. Additionally it maintains separate queues: several for high
    /// priority threads and one for low priority threads.
    /// High priority threads are executed by the first N OS threads before any
    /// other work is executed. Low priority threads are executed by the last
    /// OS thread whenever no other work is available.
    /// This scheduler does not do any work stealing.
    template <typename Mutex, typename Queuing>
    class static_priority_queue_scheduler
        : public local_priority_queue_scheduler<Mutex, Queuing>
    {
    public:
        typedef local_priority_queue_scheduler<Mutex, Queuing> base_type;

        typedef typename base_type::init_parameter_type 
            init_parameter_type;

        static_priority_queue_scheduler(init_parameter_type const& init)
          : base_type(init) 
        {}

        /// Return the next thread to be executed, return false if non is
        /// available
        bool get_next_thread(std::size_t num_thread, bool running,
            boost::int64_t& idle_loop_count, threads::thread_data_base*& thrd)
        {
            std::size_t queues_size = this->queues_.size();

            if (num_thread < this->high_priority_queues_.size())
            {
                bool result = this->high_priority_queues_[num_thread]->
                    get_next_thread(thrd, num_thread);

                this->high_priority_queues_[num_thread]->
                    increment_num_pending_accesses();

                if (!result)
                    this->high_priority_queues_[num_thread]->
                        increment_num_pending_misses();
                else
                    return true;
            }

            {
                HPX_ASSERT(num_thread < queues_size);
                bool result = this->queues_[num_thread]->
                    get_next_thread(thrd, num_thread);

                this->queues_[num_thread]->increment_num_pending_accesses();

                if (!result)
                {
                    this->queues_[num_thread]->increment_num_pending_misses();

                    bool have_staged = (this->queues_[num_thread]->
                        get_task_length(boost::memory_order_relaxed) != 0);

                    // Give up, we should have work to convert.
                    if (have_staged)
                        return false;
                }
                else
                    return true;
            }

            // Limit access to the low priority queue to one worker thread 
            if ((queues_size - 1) == num_thread)
            {
                bool result = this->low_priority_queue_.
                    get_next_thread(thrd, num_thread);
                if (result)
                    return true;
            }

            return false;
        }

        /// This is a function which gets called periodically by the thread
        /// manager to allow for maintenance tasks to be executed in the
        /// scheduler. Returns true if the OS thread calling this function
        /// has to be terminated (i.e. no more work has to be done).
        bool wait_or_add_new(std::size_t num_thread, bool running,
            boost::int64_t& idle_loop_count)
        {
            HPX_ASSERT(num_thread < this->queues_.size());

            std::size_t added = 0;
            bool result = true;

            if (num_thread < this->high_priority_queues_.size())
            {
                result = this->high_priority_queues_[num_thread]->
                    wait_or_add_new(num_thread, running, idle_loop_count,
                        added) && result;
                if (0 != added) return result;
            }

            result = this->queues_[num_thread]->wait_or_add_new(
                num_thread, running, idle_loop_count, added) && result;
            if (0 != added) return result;

#if HPX_THREAD_MINIMAL_DEADLOCK_DETECTION
            // no new work is available, are we deadlocked?
            if (HPX_UNLIKELY(minimal_deadlock_detection && LHPX_ENABLED(error)))
            {
                bool suspended_only = true;

                for (std::size_t i = 0; suspended_only && i != queues_.size(); ++i) {
                    suspended_only = this->queues_[i]->dump_suspended_threads(
                        i, idle_loop_count, running);
                }

                if (HPX_UNLIKELY(suspended_only)) {
                    if (running) {
                        LTM_(error) //-V128
                            << "queue(" << num_thread << "): "
                            << "no new work available, are we deadlocked?";
                    }
                    else {
                        LHPX_CONSOLE_(hpx::util::logging::level::error) << "  [TM] " //-V128
                              << "queue(" << num_thread << "): "
                              << "no new work available, are we deadlocked?\n";
                    }
                }
            }
#endif

            result = this->low_priority_queue_.wait_or_add_new(
                num_thread, running, idle_loop_count, added) && result;
            if (0 != added) return result;

            return result;
        }
    };
}}}

#include <hpx/config/warnings_suffix.hpp>

#endif


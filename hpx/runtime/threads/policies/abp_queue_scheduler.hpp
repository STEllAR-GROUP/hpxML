//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_D7E5D248_4886_4F46_AA1F_36D81397E5D5)
#define HPX_D7E5D248_4886_4F46_AA1F_36D81397E5D5

#include <memory>

#include <hpx/config.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/util/block_profiler.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/runtime/threads/thread_affinity.hpp>
#include <hpx/runtime/threads/policies/thread_deque.hpp>

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/lockfree/fifo.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>
#include <boost/atomic.hpp>

// TODO: add branch prediction and function heat

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace threads { namespace policies
{

struct abp_queue_scheduler : boost::noncopyable
{
    enum { max_thread_count = 1000 };

    // the scheduler type takes two initialization parameters:
    //    the number of queues
    //    the maxcount per queue
    struct init_parameter
    {
        init_parameter()
          : num_queues_(1),
            max_queue_thread_count_(max_thread_count),
            numa_sensitive_(false)
        {}

        init_parameter(std::size_t num_queues,
                std::size_t max_queue_thread_count = max_thread_count,
                bool numa_sensitive = false)
          : num_queues_(num_queues),
            max_queue_thread_count_(max_queue_thread_count),
            numa_sensitive_(numa_sensitive)
        {}

        init_parameter(std::pair<std::size_t, std::size_t> const& init,
                bool numa_sensitive = false)
          : num_queues_(init.first),
            max_queue_thread_count_(init.second),
            numa_sensitive_(numa_sensitive)
        {}

        std::size_t num_queues_;
        std::size_t max_queue_thread_count_;
        bool numa_sensitive_;
    };

    typedef init_parameter init_parameter_type;

    abp_queue_scheduler(init_parameter_type const& init)
      : queues_(init.num_queues_),
        curr_queue_(0),
        numa_sensitive_(init.numa_sensitive_)
    {
        BOOST_ASSERT(init.num_queues_ != 0);
        for (std::size_t i = 0; i < init.num_queues_; ++i)
            queues_[i] = new thread_deque(init.max_queue_thread_count_);
    }

    ~abp_queue_scheduler()
    {
        for (std::size_t i = 0; i < queues_.size(); ++i)
            delete queues_[i];
    }

    bool numa_sensitive() const { return numa_sensitive_; }

    ///////////////////////////////////////////////////////////////////////
    // Queries the current length of the queues (work items and new items).
    boost::int64_t get_queue_length(std::size_t num_thread = std::size_t(-1)) const
    {
        // Return queue length of one specific queue.
        if (std::size_t(-1) != num_thread)
        {
            BOOST_ASSERT(num_thread < queues_.size());
            return queues_[num_thread]->get_queue_length();
        }

        // Cumulative queue lengths of all queues.
        boost::int64_t result = 0;
        for (std::size_t i = 0; i < queues_.size(); ++i)
            result += queues_[i]->get_queue_length();
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    // Queries the current thread count of the queues.
    boost::int64_t get_thread_count(thread_state_enum state = unknown,
        std::size_t num_thread = std::size_t(-1)) const
    {
        // Return thread count of one specific queue.
        if (std::size_t(-1) != num_thread)
        {
            BOOST_ASSERT(num_thread < queues_.size());
            return queues_[num_thread]->get_thread_count(state);
        }

        // Return the cumulative count for all queues.
        boost::int64_t result = 0;
        for (std::size_t i = 0; i < queues_.size(); ++i)
            result += queues_[i]->get_thread_count(state);
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////
    void abort_all_suspended_threads()
    {
        for (std::size_t i = 0; i < queues_.size(); ++i)
            queues_[i]->abort_all_suspended_threads(i);
    }

    ///////////////////////////////////////////////////////////////////////////
    bool cleanup_terminated()
    {
        bool empty = true;
        for (std::size_t i = 0; i < queues_.size(); ++i)
            empty = queues_[i]->cleanup_terminated() && empty;
        return empty;
    }

    ///////////////////////////////////////////////////////////////////////////
    // create a new thread and schedule it if the initial state is equal to
    // pending
    thread_id_type create_thread(thread_init_data& data,
                                 thread_state_enum initial_state,
                                 bool run_now, error_code& ec,
                                 std::size_t num_thread)
    {
        if (std::size_t(-1) != num_thread) {
            BOOST_ASSERT(num_thread < queues_.size());
            return queues_[num_thread]->create_thread(data, initial_state,
                run_now, ec);
        }

        // TODO: load balancing
        return queues_[++curr_queue_ % queues_.size()]->create_thread(
            data, initial_state, run_now, ec);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Return the next thread to be executed, return false if none is available
    // TODO: shouldn't we try to fill the queue before stealing?
    bool get_next_thread(std::size_t num_thread, bool running,
                         std::size_t& idle_loop_count, threads::thread** thrd)
    {
        // first try to get the next thread from our own queue
        BOOST_ASSERT(num_thread < queues_.size());
        if (queues_[num_thread]->get_next_thread(thrd))
            return true;

        // FIXME: steal from NUMA neighbors first
        // steal thread from other queue
        for (std::size_t i = 1; i < queues_.size(); ++i) {
            std::size_t idx = (i + num_thread) % queues_.size();
            if (queues_[idx]->steal_next_thread(thrd))
                return true;
        }
        return false;
    }

    /// Schedule the passed thread
    void schedule_thread(threads::thread* thrd, std::size_t num_thread,
        thread_priority /*priority*/ = thread_priority_normal)
    {
        if (std::size_t(-1) != num_thread) {
            BOOST_ASSERT(num_thread < queues_.size());
            queues_[num_thread]->schedule_thread(thrd);
        }
        else {
            queues_[++curr_queue_ % queues_.size()]->schedule_thread(thrd);
        }
    }

    /// Destroy the passed thread as it has been terminated
    bool destroy_thread(threads::thread* thrd)
    {
        for (std::size_t i = 0; i < queues_.size(); ++i) {
            if (queues_[i]->destroy_thread(thrd))
                return true;
        }
        return false;
    }

    // Note that this is more like terminate_or_add_new
    bool wait_or_add_new(std::size_t num_thread, bool running,
                         std::size_t& idle_loop_count)
    {
        BOOST_ASSERT(num_thread < queues_.size());

        std::size_t added = 0;
        bool result = queues_[num_thread]->add_new_or_terminate(
            num_thread, running, added);

        if (!result) {
            // steal work items: first try to steal from other cores in the same numa node
            std::size_t core_mask = get_thread_affinity_mask(num_thread, numa_sensitive_);
            std::size_t node_mask = get_numa_node_affinity_mask(num_thread, numa_sensitive_);

            if (core_mask != std::size_t(-1) && node_mask != std::size_t(-1)) {
                std::size_t m = 0x01LL;
                for (std::size_t i = 1; (0 == added) && i < queues_.size();
                     m <<= 1, ++i)
                {
                    if (m == core_mask || !(m & node_mask))
                        continue;         // don't steal from ourselves

                    std::size_t idx = least_significant_bit_set(m);
                    BOOST_ASSERT(idx < queues_.size());

                    queues_[num_thread]->steal_new_or_terminate(
                        idx, running, added, queues_[idx]);
                }
            }

            // if nothing found ask everybody else
            for (std::size_t i = 1; 0 == added && i < queues_.size(); ++i) {
                std::size_t idx = (i + num_thread) % queues_.size();
                queues_[num_thread]->steal_new_or_terminate(
                    idx, running, added, queues_[idx]);
            }

            // no new work is available, are we deadlocked?
            if (0 == added && 0 == num_thread && LHPX_ENABLED(error)) {
                bool suspended_only = true;

                for (std::size_t i = 0; suspended_only && i < queues_.size(); ++i) {
                    suspended_only = queues_[i]->dump_suspended_threads(
                        i, idle_loop_count, running);
                }

                if (HPX_UNLIKELY(suspended_only)) {
                    if (running) {
                        LTM_(error)
                            << "queue(" << num_thread << "): "
                            << "no new work available, are we deadlocked?";
                    }
                    else {
                        LHPX_CONSOLE_(boost::logging::level::error) << "  [TM] "
                              << "queue(" << num_thread << "): "
                              << "no new work available, are we deadlocked?\n";
                    }
                }
            }
        }
        return result;
    }

    // no-op for local scheduling
    void do_some_work(std::size_t num_thread) { }

    ///////////////////////////////////////////////////////////////////////
    void on_start_thread(std::size_t num_thread)
    {
        queues_[num_thread]->on_start_thread(num_thread);
    }
    void on_stop_thread(std::size_t num_thread)
    {
        queues_[num_thread]->on_stop_thread(num_thread);
    }
    void on_error(std::size_t num_thread, boost::exception_ptr const& e)
    {
        queues_[num_thread]->on_error(num_thread, e);
    }

private:
    std::vector<thread_deque*> queues_; ///< this manages all the PX threads
    boost::atomic<std::size_t> curr_queue_;
    bool numa_sensitive_;
};

}}}

#endif // HPX_D7E5D248_4886_4F46_AA1F_36D81397E5D5


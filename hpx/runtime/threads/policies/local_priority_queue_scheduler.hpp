//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_THREADMANAGER_SCHEDULING_LOCAL_PRIOTITY_QUEUE_MAR_15_2011_0926AM)
#define HPX_THREADMANAGER_SCHEDULING_LOCAL_PRIOTITY_QUEUE_MAR_15_2011_0926AM

#include <vector>
#include <memory>

#include <hpx/config.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/runtime/threads/thread_data.hpp>
#include <hpx/runtime/threads/topology.hpp>
#include <hpx/runtime/threads/policies/thread_queue.hpp>
#include <hpx/runtime/threads/policies/affinity_data.hpp>
#include <hpx/runtime/threads/policies/scheduler_base.hpp>

#include <boost/noncopyable.hpp>
#include <boost/atomic.hpp>
#include <boost/mpl/bool.hpp>

#include <hpx/config/warnings_prefix.hpp>

// TODO: add branch prediction and function heat

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace threads { namespace policies
{
#if HPX_THREAD_MINIMAL_DEADLOCK_DETECTION
    ///////////////////////////////////////////////////////////////////////////
    // We globally control whether to do minimal deadlock detection using this
    // global bool variable. It will be set once by the runtime configuration
    // startup code
    extern bool minimal_deadlock_detection;
#endif

    ///////////////////////////////////////////////////////////////////////////
    /// The local_priority_queue_scheduler maintains exactly one queue of work
    /// items (threads) per OS thread, where this OS thread pulls its next work
    /// from. Additionally it maintains separate queues: several for high
    /// priority threads and one for low priority threads.
    /// High priority threads are executed by the first N OS threads before any
    /// other work is executed. Low priority threads are executed by the last
    /// OS thread whenever no other work is available.
    template <typename Mutex>
    class local_priority_queue_scheduler : public scheduler_base
    {
    private:
        // The maximum number of active threads this thread manager should
        // create. This number will be a constraint only as long as the work
        // items queue is not empty. Otherwise the number of active threads
        // will be incremented in steps equal to the \a min_add_new_count
        // specified above.
        enum { max_thread_count = 1000 };

    public:
        typedef boost::mpl::false_ has_periodic_maintenance;

        // the scheduler type takes two initialization parameters:
        //    the number of queues
        //    the number of high priority queues
        //    the maxcount per queue
        struct init_parameter
        {
            init_parameter()
              : num_queues_(1),
                max_queue_thread_count_(max_thread_count),
                numa_sensitive_(false)
            {}

            init_parameter(std::size_t num_queues,
                    std::size_t num_high_priority_queues = std::size_t(-1),
                    std::size_t max_queue_thread_count = max_thread_count,
                    bool numa_sensitive = false)
              : num_queues_(num_queues),
                num_high_priority_queues_(
                    num_high_priority_queues == std::size_t(-1) ?
                        num_queues : num_high_priority_queues),
                max_queue_thread_count_(max_queue_thread_count),
                numa_sensitive_(numa_sensitive)
            {}

            std::size_t num_queues_;
            std::size_t num_high_priority_queues_;
            std::size_t max_queue_thread_count_;
            bool numa_sensitive_;
        };
        typedef init_parameter init_parameter_type;

        local_priority_queue_scheduler(init_parameter_type const& init)
          : queues_(init.num_queues_),
            high_priority_queues_(init.num_high_priority_queues_),
            low_priority_queue_(init.max_queue_thread_count_),
            curr_queue_(0),
            affinity_data_(init.num_queues_),
            numa_sensitive_(init.numa_sensitive_),
            topology_(get_topology()),
#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
            steals_in_numa_domain_(init.num_queues_),
            steals_outside_numa_domain_(init.num_queues_),
#endif
#if !defined(HPX_HAVE_MORE_THAN_64_THREADS) || defined(HPX_MAX_CPU_COUNT)
            numa_domain_masks_(init.num_queues_),
            outside_numa_domain_masks_(init.num_queues_)
#else
            numa_domain_masks_(init.num_queues_, topology_.get_machine_affinity_mask()),
            outside_numa_domain_masks_(init.num_queues_, topology_.get_machine_affinity_mask())
#endif
        {
            HPX_ASSERT(init.num_queues_ != 0);
            for (std::size_t i = 0; i < init.num_queues_; ++i)
                queues_[i] = new thread_queue<Mutex>(init.max_queue_thread_count_);

            HPX_ASSERT(init.num_high_priority_queues_ != 0);
            HPX_ASSERT(init.num_high_priority_queues_ <= init.num_queues_);
            for (std::size_t i = 0; i < init.num_high_priority_queues_; ++i) {
                high_priority_queues_[i] =
                    new thread_queue<Mutex>(init.max_queue_thread_count_);
            }
        }

        ~local_priority_queue_scheduler()
        {
            for (std::size_t i = 0; i < queues_.size(); ++i)
                delete queues_[i];
            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                delete high_priority_queues_[i];
        }

        std::size_t init(init_affinity_data const& data, topology const& topology)
        {
            return affinity_data_.init(data, topology);
        }

        bool numa_sensitive() const { return numa_sensitive_; }

        threads::mask_cref_type get_pu_mask(topology const& topology,
            std::size_t num_thread) const
        {
            return affinity_data_.get_pu_mask(topology, num_thread, numa_sensitive_);
        }

        std::size_t get_pu_num(std::size_t num_thread) const
        {
            return affinity_data_.get_pu_num(num_thread);
        }

        std::size_t get_num_stolen_threads(std::size_t num_thread, bool reset)
        {
            std::size_t num_stolen_threads = 0;
            if (num_thread == std::size_t(-1))
            {
                for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                    num_stolen_threads +=
                        high_priority_queues_[i]->get_num_stolen_threads(reset);

                num_stolen_threads += low_priority_queue_.get_num_stolen_threads(reset);

                for (std::size_t i = 0; i < queues_.size(); ++i)
                    num_stolen_threads += queues_[i]->get_num_stolen_threads(reset);
                return num_stolen_threads;
            }

            if (num_thread < high_priority_queues_.size())
                num_stolen_threads =
                    high_priority_queues_[num_thread]->get_num_stolen_threads(reset);

            if (num_thread == queues_.size()-1)
                num_stolen_threads += low_priority_queue_.get_num_stolen_threads(reset);

            num_stolen_threads += queues_[num_thread]->get_num_stolen_threads(reset);
            return num_stolen_threads;
        }

        ///////////////////////////////////////////////////////////////////////
        void abort_all_suspended_threads()
        {
            for (std::size_t i = 0; i < queues_.size(); ++i)
                queues_[i]->abort_all_suspended_threads(i);

            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i) {
                std::size_t queue_num = queues_.size() + i;
                high_priority_queues_[i]->abort_all_suspended_threads(queue_num);
            }

            low_priority_queue_.abort_all_suspended_threads(
                queues_.size()+high_priority_queues_.size());
        }

        ///////////////////////////////////////////////////////////////////////
        bool cleanup_terminated(bool delete_all = false)
        {
            bool empty = true;
            for (std::size_t i = 0; i < queues_.size(); ++i)
                empty = queues_[i]->cleanup_terminated(delete_all) && empty;
            if (!delete_all)
                return empty;

            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                empty = high_priority_queues_[i]->cleanup_terminated(delete_all) && empty;

            empty = low_priority_queue_.cleanup_terminated(delete_all) && empty;
            return empty;
        }

        ///////////////////////////////////////////////////////////////////////
        // create a new thread and schedule it if the initial state is equal to
        // pending
        thread_id_type create_thread(thread_init_data& data,
            thread_state_enum initial_state, bool run_now, error_code& ec,
            std::size_t num_thread)
        {
#if HPX_THREAD_MAINTAIN_TARGET_ADDRESS
            // try to figure out the NUMA node where the data lives
            if (numa_sensitive_ && std::size_t(-1) == num_thread) {
                mask_cref_type mask =
                    topology_.get_thread_affinity_mask_from_lva(data.lva);
                if (any(mask)) {
                    num_thread = find_first(mask);
                }
            }
#endif
            std::size_t queue_size = queues_.size();

            if (std::size_t(-1) == num_thread)
                num_thread = ++curr_queue_ % queue_size;

            if (num_thread >= queue_size)
                num_thread %= queue_size;

            // now create the thread
            if (data.priority == thread_priority_critical) {
                std::size_t num = num_thread % high_priority_queues_.size();
                return high_priority_queues_[num]->create_thread(data,
                    initial_state, run_now, queue_size + num, ec);
            }
            else if (data.priority == thread_priority_low) {
                return low_priority_queue_.create_thread(data, initial_state,
                    run_now, queue_size + high_priority_queues_.size(), ec);
            }

            HPX_ASSERT(num_thread < queue_size);
            return queues_[num_thread]->create_thread(data, initial_state,
                run_now, num_thread, ec);
        }

        /// Return the next thread to be executed, return false if none is
        /// available
        bool get_next_thread(std::size_t num_thread, bool running,
            boost::int64_t& idle_loop_count, threads::thread_data_base*& thrd)
        {
            // master thread only: first try to get a priority thread
            std::size_t high_priority_queue_size = high_priority_queues_.size();
            std::size_t queue_size = queues_.size();
            if (num_thread < high_priority_queue_size)
            {
                bool result = high_priority_queues_[num_thread]->
                    get_next_thread(thrd, queue_size + num_thread);
                if (result)
                    return true;
            }

            // try to get the next thread from our own queue
            HPX_ASSERT(num_thread < queue_size);
            if (queues_[num_thread]->get_next_thread(thrd, num_thread))
                return true;

            // try to execute low priority work if no other work is available
            if (queue_size-1 == num_thread)
            {
                bool result = low_priority_queue_.get_next_thread(
                    thrd, queue_size + high_priority_queue_size);
                if (result)
                    return true;
            }

            // steal thread from other queue, first try high priority queues,
            // then normal ones

            mask_cref_type this_numa_domain = numa_domain_masks_[num_thread];
            mask_cref_type numa_domain = outside_numa_domain_masks_[num_thread];
            for (std::size_t i = 0; i < high_priority_queue_size; ++i)
            {
                if (i == num_thread)
                    continue;         // don't steal from ourselves
                if (!test(this_numa_domain, i) && !test(numa_domain, i))
                    continue;

                if (high_priority_queues_[i]->get_next_thread(thrd, queue_size + i))
                {
                    high_priority_queues_[i]->increment_num_stolen_threads();
                    return true;
                }
            }

            // steal thread from other queue
            for (std::size_t i = 0; i < queue_size; ++i) {
                if (i == num_thread)
                    continue;         // don't steal from ourselves
                if (!test(this_numa_domain, i) && !test(numa_domain, i))
                    continue;

                if (queues_[i]->get_next_thread(thrd, num_thread))
                {
                    queues_[i]->increment_num_stolen_threads();
                    return true;
                }
            }
            return false;
        }

        /// Schedule the passed thread
        void schedule_thread(threads::thread_data_base* thrd, std::size_t num_thread,
            thread_priority priority = thread_priority_normal)
        {
            if (std::size_t(-1) == num_thread)
                num_thread = ++curr_queue_ % queues_.size();

            if (priority == thread_priority_critical) {
                std::size_t num = num_thread % high_priority_queues_.size();
                high_priority_queues_[num]->schedule_thread(
                    thrd, queues_.size()+num);
            }
            else if (priority == thread_priority_low) {
                low_priority_queue_.schedule_thread(thrd,
                    queues_.size()+high_priority_queues_.size());
            }
            else {
                HPX_ASSERT(num_thread < queues_.size());
                queues_[num_thread]->schedule_thread(thrd, num_thread);
            }
        }

        void schedule_thread_last(threads::thread_data_base* thrd, std::size_t num_thread,
            thread_priority priority = thread_priority_normal)
        {
            local_priority_queue_scheduler::schedule_thread(thrd, num_thread, priority);
        }

        /// Destroy the passed thread as it has been terminated
        bool destroy_thread(threads::thread_data_base* thrd, boost::int64_t& busy_count)
        {
            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
            {
                if (high_priority_queues_[i]->destroy_thread(thrd, busy_count))
                    return true;
            }

            for (std::size_t i = 0; i < queues_.size(); ++i)
            {
                if (queues_[i]->destroy_thread(thrd, busy_count))
                    return true;
            }

            if (low_priority_queue_.destroy_thread(thrd, busy_count))
                return true;

            // the thread has to belong to one of the queues, always
            HPX_ASSERT(false);

            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        // This returns the current length of the queues (work items and new items)
        boost::int64_t get_queue_length(std::size_t num_thread = std::size_t(-1)) const
        {
            // Return queue length of one specific queue.
            boost::int64_t count = 0;
            if (std::size_t(-1) != num_thread) {
                HPX_ASSERT(num_thread < queues_.size());

                if (num_thread < high_priority_queues_.size())
                    count = high_priority_queues_[num_thread]->get_queue_length();

                if (num_thread == queues_.size()-1)
                    count += low_priority_queue_.get_queue_length();

                return count + queues_[num_thread]->get_queue_length();
            }

            // Cumulative queue lengths of all queues.
            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                count += high_priority_queues_[i]->get_queue_length();

            count += low_priority_queue_.get_queue_length();

            for (std::size_t i = 0; i < queues_.size(); ++i)
                count += queues_[i]->get_queue_length();

            return count;
        }

        ///////////////////////////////////////////////////////////////////////
        // Queries the current thread count of the queues.
        boost::int64_t get_thread_count(thread_state_enum state = unknown,
            thread_priority priority = thread_priority_default,
            std::size_t num_thread = std::size_t(-1), bool reset = false) const
        {
            // Return thread count of one specific queue.
            boost::int64_t count = 0;
            if (std::size_t(-1) != num_thread)
            {
                HPX_ASSERT(num_thread < queues_.size());

                switch (priority) {
                case thread_priority_default:
                    {
                        if (num_thread < high_priority_queues_.size())
                            count = high_priority_queues_[num_thread]->get_thread_count(state);

                        if (queues_.size()-1 == num_thread)
                            count += low_priority_queue_.get_thread_count(state);

                        return count + queues_[num_thread]->get_thread_count(state);
                    }

                case thread_priority_low:
                    {
                        if (queues_.size()-1 == num_thread)
                            return low_priority_queue_.get_thread_count(state);
                        break;
                    }

                case thread_priority_normal:
                    return queues_[num_thread]->get_thread_count(state);

                case thread_priority_critical:
                    {
                        if (num_thread < high_priority_queues_.size())
                            return high_priority_queues_[num_thread]->get_thread_count(state);
                        break;
                    }

                default:
                case thread_priority_unknown:
                    {
                        HPX_THROW_EXCEPTION(bad_parameter,
                            "local_priority_queue_scheduler::get_thread_count",
                            "unknown thread priority value (thread_priority_unknown)");
                        return 0;
                    }
                }
                return 0;
            }

            // Return the cumulative count for all queues.
            switch (priority) {
            case thread_priority_default:
                {
                    for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                        count += high_priority_queues_[i]->get_thread_count(state);

                    count += low_priority_queue_.get_thread_count(state);

                    for (std::size_t i = 0; i < queues_.size(); ++i)
                        count += queues_[i]->get_thread_count(state);
                }

            case thread_priority_low:
                return low_priority_queue_.get_thread_count(state);

            case thread_priority_normal:
                {
                    for (std::size_t i = 0; i < queues_.size(); ++i)
                        count += queues_[i]->get_thread_count(state);
                    break;
                }

            case thread_priority_critical:
                {
                    for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
                        count += high_priority_queues_[i]->get_thread_count(state);
                    break;
                }

            default:
            case thread_priority_unknown:
                {
                    HPX_THROW_EXCEPTION(bad_parameter,
                        "local_priority_queue_scheduler::get_thread_count",
                        "unknown thread priority value (thread_priority_unknown)");
                    return 0;
                }
            }
            return count;
        }

#if HPX_THREAD_MAINTAIN_QUEUE_WAITTIME
        ///////////////////////////////////////////////////////////////////////
        // Queries the current average thread wait time of the queues.
        boost::int64_t get_average_thread_wait_time(
            std::size_t num_thread = std::size_t(-1)) const
        {
            // Return average thread wait time of one specific queue.
            boost::uint64_t wait_time = 0;
            boost::uint64_t count = 0;
            if (std::size_t(-1) != num_thread)
            {
                HPX_ASSERT(num_thread < queues_.size());

                if (num_thread < high_priority_queues_.size())
                {
                    wait_time = high_priority_queues_[num_thread]->
                        get_average_thread_wait_time();
                    ++count;
                }

                if (queues_.size()-1 == num_thread)
                {
                    wait_time += low_priority_queue_.
                        get_average_thread_wait_time();
                    ++count;
                }

                wait_time += queues_[num_thread]->get_average_thread_wait_time();
                return wait_time / (count + 1);
            }

            // Return the cumulative average thread wait time for all queues.
            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
            {
                wait_time += high_priority_queues_[i]->get_average_thread_wait_time();
                ++count;
            }

            wait_time += low_priority_queue_.get_average_thread_wait_time();

            for (std::size_t i = 0; i < queues_.size(); ++i)
            {
                wait_time += queues_[i]->get_average_thread_wait_time();
                ++count;
            }

            return wait_time / (count + 1);
        }

        ///////////////////////////////////////////////////////////////////////
        // Queries the current average task wait time of the queues.
        boost::int64_t get_average_task_wait_time(
            std::size_t num_thread = std::size_t(-1)) const
        {
            // Return average task wait time of one specific queue.
            boost::uint64_t wait_time = 0;
            boost::uint64_t count = 0;
            if (std::size_t(-1) != num_thread)
            {
                HPX_ASSERT(num_thread < queues_.size());

                if (num_thread < high_priority_queues_.size())
                {
                    wait_time = high_priority_queues_[num_thread]->
                        get_average_task_wait_time();
                    ++count;
                }

                if (queues_.size()-1 == num_thread)
                {
                    wait_time += low_priority_queue_.
                        get_average_task_wait_time();
                    ++count;
                }

                wait_time += queues_[num_thread]->get_average_task_wait_time();
                return wait_time / (count + 1);
            }

            // Return the cumulative average task wait time for all queues.
            for (std::size_t i = 0; i < high_priority_queues_.size(); ++i)
            {
                wait_time += high_priority_queues_[i]->
                    get_average_task_wait_time();
                ++count;
            }

            wait_time += low_priority_queue_.get_average_task_wait_time();

            for (std::size_t i = 0; i < queues_.size(); ++i)
            {
                wait_time += queues_[i]->get_average_task_wait_time();
                ++count;
            }

            return wait_time / (count + 1);
        }
#endif

        /// This is a function which gets called periodically by the thread
        /// manager to allow for maintenance tasks to be executed in the
        /// scheduler. Returns true if the OS thread calling this function
        /// has to be terminated (i.e. no more work has to be done).
        bool wait_or_add_new(std::size_t num_thread, bool running,
            boost::int64_t& idle_loop_count)
        {
            std::size_t queues_size = queues_.size();
            HPX_ASSERT(num_thread < queues_.size());

            std::size_t added = 0;
            bool result = true;

            if (num_thread < high_priority_queues_.size()) {
                // Convert high priority tasks to threads before attempting to
                // steal from other OS thread.
                result = high_priority_queues_[num_thread]->
                    wait_or_add_new(queues_size + num_thread, running,
                        idle_loop_count, added);
                if (0 != added) return result;
            }

            result = queues_[num_thread]->wait_or_add_new(
                num_thread, running, idle_loop_count, added) && result;
            if (0 != added) return result;

            if (queues_size-1 == num_thread) {
                // Convert low priority tasks to threads before attempting to
                // steal from other OS thread.
                result = low_priority_queue_.wait_or_add_new(
                    num_thread, running, idle_loop_count, added) && result;
                if (0 != added) return result;
            }

            // steal work items: first try to steal from other cores in
            // the same NUMA node
#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
            if (test(steals_in_numa_domain_, num_thread))
#endif
            {
                mask_cref_type numa_domain_mask =
                    numa_domain_masks_[num_thread];
                for (std::size_t i = 0; i != queues_size; ++i)
                {
                    // don't steal from ourselves, and only if we're allowed
                    // to steal inside this domain
                    if (i == num_thread ||
                        !test(numa_domain_mask, topology_.get_pu_number(i)))
                    {
                        continue;
                    }

                    result = queues_[num_thread]->wait_or_add_new(i,
                        running, idle_loop_count, added, queues_[i]) && result;
                    if (0 != added)
                    {
                        queues_[num_thread]->increment_num_stolen_threads(added);
                        return result;
                    }
                }
            }

#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
            // if nothing found, ask everybody else
            if (test(steals_outside_numa_domain_, num_thread))
            {
                mask_cref_type numa_domain_mask =
                    outside_numa_domain_masks_[num_thread];
                for (std::size_t i = 0; i != queues_size; ++i)
                {
                    // don't steal from ourselves, and only if we're allowed
                    // to steal from another domain
                    if (i == num_thread ||
                        !test(numa_domain_mask, topology_.get_pu_number(i)))
                    {
                        continue;
                    }

                    result = queues_[num_thread]->wait_or_add_new(i, running,
                        idle_loop_count, added, queues_[i]) && result;
                    if (0 != added)
                    {
                        queues_[num_thread]->increment_num_stolen_threads(added);
                        return result;
                    }
                }
            }
#endif

#if HPX_THREAD_MINIMAL_DEADLOCK_DETECTION
            // no new work is available, are we deadlocked?
            if (HPX_UNLIKELY(minimal_deadlock_detection && LHPX_ENABLED(error)))
            {
                bool suspended_only = true;

                for (std::size_t i = 0; suspended_only && i != queues_.size(); ++i) {
                    suspended_only = queues_[i]->dump_suspended_threads(
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
            return result;
        }

        ///////////////////////////////////////////////////////////////////////
        // no-op for local scheduling
        void do_some_work(std::size_t num_thread = std::size_t(-1)) {}

        ///////////////////////////////////////////////////////////////////////
        void add_punit(std::size_t virt_core, std::size_t thread_num)
        {
            affinity_data_.add_punit(virt_core, thread_num, topology_);
        }

        ///////////////////////////////////////////////////////////////////////
        void on_start_thread(std::size_t num_thread)
        {
            // forward this call to all queues etc.
            if (num_thread < high_priority_queues_.size())
                high_priority_queues_[num_thread]->on_start_thread(num_thread);
            if (num_thread == queues_.size()-1)
                low_priority_queue_.on_start_thread(num_thread);

            queues_[num_thread]->on_start_thread(num_thread);

            // pre-calculate certain constants for the given thread number
            std::size_t num_pu = get_pu_num(num_thread);
            mask_cref_type machine_mask = topology_.get_machine_affinity_mask();
            mask_cref_type core_mask =
                topology_.get_thread_affinity_mask(num_pu, numa_sensitive_);
            mask_cref_type node_mask =
                topology_.get_numa_node_affinity_mask(num_pu, numa_sensitive_);

            if (any(core_mask) && any(node_mask)) {
#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
                set(steals_in_numa_domain_, num_thread);
#endif
                numa_domain_masks_[num_thread] = node_mask;
            }

            // we allow the thread on the boundary of the NUMA domain to steal
            mask_type first_mask = mask_type();
            resize(first_mask, mask_size(core_mask));

            std::size_t first = find_first(node_mask);
            if (first != std::size_t(-1))
                set(first_mask, first);
            else
                first_mask = core_mask;

            if (any(first_mask & core_mask)) {
#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
                set(steals_outside_numa_domain_, num_thread);
#endif
                outside_numa_domain_masks_[num_thread] = not_(node_mask) & machine_mask;
            }
        }

        void on_stop_thread(std::size_t num_thread)
        {
            if (num_thread < high_priority_queues_.size())
                high_priority_queues_[num_thread]->on_stop_thread(num_thread);
            if (num_thread == queues_.size()-1)
                low_priority_queue_.on_stop_thread(num_thread);

            queues_[num_thread]->on_stop_thread(num_thread);
        }

        void on_error(std::size_t num_thread, boost::exception_ptr const& e)
        {
            if (num_thread < high_priority_queues_.size())
                high_priority_queues_[num_thread]->on_error(num_thread, e);
            if (num_thread == queues_.size()-1)
                low_priority_queue_.on_error(num_thread, e);

            queues_[num_thread]->on_error(num_thread, e);
        }

    private:
        std::vector<thread_queue<Mutex>*> queues_;   ///< this manages all the PX threads
        std::vector<thread_queue<Mutex>*> high_priority_queues_;
        thread_queue<Mutex> low_priority_queue_;
        boost::atomic<std::size_t> curr_queue_;
        detail::affinity_data affinity_data_;
        bool numa_sensitive_;
        topology const& topology_;

#if !defined(HPX_NATIVE_MIC)        // we know that the MIC has one NUMA domain only
        mask_type steals_in_numa_domain_;
        mask_type steals_outside_numa_domain_;
#endif
        std::vector<mask_type> numa_domain_masks_;
        std::vector<mask_type> outside_numa_domain_masks_;
    };
}}}

#include <hpx/config/warnings_suffix.hpp>

#endif


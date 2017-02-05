//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_RUNTIME_THREADS_FWD_HPP
#define HPX_RUNTIME_THREADS_FWD_HPP

#include <hpx/config.hpp>
#include <hpx/runtime/threads/thread_data_fwd.hpp>
#include <hpx/runtime/threads/thread_enums.hpp>
#include <hpx/util/unique_function.hpp>

#include <boost/thread/mutex.hpp>

namespace hpx
{
    /// \namespace threads
    ///
    /// The namespace \a thread-manager contains all the definitions required
    /// for the scheduling, execution and general management of \a
    /// hpx#threadmanager#thread's.
    namespace threads
    {
        namespace policies
        {
            struct scheduler_base;

            struct lockfree_fifo;
            struct lockfree_lifo;

            // multi priority scheduler with work-stealing
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT local_priority_queue_scheduler;

            // single priority scheduler with work-stealing
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT local_queue_scheduler;

#if defined(HPX_HAVE_PERIODIC_PRIORITY_SCHEDULER)
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT periodic_priority_queue_scheduler;
#endif

#if defined(HPX_HAVE_STATIC_PRIORITY_SCHEDULER)
            // multi priority scheduler with no work-stealing
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT static_priority_queue_scheduler;
#endif

#if defined(HPX_HAVE_STATIC_SCHEDULER)
            // single priority scheduler with no work-stealing
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT static_queue_scheduler;
#endif

#if defined(HPX_HAVE_THROTTLE_SCHEDULER) && defined(HPX_HAVE_APEX)
            // single priority scheduler with work-stealing and throttling
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT throttle_queue_scheduler;
#endif

#if defined(HPX_HAVE_HIERARCHY_SCHEDULER)
            template <typename Mutex = boost::mutex
                    , typename PendingQueuing = lockfree_fifo
                    , typename StagedQueuing = lockfree_fifo
                    , typename TerminatedQueuing = lockfree_lifo
                     >
            class HPX_EXPORT hierarchy_scheduler;
#endif

            class HPX_EXPORT callback_notifier;
        }

        namespace executors
        {
            struct HPX_EXPORT current_executor;
        }
    }
}

#endif

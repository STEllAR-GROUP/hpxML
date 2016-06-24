//  Copyright (c) 2007-2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/executors/thread_executor_traits.hpp

#if !defined(HPX_PARALLEL_THREAD_EXECUTOR_TRAITS_AUG_07_2015_0826AM)
#define HPX_PARALLEL_THREAD_EXECUTOR_TRAITS_AUG_07_2015_0826AM

#include <hpx/config.hpp>
#include <hpx/apply.hpp>
#include <hpx/async.hpp>
#include <hpx/parallel/config/inline_namespace.hpp>
#include <hpx/parallel/executors/executor_traits.hpp>
#include <hpx/runtime/threads/thread_executor.hpp>
#include <hpx/traits/is_launch_policy.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/deferred_call.hpp>
#include <hpx/util/unwrapped.hpp>

#include <type_traits>
#include <utility>
#include <vector>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v3)
{
    ///////////////////////////////////////////////////////////////////////////
    /// Specialization for executor_traits for types which conform to
    /// traits::is_threads_executor<Executor>
    template <typename Executor>
    struct executor_traits<Executor,
        typename std::enable_if<
            hpx::traits::is_threads_executor<Executor>::value
        >::type>
    {
        /// The type of the executor associated with this instance of
        /// \a executor_traits
        typedef Executor executor_type;

        /// The category of agents created by the bulk-form execute() and
        /// async_execute(). All threads::executors create parallel execution
        /// agents
        ///
        typedef parallel_execution_tag execution_category;

        /// The type of future returned by async_execute(). All
        /// threads::executors return hpx::future<T>.
        ///
        template <typename T>
        struct future
        {
            typedef hpx::future<T> type;
        };

        /// \brief Singleton form of asynchronous fire & forget execution agent
        ///        creation.
        ///
        /// This asynchronously (fire & forget) creates a single function
        /// invocation f() using the associated executor. All
        /// threads::executors invoke hpx::apply(sched, f).
        ///
        /// \param sched [in] The executor object to use for scheduling of the
        ///             function \a f.
        /// \param f    [in] The function which will be scheduled using the
        ///             given executor.
        /// \param ts... [in] Additional arguments to use to invoke \a f.
        ///
        template <typename F, typename ... Ts>
        static void apply_execute(executor_type& sched, F && f, Ts &&... ts)
        {
            hpx::apply(sched, std::forward<F>(f), std::forward<Ts>(ts)...);
        }

        /// \brief Singleton form of asynchronous execution agent creation.
        ///
        /// This asynchronously creates a single function invocation f() using
        /// the associated executor. All threads::executors invoke
        /// hpx::async(sched, f).
        ///
        /// \param sched [in] The executor object to use for scheduling of the
        ///             function \a f.
        /// \param f    [in] The function which will be scheduled using the
        ///             given executor.
        /// \param ts... [in] Additional arguments to use to invoke \a f.
        ///
        /// \returns f(ts...)'s result through a future
        ///
        template <typename F, typename ... Ts>
        static hpx::future<
            typename hpx::util::detail::deferred_result_of<F(Ts&&...)>::type
        >
        async_execute(executor_type& sched, F && f, Ts &&... ts)
        {
            return hpx::async(sched, std::forward<F>(f),
                std::forward<Ts>(ts)...);
        }

        /// \brief Singleton form of synchronous execution agent creation.
        ///
        /// This synchronously creates a single function invocation f() using
        /// the associated executor. The execution of the supplied function
        /// synchronizes with the caller. All threads::executors invoke
        /// hpx::async(sched, f).get().
        ///
        /// \param sched [in] The executor object to use for scheduling of the
        ///             function \a f.
        /// \param f    [in] The function which will be scheduled using the
        ///             given executor.
        /// \param ts... [in] Additional arguments to use to invoke \a f.
        ///
        /// \returns f(ts...)'s result through a future
        ///
        template <typename F, typename ... Ts>
        static typename hpx::util::detail::deferred_result_of<F(Ts&&...)>::type
        execute(executor_type& sched, F && f, Ts &&... ts)
        {
            return hpx::async(sched, std::forward<F>(f),
                std::forward<Ts>(ts)...).get();
        }

        /// \brief Bulk form of asynchronous execution agent creation
        ///
        /// This asynchronously creates a group of function invocations f(i)
        /// whose ordering is given by the execution_category associated with
        /// the executor.
        ///
        /// Here \a i takes on all values in the index space implied by shape.
        /// All exceptions thrown by invocations of f(i) are reported in a
        /// manner consistent with parallel algorithm execution through the
        /// returned future.
        ///
        /// \param sched  [in] The executor object to use for scheduling of the
        ///              function \a f.
        /// \param f     [in] The function which will be scheduled using the
        ///              given executor.
        /// \param shape [in] The shape objects which defines the iteration
        ///              boundaries for the arguments to be passed to \a f.
        /// \param ts... [in] Additional arguments to use to invoke \a f.
        ///
        /// \returns The return type of \a executor_type::async_execute if
        ///          defined by \a executor_type. Otherwise a vector
        ///          of futures holding the returned value of each invocation
        ///          of \a f.
        ///
        template <typename F, typename Shape, typename ... Ts>
        static std::vector<hpx::future<
            typename detail::bulk_async_execute_result<F, Shape, Ts...>::type
        > >
        bulk_async_execute(executor_type& sched, F && f, Shape const& shape,
            Ts &&... ts)
        {
            std::vector<hpx::future<
                    typename detail::bulk_async_execute_result<
                        F, Shape, Ts...
                    >::type
                > > results;

            for (auto const& elem: shape)
            {
                results.push_back(hpx::async(sched, std::forward<F>(f),
                    elem, ts...));
            }

            return results;
        }

        /// \brief Bulk form of synchronous execution agent creation
        ///
        /// This synchronously creates a group of function invocations f(i)
        /// whose ordering is given by the execution_category associated with
        /// the executor. The function synchronizes the execution of all
        /// scheduled functions with the caller.
        ///
        /// Here \a i takes on all values in the index space implied by shape.
        /// All exceptions thrown by invocations of f(i) are reported in a
        /// manner consistent with parallel algorithm execution through the
        /// returned future.
        ///
        /// \param sched  [in] The executor object to use for scheduling of the
        ///              function \a f.
        /// \param f     [in] The function which will be scheduled using the
        ///              given executor.
        /// \param shape [in] The shape objects which defines the iteration
        ///              boundaries for the arguments to be passed to \a f.
        /// \param ts... [in] Additional arguments to use to invoke \a f.
        ///
        /// \returns The return type of \a executor_type::execute if defined
        ///          by \a executor_type. Otherwise a vector holding the
        ///          returned value of each invocation of \a f except when
        ///          \a f returns void, which case void is returned.
        ///
        template <typename F, typename Shape, typename ... Ts>
        static typename detail::bulk_execute_result<F, Shape, Ts...>::type
        bulk_execute(executor_type& sched, F && f, Shape const& shape,
            Ts &&... ts)
        {
            std::vector<hpx::future<
                    typename detail::bulk_async_execute_result<
                        F, Shape, Ts...
                    >::type
                > > results;

            for (auto const& elem: shape)
            {
                results.push_back(hpx::async(sched, std::forward<F>(f),
                    elem, ts...));
            }

            return hpx::util::unwrapped(results);
        }

        /// Retrieve whether this executor has operations pending or not.
        /// All threads::executors invoke sched.num_pending_closures().
        ///
        /// \param sched  [in] The executor object to use for querying the
        ///               number of pending tasks.
        ///
        static bool has_pending_closures(executor_type& sched)
        {
            return sched.num_pending_closures() != 0;
        }
    };
}}}

#endif

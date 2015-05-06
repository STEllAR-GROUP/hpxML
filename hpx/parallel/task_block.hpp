//  Copyright (c) 2007-2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file task_block.hpp

#if !defined(HPX_PARALLEL_TASK_BLOCK_JUL_09_2014_1250PM)
#define HPX_PARALLEL_TASK_BLOCK_JUL_09_2014_1250PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/config/emulate_deleted.hpp>
#include <hpx/lcos/local/dataflow.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/lcos/when_all.hpp>
#include <hpx/util/scoped_unlock.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/async.hpp>

#include <hpx/parallel/config/inline_namespace.hpp>
#include <hpx/parallel/exception_list.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/util/detail/algorithm_result.hpp>

#include <memory>                           // std::addressof
#include <boost/utility/addressof.hpp>      // boost::addressof

#include <boost/static_assert.hpp>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v2)
{
    namespace detail
    {
        /// \cond NOINTERNAL
        ///////////////////////////////////////////////////////////////////////
        void handle_task_block_exceptions(parallel::exception_list& errors)
        {
            try {
                boost::rethrow_exception(boost::current_exception());
            }
            catch (parallel::exception_list const& el) {
                for (boost::exception_ptr const& e: el)
                    errors.add(e);
            }
            catch (...) {
                errors.add(boost::current_exception());
            }
        }

        hpx::launch get_launch_policy(std::true_type)
        {
            return hpx::launch::sync;
        }

        hpx::launch get_launch_policy(std::false_type)
        {
            return hpx::launch::fork;
        }

        template <typename ExPolicy>
        hpx::launch get_launch_policy(ExPolicy const&)
        {
            typedef std::integral_constant<
                    bool,
                    parallel::is_sequential_execution_policy<ExPolicy>::value
                > is_seq;
            return get_launch_policy(is_seq());
        }

        inline hpx::launch
        get_launch_policy(parallel::execution_policy const& policy)
        {
            using namespace parallel::v1::detail;
            int t = which(policy);

            if (t == execution_policy_enum::sequential ||
                t == execution_policy_enum::sequential_task)
            {
                return hpx::launch::sync;
            }
            return hpx::launch::fork;
        }
        /// \endcond
    }

    /// The class \a task_canceled_exception defines the type of objects thrown
    /// by task_block::run or task_block::wait if they detect
    /// that an exception is pending within the current parallel region.
    class task_canceled_exception : public hpx::exception
    {
    public:
        task_canceled_exception() BOOST_NOEXCEPT
          : hpx::exception(hpx::task_canceled_exception)
        {}
    };

    /// The class task_block defines an interface for forking and
    /// joining parallel tasks. The \a define_task_block and
    /// \a define_task_block_restore_thread
    /// function templates create an object of type task_block and
    /// pass a reference to that object to a user-provided callable object.
    ///
    /// An object of class \a task_block cannot be constructed,
    /// destroyed, copied, or moved except by the implementation of the task
    /// region library. Taking the address of a task_block object via
    /// operator& or addressof is ill formed. The result of obtaining its
    /// address by any other means is unspecified.
    ///
    /// A \a task_block is active if it was created by the nearest
    /// enclosing task block, where "task block" refers to an invocation of
    /// define_task_block or define_task_block_restore_thread and "nearest
    /// enclosing" means the most
    /// recent invocation that has not yet completed. Code designated for
    /// execution in another thread by means other than the facilities in this
    /// section (e.g., using thread or async) are not enclosed in the task
    /// region and a task_block passed to (or captured by) such code
    /// is not active within that code. Performing any operation on a
    /// task_block that is not active results in undefined behavior.
    ///
    /// The \a task_block that is active before a specific call to the
    /// run member function is not active within the asynchronous function
    /// that invoked run. (The invoked function should not, therefore, capture
    /// the \a task_block from the surrounding block.)
    ///
    /// \code
    /// Example:
    ///     define_task_block([&](auto& tr) {
    ///         tr.run([&] {
    ///             tr.run([] { f(); });                // Error: tr is not active
    ///             define_task_block([&](auto& tr) {   // Nested task block
    ///                 tr.run(f);                      // OK: inner tr is active
    ///                 /// ...
    ///             });
    ///         });
    ///         /// ...
    ///     });
    /// \endcode
    ///
    template <typename ExPolicy = parallel::parallel_execution_policy>
    class task_block
    {
    private:
        /// \cond NOINTERNAL
        typedef hpx::lcos::local::spinlock mutex_type;

        template <typename ExPolicy_, typename F>
        friend typename util::detail::algorithm_result<ExPolicy_>::type
        define_task_block(ExPolicy_ &&, F &&);

        explicit task_block(ExPolicy const& policy = ExPolicy())
          : id_(threads::get_self_id()),
            policy_(policy)
        {
        }

        void wait_for_completion(std::false_type)
        {
           when();
        }

        void wait_for_completion(std::true_type)
        {
           when().wait();
        }

        void wait_for_completion()
        {
            typedef typename util::detail::algorithm_result<ExPolicy>::type
                result_type;
            typedef std::integral_constant<
                    bool, traits::is_future<result_type>::value
                > is_fut;
            wait_for_completion(is_fut());
        }

        ~task_block()
        {
            wait_for_completion();
        }

        task_block(task_block const &) = delete;
        task_block& operator=(task_block const &) = delete;

        task_block* operator&() const = delete;

        static void
        on_ready(std::vector<hpx::future<void> > && results,
            parallel::exception_list && errors)
        {
            for (hpx::future<void>& f: results)
            {
                if (f.has_exception())
                    errors.add(f.get_exception_ptr());
            }
            if (errors.size() != 0)
                boost::throw_exception(errors);
        }

        // return future representing the execution of all tasks
        typename util::detail::algorithm_result<ExPolicy>::type
        when(bool throw_on_error = false)
        {
            std::vector<hpx::future<void> > tasks;
            parallel::exception_list errors;

            {
                mutex_type::scoped_lock l(mtx_);
                std::swap(tasks_, tasks);
                std::swap(errors_, errors);
            }

            typedef util::detail::algorithm_result<ExPolicy> result;

            if (tasks.empty() && errors.size() == 0)
                return result::get();

            if (!throw_on_error)
                return result::get(hpx::when_all(tasks));

            return
                result::get(
                    hpx::lcos::local::dataflow(
                        hpx::util::bind(hpx::
                            util::one_shot(&task_block::on_ready),
                            hpx::util::placeholders::_1, std::move(errors)),
                        std::move(tasks)
                    ));
        }
        /// \endcond

    public:
        /// Causes the expression f() to be invoked asynchronously.
        /// The invocation of f is permitted to run on an unspecified thread
        /// in an unordered fashion relative to the sequence of operations
        /// following the call to run(f) (the continuation), or indeterminately
        /// sequenced within the same thread as the continuation.
        ///
        /// The call to \a run synchronizes with the invocation of f. The
        /// completion of f() synchronizes with the next invocation of wait on
        /// the same task_block or completion of the nearest enclosing
        /// task block (i.e., the \a define_task_block or
        /// \a define_task_block_restore_thread that created this task block).
        ///
        /// Requires: F shall be MoveConstructible. The expression, (void)f(),
        ///           shall be well-formed.
        ///
        /// Precondition: this shall be the active task_block.
        ///
        /// Postconditions: A call to run may return on a different thread than
        ///                 that on which it was called.
        ///
        /// \note The call to \a run is sequenced before the continuation as if
        ///       \a run returns on the same thread.
        ///       The invocation of the user-supplied callable object f may be
        ///       immediate or may be delayed until compute resources are
        ///       available. \a run might or might not return before invocation
        ///       of f completes.
        ///
        /// \throw This function may throw \a task_canceled_exception, as
        ///        described in Exception Handling.
        ///
        template <typename F>
        void run(F && f)
        {
            // The proposal requires that the task_block should be
            // 'active' to be usable.
            if (id_ != threads::get_self_id())
            {
                HPX_THROW_EXCEPTION(task_block_not_active,
                    "task_block::run",
                    "the task_block is not active");
            }

            hpx::future<void> result;
            threads::executor exec = policy_.get_executor();

            if (exec)
            {
                result = hpx::async(exec, boost::move(f));
            }
            else
            {
                result = hpx::async(detail::get_launch_policy(policy_),
                    boost::move(f));
            }

            mutex_type::scoped_lock l(mtx_);
            tasks_.push_back(std::move(result));
        }

        /// Blocks until the tasks spawned using this task_block have
        /// finished.
        ///
        /// Precondition: this shall be the active task_block.
        ///
        /// Postcondition: All tasks spawned by the nearest enclosing task
        ///                region have finished. A call to wait may return on
        ///                a different thread than that on which it was called.
        ///
        /// \note The call to \a wait is sequenced before the continuation as if
        ///       \a wait returns on the same thread.
        ///
        /// \throw This function may throw \a task_canceled_exception, as
        ///        described in Exception Handling.
        ///
        /// \code
        /// Example:
        ///     define_task_block([&](auto& tr) {
        ///         tr.run([&]{ process(a, w, x); }); // Process a[w] through a[x]
        ///         if (y < x) tr.wait();   // Wait if overlap between [w, x) and [y, z)
        ///         process(a, y, z);       // Process a[y] through a[z]
        ///     });
        /// \endcode
        ///
        void wait()
        {
            // The proposal requires that the task_block should be
            // 'active' to be usable.
            if (id_ != threads::get_self_id())
            {
                HPX_THROW_EXCEPTION(task_block_not_active,
                    "task_block::run", "the task_block is not active");
                return;
            }

            wait_for_completion();
        }

    private:
        mutable mutex_type mtx_;
        std::vector<hpx::future<void> > tasks_;
        parallel::exception_list errors_;
        threads::thread_id_type id_;
        ExPolicy policy_;
    };

    /// Constructs a \a task_block, tr, and invokes the expression
    /// \a f(tr) on the user-provided object, \a f.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the task block may be parallelized.
    /// \tparam F   The type of the user defined function to invoke inside the
    ///             define_task_block (deduced). \a F shall be MoveConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param f    The user defined function to invoke inside the task block.
    ///             Given an lvalue \a tr of type \a task_block, the
    ///             expression, (void)f(tr), shall be well-formed.
    ///
    /// Postcondition: All tasks spawned from \a f have finished execution.
    ///                A call to define_task_block may return on a different
    ///                thread than that on which it was called.
    ///
    /// \throws An \a exception_list, as specified in Exception Handling.
    ///
    /// \note It is expected (but not mandated) that f will (directly or
    ///       indirectly) call tr.run(_callable_object_).
    ///
    template <typename ExPolicy, typename F>
    typename util::detail::algorithm_result<ExPolicy>::type
    define_task_block(ExPolicy && policy, F && f)
    {
        BOOST_STATIC_ASSERT(parallel::is_execution_policy<ExPolicy>::value);

        typedef typename hpx::util::decay<ExPolicy>::type policy_type;
        task_block<policy_type> trh(std::forward<ExPolicy>(policy));

        // invoke the user supplied function
        try {
            f(trh);
        }
        catch (...) {
            detail::handle_task_block_exceptions(trh.errors_);
        }

        // regardless of whether f(trh) has thrown an exception we need to
        // obey the contract and wait for all tasks to join
        return trh.when(true);
    }

    /// Constructs a \a task_block, tr, and invokes the expression
    /// \a f(tr) on the user-provided object, \a f. This version uses
    /// \a parallel_execution_policy for task scheduling.
    ///
    /// \tparam F   The type of the user defined function to invoke inside the
    ///             define_task_block (deduced). \a F shall be MoveConstructible.
    ///
    /// \param f    The user defined function to invoke inside the task block.
    ///             Given an lvalue \a tr of type \a task_block, the
    ///             expression, (void)f(tr), shall be well-formed.
    ///
    /// Postcondition: All tasks spawned from \a f have finished execution.
    ///                A call to define_task_block may return on a different
    ///                thread than that on which it was called.
    ///
    /// \throws An \a exception_list, as specified in Exception Handling.
    ///
    /// \note It is expected (but not mandated) that f will (directly or
    ///       indirectly) call tr.run(_callable_object_).
    ///
    template <typename F>
    void define_task_block(F && f)
    {
        define_task_block(parallel::par, std::forward<F>(f));
    }

    /// \cond NOINTERNAL
    template <typename F>
    inline void
    define_task_block(parallel::execution_policy && policy, F && f)
    {
        switch(parallel::v1::detail::which(policy))
        {
        case parallel::v1::detail::execution_policy_enum::sequential:
            return define_task_block(
                *policy.get<sequential_execution_policy>(),
                std::forward<f>(f));

        case parallel::v1::detail::execution_policy_enum::sequential_task:
            return define_task_block(parallel::seq, std::forward<f>(f));

        case parallel::v1::detail::execution_policy_enum::parallel:
            return define_task_block(
                *policy.get<parallel_execution_policy>(),
                std::forward<f>(f));

        case parallel::v1::detail::execution_policy_enum::parallel_task:
            {
                parallel_task_execution_policy const& t =
                    *policy.get<parallel_task_execution_policy>();
                return define_task_block(
                    par(t.get_executor(), t.get_chunk_size()),
                    std::forward<f>(f));
            }

        case parallel::v1::detail::execution_policy_enum::parallel_vector:
            return define_task_block(
                *policy.get<parallel_vector_execution_policy>(),
                std::forward<f>(f));

        default:
            HPX_THROW_EXCEPTION(hpx::bad_parameter,
                "define_task_block",
                "The given execution policy is not supported");
        }
    }
    /// \endcond

    /// Constructs a \a task_block, tr, and invokes the expression
    /// \a f(tr) on the user-provided object, \a f.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the task block may be parallelized.
    /// \tparam F   The type of the user defined function to invoke inside the
    ///             define_task_block (deduced). \a F shall be MoveConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param f    The user defined function to invoke inside the define_task_block.
    ///             Given an lvalue \a tr of type \a task_block, the
    ///             expression, (void)f(tr), shall be well-formed.
    ///
    /// \throws An \a exception_list, as specified in Exception Handling.
    ///
    /// Postcondition: All tasks spawned from \a f have finished execution.
    ///                A call to \a define_task_block_restore_thread always returns on the
    ///                same thread as that on which it was called.
    ///
    /// \note It is expected (but not mandated) that f will (directly or
    ///       indirectly) call tr.run(_callable_object_).
    ///
    template <typename ExPolicy, typename F>
    typename util::detail::algorithm_result<ExPolicy>::type
    define_task_block_restore_thread(ExPolicy && policy, F && f)
    {
        BOOST_STATIC_ASSERT(parallel::is_execution_policy<ExPolicy>::value);

        // By design we always return on the same (HPX-) thread as we started
        // executing define_task_block_restore_thread.
        define_task_block(std::forward<ExPolicy>(policy), std::forward<F>(f));
    }

    /// Constructs a \a task_block, tr, and invokes the expression
    /// \a f(tr) on the user-provided object, \a f. This version uses
    /// \a parallel_execution_policy for task scheduling.
    ///
    /// \tparam F   The type of the user defined function to invoke inside the
    ///             define_task_block (deduced). \a F shall be MoveConstructible.
    ///
    /// \param f    The user defined function to invoke inside the define_task_block.
    ///             Given an lvalue \a tr of type \a task_block, the
    ///             expression, (void)f(tr), shall be well-formed.
    ///
    /// \throws An \a exception_list, as specified in Exception Handling.
    ///
    /// Postcondition: All tasks spawned from \a f have finished execution.
    ///                A call to \a define_task_block_restore_thread always returns on the
    ///                same thread as that on which it was called.
    ///
    /// \note It is expected (but not mandated) that f will (directly or
    ///       indirectly) call tr.run(_callable_object_).
    ///
    template <typename F>
    void define_task_block_restore_thread(F && f)
    {
        // By design we always return on the same (HPX-) thread as we started
        // executing define_task_block_restore_thread.
        define_task_block(parallel::par, std::forward<F>(f));
    }
}}}

/// \cond NOINTERNAL
namespace std
{
    template <typename ExPolicy>
    hpx::parallel::v2::task_block<ExPolicy>*
    addressof(hpx::parallel::v2::task_block<ExPolicy>&) = delete;
}
namespace boost
{
    template <typename ExPolicy>
    hpx::parallel::v2::task_block<ExPolicy>*
    addressof(hpx::parallel::v2::task_block<ExPolicy>&) = delete;
}
/// \endcond

#endif

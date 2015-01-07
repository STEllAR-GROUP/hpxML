//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/execution_policy.hpp

#if !defined(HPX_PARALLEL_EXECUTION_POLICY_MAY_27_2014_0908PM)
#define HPX_PARALLEL_EXECUTION_POLICY_MAY_27_2014_0908PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/runtime/threads/thread_executor.hpp>
#include <hpx/parallel/config/inline_namespace.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/serialization/serialization.hpp>

#include <memory>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v1)
{
    ///////////////////////////////////////////////////////////////////////////
    /// \cond NOINTERNAL
    struct task_execution_policy_tag
    {
        task_execution_policy_tag() {}
    };
    /// \endcond

    /// The execution policy tag \a task can be used to create a execution
    /// policy which forces the given algorithm to be executed in an
    /// asynchronous way.
    static task_execution_policy_tag const task;

    ///////////////////////////////////////////////////////////////////////////
    /// Extension: The class sequential_task_execution_policy is an execution
    /// policy type used as a unique type to disambiguate parallel algorithm
    /// overloading and indicate that a parallel algorithm's execution may be
    /// parallelized.
    ///
    /// The algorithm returns a future representing the result of the
    /// corresponding algorithm when invoked with the
    /// sequential_execution_policy.
    struct sequential_task_execution_policy
    {
        sequential_task_execution_policy() {}

        /// Create a new sequential_task_execution_policy from itself
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        ///
        /// \returns The new sequential_task_execution_policy
        ///
        sequential_task_execution_policy operator()(
            task_execution_policy_tag tag) const
        {
            return *this;
        }
    };

    /// Default sequential task execution policy object.
    static sequential_task_execution_policy const seq_task;

    /// Extension: The class parallel_task_execution_policy is an execution
    /// policy type used as a unique type to disambiguate parallel algorithm
    /// overloading and indicate that a parallel algorithm's execution may be
    /// parallelized.
    ///
    /// The algorithm returns a future representing the result of the
    /// corresponding algorithm when invoked with the parallel_execution_policy.
    struct parallel_task_execution_policy
    {
    public:
        /// \cond NOINTERNAL
        parallel_task_execution_policy() {}
        /// \endcond

        /// Create a new parallel_task_execution_policy referencing an executor and
        /// a chunk size.
        ///
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_task_execution_policy
        ///
        parallel_task_execution_policy operator()(threads::executor const& exec,
            std::size_t chunk_size) const
        {
            return parallel_task_execution_policy(exec, chunk_size);
        }

        /// Create a new parallel_task_execution_policy referencing an executor and
        /// a chunk size.
        ///
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        ///
        /// \returns The new parallel_task_execution_policy
        ///
        parallel_task_execution_policy operator()(
            threads::executor const& exec) const
        {
            return parallel_task_execution_policy(exec, chunk_size_);
        }

        /// Create a new parallel_task_execution_policy referencing a chunk size.
        ///
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_task_execution_policy
        ///
        parallel_task_execution_policy operator()(std::size_t chunk_size) const
        {
            return parallel_task_execution_policy(exec_, chunk_size);
        }

        /// Create a new parallel_task_execution_policy from itself
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        ///
        /// \returns The new parallel_task_execution_policy
        ///
        parallel_task_execution_policy operator()(
            task_execution_policy_tag tag) const
        {
            return *this;
        }

        /// \cond NOINTERNAL
        threads::executor get_executor() const { return exec_; }
        std::size_t get_chunk_size() const { return chunk_size_; }
        /// \endcond

    private:
        /// \cond NOINTERNAL
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, unsigned)
        {
            ar & chunk_size_;
        }

        parallel_task_execution_policy(threads::executor const& exec,
                std::size_t chunk_size)
          : exec_(exec), chunk_size_(chunk_size)
        {}

        threads::executor exec_;
        std::size_t chunk_size_;
        /// \endcond
    };

    /// Default parallel task execution policy object.
    static parallel_task_execution_policy const par_task;

    ///////////////////////////////////////////////////////////////////////////
    /// The class parallel_execution_policy is an execution policy type used
    /// as a unique type to disambiguate parallel algorithm overloading and
    /// indicate that a parallel algorithm's execution may be parallelized.
    struct parallel_execution_policy
    {
    public:
        /// \cond NOINTERNAL
        parallel_execution_policy() {}
        /// \endcond

        /// Create a new parallel_execution_policy referencing an executor and
        /// a chunk size.
        ///
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_execution_policy operator()(threads::executor const& exec,
            std::size_t chunk_size) const
        {
            return parallel_execution_policy(exec, chunk_size);
        }

        /// Create a new parallel_execution_policy referencing an executor and
        /// a chunk size.
        ///
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_execution_policy operator()(threads::executor const& exec) const
        {
            return parallel_execution_policy(exec, chunk_size_);
        }

        /// Create a new parallel_execution_policy referencing a chunk size.
        ///
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_execution_policy operator()(std::size_t chunk_size) const
        {
            return parallel_execution_policy(exec_, chunk_size);
        }

        /// Create a new parallel_task_execution_policy referencing an executor
        /// and a chunk size.
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_task_execution_policy operator()(task_execution_policy_tag tag,
            threads::executor const& exec, std::size_t chunk_size) const
        {
            return par_task(exec, chunk_size);
        }

        /// Create a new parallel_task_execution_policy referencing an executor
        /// and a chunk size.
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        /// \param exec         [in] The executor to use for the execution of
        ///                     the parallel algorithm the returned execution
        ///                     policy is used with
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_task_execution_policy operator()(task_execution_policy_tag tag,
            threads::executor const& exec) const
        {
            return par_task(exec, chunk_size_);
        }

        /// Create a new parallel_execution_policy referencing a chunk size.
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        /// \param chunk_size   [in] The chunk size controlling the number of
        ///                     iterations scheduled to be executed on the same
        ///                     HPX thread
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_task_execution_policy operator()(task_execution_policy_tag tag,
            std::size_t chunk_size) const
        {
            return par_task(exec_, chunk_size);
        }

        /// Create a new parallel_execution_policy referencing a chunk size.
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        ///
        /// \returns The new parallel_execution_policy
        ///
        parallel_task_execution_policy operator()(task_execution_policy_tag tag) const
        {
            return par_task(exec_, chunk_size_);
        }

        /// \cond NOINTERNAL
        threads::executor get_executor() const { return exec_; }
        std::size_t get_chunk_size() const { return chunk_size_; }
        /// \endcond

    private:
        /// \cond NOINTERNAL
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, unsigned)
        {
            ar & chunk_size_;
        }

        parallel_execution_policy(threads::executor const& exec,
                std::size_t chunk_size)
          : exec_(exec), chunk_size_(chunk_size)
        {}

        threads::executor exec_;
        std::size_t chunk_size_;
        // \endcond
    };

    /// Default parallel execution policy object.
    static parallel_execution_policy const par;

    ///////////////////////////////////////////////////////////////////////////
    /// The class sequential_execution_policy is an execution policy type used
    /// as a unique type to disambiguate parallel algorithm overloading and
    /// require that a parallel algorithm's execution may not be parallelized.
    struct sequential_execution_policy
    {
        /// \cond NOINTERNAL
        sequential_execution_policy() {}

        static threads::executor get_executor() { return threads::executor(); }
        static std::size_t get_chunk_size() { return 0; }
        // \endcond

        /// Create a new sequential_task_execution_policy referencing an executor
        /// and a chunk size.
        ///
        /// \param tag          [in] Specify that the corresponding asynchronous
        ///                     execution policy should be used
        ///
        /// \returns The new parallel_execution_policy
        ///
        sequential_task_execution_policy operator()(
            task_execution_policy_tag tag) const
        {
            return seq_task;
        }
    };

    /// Default sequential execution policy object.
    static sequential_execution_policy const seq;

    ///////////////////////////////////////////////////////////////////////////
    /// The class parallel_vector_execution_policy is an execution policy type used as
    /// a unique type to disambiguate parallel algorithm overloading and
    /// indicate that a parallel algorithm's execution may be vectorized.
    struct parallel_vector_execution_policy
    {
        /// \cond NOINTERNAL
        parallel_vector_execution_policy() {}

        static threads::executor get_executor() { return threads::executor(); }
        static std::size_t get_chunk_size() { return 0; }
        /// \endcond

        /// Create a new parallel_vector_execution_policy from itself
        ///
        /// \param tag [in] Specify that the corresponding asynchronous
        ///            execution policy should be used
        ///
        /// \returns The new parallel_vector_execution_policy
        ///
        parallel_vector_execution_policy operator()(
            task_execution_policy_tag tag) const
        {
            return *this;
        }
    };

    /// Default vector execution policy object.
    static parallel_vector_execution_policy const par_vec;

    ///////////////////////////////////////////////////////////////////////////
    class execution_policy;

    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename T>
        struct is_execution_policy
          : boost::mpl::false_
        {};

        template <>
        struct is_execution_policy<parallel_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_execution_policy<parallel_vector_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_execution_policy<sequential_execution_policy>
          : boost::mpl::true_
        {};

        // extension
        template <>
        struct is_execution_policy<sequential_task_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_execution_policy<parallel_task_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_execution_policy<execution_policy>
          : boost::mpl::true_
        {};
        // \endcond
    }

    ///////////////////////////////////////////////////////////////////////////
    /// 1. The type is_execution_policy can be used to detect execution
    ///    policies for the purpose of excluding function signatures
    ///    from otherwise ambiguous overload resolution participation.
    /// 2. If T is the type of a standard or implementation-defined execution
    ///    policy, is_execution_policy<T> shall be publicly derived from
    ///    integral_constant<bool, true>, otherwise from
    ///    integral_constant<bool, false>.
    /// 3. The behavior of a program that adds specializations for
    ///    is_execution_policy is undefined.
    ///
    template <typename T>
    struct is_execution_policy
      : detail::is_execution_policy<typename hpx::util::decay<T>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename T>
        struct is_parallel_execution_policy
          : boost::mpl::false_
        {};

        template <>
        struct is_parallel_execution_policy<parallel_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_parallel_execution_policy<parallel_vector_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_parallel_execution_policy<parallel_task_execution_policy>
          : boost::mpl::true_
        {};
        // \endcond
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Extension: Detect whether given execution policy enables parallelization
    ///
    /// 1. The type is_parallel_execution_policy can be used to detect parallel
    ///    execution policies for the purpose of excluding function signatures
    ///    from otherwise ambiguous overload resolution participation.
    /// 2. If T is the type of a standard or implementation-defined execution
    ///    policy, is_parallel_execution_policy<T> shall be publicly derived
    ///    from integral_constant<bool, true>, otherwise from
    ///    integral_constant<bool, false>.
    /// 3. The behavior of a program that adds specializations for
    ///    is_parallel_execution_policy is undefined.
    ///
    template <typename T>
    struct is_parallel_execution_policy
      : detail::is_parallel_execution_policy<typename hpx::util::decay<T>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename T>
        struct is_sequential_execution_policy
          : boost::mpl::false_
        {};

        template <>
        struct is_sequential_execution_policy<sequential_task_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_sequential_execution_policy<sequential_execution_policy>
          : boost::mpl::true_
        {};
        // \endcond
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Extension: Detect whether given execution policy does not enable
    ///            parallelization
    ///
    /// 1. The type is_sequential_execution_policy can be used to detect
    ///    non-parallel execution policies for the purpose of excluding
    ///    function signatures from otherwise ambiguous overload resolution
    ///    participation.
    /// 2. If T is the type of a standard or implementation-defined execution
    ///    policy, is_sequential_execution_policy<T> shall be publicly derived
    ///    from integral_constant<bool, true>, otherwise from
    ///    integral_constant<bool, false>.
    /// 3. The behavior of a program that adds specializations for
    ///    is_sequential_execution_policy is undefined.
    ///
    // extension:
    template <typename T>
    struct is_sequential_execution_policy
      : detail::is_sequential_execution_policy<typename hpx::util::decay<T>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename T>
        struct is_async_execution_policy
          : boost::mpl::false_
        {};

        template <>
        struct is_async_execution_policy<sequential_task_execution_policy>
          : boost::mpl::true_
        {};

        template <>
        struct is_async_execution_policy<parallel_task_execution_policy>
          : boost::mpl::true_
        {};
        // \endcond
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Extension: Detect whether given execution policy makes algorithms
    ///            asynchronous
    ///
    /// 1. The type is_async_execution_policy can be used to detect
    ///    asynchronous execution policies for the purpose of excluding
    ///    function signatures from otherwise ambiguous overload resolution
    ///    participation.
    /// 2. If T is the type of a standard or implementation-defined execution
    ///    policy, is_async_execution_policy<T> shall be publicly derived
    ///    from integral_constant<bool, true>, otherwise from
    ///    integral_constant<bool, false>.
    /// 3. The behavior of a program that adds specializations for
    ///    is_async_execution_policy is undefined.
    ///
    // extension:
    template <typename T>
    struct is_async_execution_policy
      : detail::is_async_execution_policy<typename hpx::util::decay<T>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        /// \cond NOINTERNAL
        namespace execution_policy_enum
        {
            enum {
                unknown = -1,
                sequential = 0,
                sequential_task = 1,
                parallel = 2,
                parallel_task = 3,
                parallel_vector = 4
            };
        }

        int which(class parallel::execution_policy const& policy);
        /// \endcond
    }

    ///////////////////////////////////////////////////////////////////////////
    ///
    /// An execution policy is an object that expresses the requirements on the
    /// ordering of functions invoked as a consequence of the invocation of a
    /// standard algorithm. Execution policies afford standard algorithms the
    /// discretion to execute in parallel.
    ///
    /// 1. The class execution_policy is a dynamic container for execution
    ///    policy objects. execution_policy allows dynamic control over
    ///    standard algorithm execution.
    /// 2. Objects of type execution_policy shall be constructible and
    ///    assignable from objects of type T for which
    ///    is_execution_policy<T>::value is true.
    ///
    class execution_policy
    {
    private:
        boost::shared_ptr<void> inner_;
        std::type_info const* type_;

        execution_policy(execution_policy const& rhs)
          : inner_(rhs.inner_),
            type_(rhs.type_)
        {}

    public:
        /// Effects: Constructs an execution_policy object with a copy of
        ///          exec's state
        /// Requires: is_execution_policy<T>::value is true
        ///
        /// \param policy Specifies the inner execution policy
        template <typename ExPolicy>
        execution_policy(ExPolicy const& policy,
                typename boost::enable_if<
                    is_execution_policy<ExPolicy>, ExPolicy
                >::type* = 0)
          : inner_(boost::make_shared<ExPolicy>(policy)),
            type_(&typeid(ExPolicy))
        {}

        /// Move constructs a new execution_policy object.
        ///
        /// \param policy Specifies the inner execution policy
        execution_policy(execution_policy && policy)
          : inner_(std::move(policy.inner_)),
            type_(policy.type_)
        {
            policy.type_ = 0;
        }

        /// Extension: Create a new execution_policy holding the current policy
        /// made asynchronous.
        ///
        /// \param tag  [in] Specify that the corresponding asynchronous
        ///             execution policy should be used
        ///
        /// \returns The new execution_policy
        ///
        execution_policy operator()(task_execution_policy_tag tag) const
        {
            switch(detail::which(*this))
            {
            case detail::execution_policy_enum::sequential:
                return (*get<sequential_execution_policy>())(task);

            case detail::execution_policy_enum::parallel:
                return (*get<parallel_execution_policy>())(task);

            case detail::execution_policy_enum::parallel_vector:
                return (*get<parallel_vector_execution_policy>())(task);

            case detail::execution_policy_enum::sequential_task:
            case detail::execution_policy_enum::parallel_task:
                return *this;

            default:
                HPX_THROW_EXCEPTION(hpx::bad_parameter,
                    "hpx::parallel::execution_policy::operator()(task)",
                    "The given execution policy is not supported");
            }
        }

        /// Effects: Assigns a copy of exec's state to *this
        /// Returns: *this
        /// Requires: is_execution_policy<T>::value is true
        ///
        /// \param policy Specifies the inner execution policy
        template <typename ExPolicy>
        typename boost::enable_if<
            is_execution_policy<ExPolicy>, execution_policy
        >::type&
        operator=(ExPolicy const& policy)
        {
            inner_ = boost::make_shared<ExPolicy>(policy);
            type_ = &typeid(ExPolicy);
            return *this;
        }

        /// Move assigns a new execution policy to the object.
        ///
        /// \param policy Specifies the inner execution policy
        execution_policy& operator=(execution_policy && policy)
        {
            if (this != &policy)
            {
                inner_ = std::move(policy.inner_);
                type_ = policy.type_;
                policy.type_ = 0;
            }
            return *this;
        }

        /// Returns: typeid(T), such that T is the type of the execution policy
        ///          object contained by *this
        std::type_info const& type() const BOOST_NOEXCEPT
        {
            HPX_ASSERT(0 != type_);
            return *type_;
        }

        /// Returns: If target_type() == typeid(T), a pointer to the stored
        ///          execution policy object; otherwise a null pointer
        /// Requires: is_execution_policy<T>::value is true
        template <typename ExPolicy>
        ExPolicy* get() BOOST_NOEXCEPT
        {
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<ExPolicy, execution_policy>::value),
                "Incorrect execution policy parameter.");
            BOOST_STATIC_ASSERT_MSG(
                is_execution_policy<ExPolicy>::value,
                "Execution policy type required.");

            if (*type_ != typeid(ExPolicy))
                return 0;

            return static_cast<ExPolicy*>(inner_.get());
        }

        /// Returns: If target_type() == typeid(T), a pointer to the stored
        ///          execution policy object; otherwise a null pointer
        /// Requires: is_execution_policy<T>::value is true
        template <typename ExPolicy>
        ExPolicy const* get() const BOOST_NOEXCEPT
        {
            BOOST_STATIC_ASSERT_MSG(
                !(boost::is_same<ExPolicy, execution_policy>::value),
                "Incorrect execution policy parameter.");
            BOOST_STATIC_ASSERT_MSG(
                is_execution_policy<ExPolicy>::value,
                "Execution policy type required.");

            if (*type_ != typeid(ExPolicy))
                return 0;

            return static_cast<ExPolicy const*>(inner_.get());
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        /// \cond NOINTERNAL
        inline int which(execution_policy const& policy)
        {
            std::type_info const& t = policy.type();

            if (t == typeid(parallel_execution_policy))
                return execution_policy_enum::parallel;
            if (t == typeid(parallel_task_execution_policy))
                return execution_policy_enum::parallel_task;

            if (t == typeid(sequential_execution_policy))
                return execution_policy_enum::sequential;
            if (t == typeid(sequential_task_execution_policy))
                return execution_policy_enum::sequential_task;

            if (t == typeid(parallel_vector_execution_policy))
                return execution_policy_enum::parallel_vector;

            return execution_policy_enum::unknown;
        }
        /// \endcond
    }
}}}

#endif

// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


        
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0>
    class packaged_task<R(T0)>
      : private detail::packaged_task_base<R, R(T0)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1>
    class packaged_task<R(T0 , T1)>
      : private detail::packaged_task_base<R, R(T0 , T1)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2>
    class packaged_task<R(T0 , T1 , T2)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3>
    class packaged_task<R(T0 , T1 , T2 , T3)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7 , T8 t8)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 ) , std::forward<T8>( t8 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7 , T8 t8 , T9 t9)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 ) , std::forward<T8>( t8 ) , std::forward<T9>( t9 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7 , T8 t8 , T9 t9 , T10 t10)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 ) , std::forward<T8>( t8 ) , std::forward<T9>( t9 ) , std::forward<T10>( t10 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7 , T8 t8 , T9 t9 , T10 t10 , T11 t11)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 ) , std::forward<T8>( t8 ) , std::forward<T9>( t9 ) , std::forward<T10>( t10 ) , std::forward<T11>( t11 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}
namespace hpx { namespace lcos { namespace local
{
    template <typename R, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    class packaged_task<R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)>
      : private detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)>
    {
        HPX_MOVABLE_BUT_NOT_COPYABLE(packaged_task);
        typedef detail::packaged_task_base<R, R(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)> base_type;
    public:
        
        typedef R result_type;
        
        packaged_task()
          : base_type()
        {}
        template <typename F>
        explicit packaged_task(F && f,
            typename boost::enable_if_c<
                !boost::is_same<typename util::decay<F>::type, packaged_task>::value
             && traits::is_callable<typename util::decay<F>::type(
                    T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12
                )>::value
            >::type* = 0)
          : base_type(std::forward<F>(f))
        {}
        packaged_task(packaged_task && other)
          : base_type(std::move(other))
        {}
        packaged_task& operator=(packaged_task && rhs)
        {
            base_type::operator=(std::move(rhs));
            return *this;
        }
        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            base_type::swap(other);
        }
        void operator()(T0 t0 , T1 t1 , T2 t2 , T3 t3 , T4 t4 , T5 t5 , T6 t6 , T7 t7 , T8 t8 , T9 t9 , T10 t10 , T11 t11 , T12 t12)
        {
            base_type::invoke(
                util::deferred_call(this->function_, std::forward<T0>( t0 ) , std::forward<T1>( t1 ) , std::forward<T2>( t2 ) , std::forward<T3>( t3 ) , std::forward<T4>( t4 ) , std::forward<T5>( t5 ) , std::forward<T6>( t6 ) , std::forward<T7>( t7 ) , std::forward<T8>( t8 ) , std::forward<T9>( t9 ) , std::forward<T10>( t10 ) , std::forward<T11>( t11 ) , std::forward<T12>( t12 )),
                boost::is_void<R>());
        }
        
        using base_type::get_future;
        using base_type::valid;
        using base_type::reset;
    };
}}}

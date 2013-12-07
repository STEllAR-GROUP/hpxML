//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2013 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_FUTURE_MAR_06_2012_1059AM)
#define HPX_LCOS_FUTURE_MAR_06_2012_1059AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/config/forceinline.hpp>
#include <hpx/traits/is_future.hpp>
#include <hpx/lcos/detail/future_data.hpp>
#include <hpx/util/always_void.hpp>
#include <hpx/util/move.hpp>
#include <hpx/util/date_time_chrono.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/runtime/actions/continuation.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/detail/iterator.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/declval.hpp>

namespace hpx { namespace lcos
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename T>
        struct future_traits
        {};

        template <typename T>
        struct future_traits<lcos::future<T> >
        {
            typedef T type;
        };

        template <typename T>
        struct future_traits<lcos::future<T> const>
        {
            typedef T type;
        };

        template <typename T>
        struct future_traits<lcos::future<T> &>
        {
            typedef T type;
        };

        template <typename T>
        struct future_traits<lcos::future<T> const &>
        {
            typedef T type;
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Future, typename F, typename Enable = void>
        struct future_then_result
        {
            typedef struct continuation_not_callable
            {
                void error(Future& future, F& f)
                {
                    f(future);
                }

                ~continuation_not_callable()
                {
                    error(boost::declval<Future&>(), boost::declval<F&>());
                }
            } type;
        };

        template <typename Future, typename F>
        struct future_then_result<
            Future, F
          , typename util::always_void<
                typename boost::result_of<F(Future&)>::type
            >::type
        >
        {
            typedef typename boost::result_of<F(Future&)>::type result;

            typedef
                typename boost::mpl::if_<
                    traits::is_future<result>
                  , result
                  , lcos::future<result>
                >::type
                type;
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Result>
        struct unwrapped_future_result
          : boost::mpl::if_<traits::is_future<Result>, Result, void>
        {};

        ///////////////////////////////////////////////////////////////////////
        template <typename Iter>
        struct future_iterator_traits
        {
            typedef future_traits<
                typename boost::detail::iterator_traits<Iter>::value_type
            > traits_type;
        };

        template <typename T>
        struct future_iterator_traits<future<T> >
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    namespace local { namespace detail
    {
        template <typename Policy>
        struct is_launch_policy
          : boost::mpl::or_<
                boost::is_same<BOOST_SCOPED_ENUM(launch), Policy>
              , boost::is_base_and_derived<threads::executor, Policy>
            >
        {};
    }}

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result>
    class future
    {
    public:
        typedef lcos::detail::future_data<Result> future_data_type;

    private:
        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            boost::intrusive_ptr<detail::future_data<Result_> > const&);

        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            BOOST_RV_REF(boost::intrusive_ptr<detail::future_data<Result_> >));

        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            detail::future_data<Result_>* p);

        template <typename Result_>
        friend detail::future_data<Result_>*
            detail::get_future_data(lcos::future<Result_>&);

        template <typename Result_>
        friend detail::future_data<Result_> const*
            detail::get_future_data(lcos::future<Result_> const&);

    private:
        BOOST_COPYABLE_AND_MOVABLE(future)

        explicit future(future_data_type* p)
          : future_data_(p)
        {}

        explicit future(boost::intrusive_ptr<future_data_type> const& p)
          : future_data_(p)
        {}

        explicit future(BOOST_RV_REF(boost::intrusive_ptr<future_data_type>) p)
          : future_data_(p)
        {
            p.reset();
        }

    public:
        typedef lcos::promise<Result> promise_type;
        typedef Result result_type;

        future()
        {}

        ~future()
        {}

        future(future const& other)
          : future_data_(other.future_data_)
        {
        }

        future(BOOST_RV_REF(future) other)
          : future_data_(other.future_data_)
        {
            other.future_data_.reset();
        }

        // accept wrapped future
        future(BOOST_RV_REF(future<future>) other)
        {
            future f = other.unwrap();
            future_data_ = boost::move(f.future_data_);
        }

#ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
        // [N3722, 4.1] asks for this... defined at promise.hpp
        explicit future(promise_type& promise);
#endif

        // assignment
        future& operator=(BOOST_COPY_ASSIGN_REF(future) other)
        {
            if (this != &other)
                future_data_ = other.future_data_;
            return *this;
        }

        future& operator=(BOOST_RV_REF(future) other)
        {
            if (this != &other)
            {
                future_data_ = other.future_data_;
                other.future_data_.reset();
            }
            return *this;
        }

        void swap(future& other)
        {
            future_data_.swap(other.future_data_);
        }

        // retrieving the value
        Result const& get() const
        {
            if (!future_data_) {
                HPX_THROW_EXCEPTION(no_state,
                    "future<Result>::get",
                    "this future has no valid shared state");
            }

            typedef typename future_data_type::data_type data_type;
            data_type& data = future_data_->get_result();

            // no error has been reported, return the result
            return data.get_value();
        }

        Result const& get(error_code& ec) const
        {
            static result_type default_;

            if (!future_data_) {
                HPX_THROWS_IF(ec, no_state,
                    "future<Result>::get",
                    "this future has no valid shared state");
                return default_;
            }

            typedef typename future_data_type::data_type data_type;
            data_type& data = future_data_->get_result(ec);
            if (ec) return default_;

            // no error has been reported, return the result
            return data.get_value();
        }

    private:
        struct invalidate
        {
            invalidate(future& f)
              : f_(f)
            {}

            ~invalidate()
            {
                // This resets the intrusive pointer itself, not the future_data_.
                f_.future_data_.reset();
            }

            future& f_;
        };
        friend struct invalidate;

    public:
        Result move()
        {
            if (!future_data_) {
                HPX_THROW_EXCEPTION(no_state,
                    "future<Result>::move",
                    "this future has no valid shared state");
            }

            invalidate on_exit(*this);

            typedef typename future_data_type::data_type data_type;
            data_type& data = future_data_->get_result();

            // no error has been reported, return the result
            return data.move_value();
        }

        Result move(error_code& ec)
        {
            static result_type default_;

            if (!future_data_) {
                HPX_THROWS_IF(ec, no_state,
                    "future<Result>::move",
                    "this future has no valid shared state");
                return default_;
            }

            invalidate on_exit(*this);

            typedef typename future_data_type::data_type data_type;
            data_type& data = future_data_->get_result(ec);
            if (ec) return default_;

            // no error has been reported, return the result
            return data.move_value();
        }

        // state introspection
        bool is_ready() const
        {
            return future_data_ != 0 && future_data_->is_ready();
        }

        bool has_value() const
        {
            return future_data_ != 0 && future_data_->has_value();
        }

        bool has_exception() const
        {
            return future_data_ != 0 && future_data_->has_exception();
        }

        BOOST_SCOPED_ENUM(future_status) get_status() const
        {
            if (!future_data_)
                return future_status::uninitialized;

            return future_data_->get_status();
        }

        // cancellation support
        bool cancelable() const
        {
            return future_data_->cancelable();
        }

        void cancel()
        {
            future_data_->cancel();
        }

        bool valid() const BOOST_NOEXCEPT
        {
            // avoid warning about conversion to bool
            return future_data_.get() ? true : false;
        }

        // continuation support
        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(BOOST_FWD_REF(F) f);

        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(F) f);

        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(threads::executor& sched, BOOST_FWD_REF(F) f);

        // wait support
        void wait() const
        {
            future_data_->wait();
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_until(boost::posix_time::ptime const& at)
        {
            return future_data_->wait_until(at);
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_for(boost::posix_time::time_duration const& p)
        {
            return future_data_->wait_for(p);
        }

        template <typename Clock, typename Duration>
        BOOST_SCOPED_ENUM(future_status)
        wait_until(boost::chrono::time_point<Clock, Duration> const& abs_time)
        {
            return wait_until(util::to_ptime(abs_time));
        }

        template <typename Rep, typename Period>
        BOOST_SCOPED_ENUM(future_status)
        wait_for(boost::chrono::duration<Rep, Period> const& rel_time)
        {
            return wait_for(util::to_time_duration(rel_time));
        }

        typename detail::unwrapped_future_result<Result>::type
        unwrap(error_code& ec = throws);

    private:
        template <typename InnerResult, typename UnwrapResult>
        void on_inner_ready(future<InnerResult>& inner,
            boost::intrusive_ptr<lcos::detail::future_data<UnwrapResult> > p);

        template <typename UnwrapResult>
        void on_outer_ready(
            boost::intrusive_ptr<lcos::detail::future_data<UnwrapResult> > p);

    protected:
        boost::intrusive_ptr<future_data_type> future_data_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // extension: create a pre-initialized future object
    template <typename Result>
    future<typename util::decay<Result>::type>
    make_ready_future(BOOST_FWD_REF(Result) init)
    {
        typedef typename util::decay<Result>::type result_type;
        typedef lcos::detail::future_data<result_type> future_data_type;

        boost::intrusive_ptr<future_data_type> p(new future_data_type());
        p->set_data(boost::forward<Result>(init));

        return lcos::detail::make_future_from_data<result_type>(boost::move(p));
    }

    // extension: create a pre-initialized future object which holds the
    // given error
    template <typename Result>
    future<Result>
    make_error_future(boost::exception_ptr const& e)
    {
        typedef lcos::detail::future_data<Result> future_data_type;

        boost::intrusive_ptr<future_data_type> p(new future_data_type());
        p->set_exception(e);

        return lcos::detail::make_future_from_data<Result>(boost::move(p));
    }

    // extension: create a pre-initialized future object which gets ready at
    // a given point in time
    template <typename Result>
    future<typename util::decay<Result>::type>
    make_ready_future_at(boost::posix_time::ptime const& at,
        BOOST_FWD_REF(Result) init)
    {
        typedef typename util::decay<Result>::type result_type;
        typedef lcos::detail::timed_future_data<result_type> future_data_type;

        return lcos::detail::make_future_from_data<result_type>(
            new future_data_type(at, boost::forward<Result>(init)));
    }

    template <typename Clock, typename Duration, typename Result>
    future<typename util::decay<Result>::type>
    make_ready_future_at(boost::chrono::time_point<Clock, Duration> const& at,
        BOOST_FWD_REF(Result) init)
    {
        return make_ready_future_at(
            util::to_ptime(at), boost::forward<Result>(init));
    }

    template <typename Result>
    future<typename util::decay<Result>::type>
    make_ready_future_after(boost::posix_time::time_duration const& d,
        BOOST_FWD_REF(Result) init)
    {
        typedef typename util::decay<Result>::type result_type;
        typedef lcos::detail::timed_future_data<result_type> future_data_type;

        return lcos::detail::make_future_from_data<result_type>(
            new future_data_type(d, boost::forward<Result>(init)));
    }

    template <typename Rep, typename Period, typename Result>
    future<typename util::decay<Result>::type>
    make_ready_future_after(boost::chrono::duration<Rep, Period> const& d,
        BOOST_FWD_REF(Result) init)
    {
        return make_ready_future_at(
            util::to_time_duration(d), boost::forward<Result>(init));
    }

    ///////////////////////////////////////////////////////////////////////////
    template <>
    class future<void>
    {
    public:
        typedef lcos::detail::future_data<void> future_data_type;
        typedef future_data_type::data_type data_type;

    private:
        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            boost::intrusive_ptr<detail::future_data<Result_> > const&);

        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            BOOST_RV_REF(boost::intrusive_ptr<detail::future_data<Result_> >));

        template <typename Result_>
        friend lcos::future<Result_> detail::make_future_from_data(
            detail::future_data<Result_>*);

        template <typename Result_>
        friend detail::future_data<Result_>*
            detail::get_future_data(lcos::future<Result_>&);

        template <typename Result_>
        friend detail::future_data<Result_> const*
            detail::get_future_data(lcos::future<Result_> const&);

    private:
        BOOST_COPYABLE_AND_MOVABLE(future)

        explicit future(future_data_type* p)
          : future_data_(p)
        {}

        explicit future(boost::intrusive_ptr<future_data_type> const& p)
          : future_data_(p)
        {}

        explicit future(BOOST_RV_REF(boost::intrusive_ptr<future_data_type>) p)
          : future_data_(p)
        {
            p.reset();
        }

    public:
        typedef lcos::promise<void> promise_type;
        typedef void result_type;

        future()
        {}

        ~future()
        {}

        future(future const& other)
          : future_data_(other.future_data_)
        {
        }

        future(BOOST_RV_REF(future) other)
          : future_data_(other.future_data_)
        {
            other.future_data_.reset();
        }

        // extension: accept wrapped future
        future(BOOST_RV_REF(future<future>) other)
        {
            future f = other.unwrap();
            future_data_ = boost::move(f.future_data_);
        }

#ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
        // [N3722, 4.1] asks for this... defined at promise.hpp
        explicit future(promise_type& promise);
#endif

        // assignment
        future& operator=(BOOST_COPY_ASSIGN_REF(future) other)
        {
            if (this != &other)
                future_data_ = other.future_data_;
            return *this;
        }

        future& operator=(BOOST_RV_REF(future) other)
        {
            if (this != &other)
            {
                future_data_ = other.future_data_;
                other.future_data_.reset();
            }
            return *this;
        }

        void swap(future& other)
        {
            future_data_.swap(other.future_data_);
        }

        // retrieving the value
        void get(error_code& ec = throws) const
        {
            if (!future_data_) {
                HPX_THROW_EXCEPTION(no_state,
                    "future<void>::get",
                    "this future has no valid shared state");
            }

            future_data_->get_result(ec);
        }

        void move(error_code& ec = throws)
        {
            if (!future_data_) {
                HPX_THROW_EXCEPTION(no_state,
                    "future<void>::get",
                    "this future has no valid shared state");
            }

            future_data_->get_result(ec);

            // This resets the intrusive pointer itself, not the future_data_
            future_data_.reset();
        }

        // state introspection
        bool is_ready() const
        {
            return future_data_ != 0 && future_data_->is_ready();
        }

        bool has_value() const
        {
            return future_data_ != 0 && future_data_->has_value();
        }

        bool has_exception() const
        {
            return future_data_ != 0 && future_data_->has_exception();
        }

        BOOST_SCOPED_ENUM(future_status) get_status() const
        {
            if (!future_data_)
                return future_status::uninitialized;

            return future_data_->get_status();
        }

        // cancellation support
        bool cancelable() const
        {
            return future_data_->cancelable();
        }

        void cancel()
        {
            future_data_->cancel();
        }

        bool valid() const BOOST_NOEXCEPT
        {
            // avoid warning about conversion to bool
            return future_data_.get() ? true : false;
        }

        // continuation support
        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(BOOST_FWD_REF(F) f);

        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(F) f);

        template <typename F>
        typename detail::future_then_result<future, F>::type
        then(threads::executor& sched, BOOST_FWD_REF(F) f);

        // wait support
        void wait() const
        {
            future_data_->wait();
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_until(boost::posix_time::ptime const& at)
        {
            return future_data_->wait_until(at);
        }

        BOOST_SCOPED_ENUM(future_status)
        wait_for(boost::posix_time::time_duration const& p)
        {
            return future_data_->wait_for(p);
        }

        template <typename Clock, typename Duration>
        BOOST_SCOPED_ENUM(future_status)
        wait_until(boost::chrono::time_point<Clock, Duration> const& abs_time)
        {
            return wait_until(util::to_ptime(abs_time));
        }

        template <typename Rep, typename Period>
        BOOST_SCOPED_ENUM(future_status)
        wait_for(boost::chrono::duration<Rep, Period> const& rel_time)
        {
            return wait_for(util::to_time_duration(rel_time));
        }

    protected:
        boost::intrusive_ptr<future_data_type> future_data_;
    };

    // extension: create a pre-initialized future object
    inline future<void> make_ready_future()
    {
        typedef lcos::detail::future_data<void> future_data_type;

        boost::intrusive_ptr<future_data_type> p(new future_data_type());
        p->set_data(util::unused);

        return lcos::detail::make_future_from_data<void>(boost::move(p));
    }

    // extension: create a pre-initialized future object which gets ready at
    // a given point in time
    inline future<void> make_ready_future_at(
        boost::posix_time::ptime const& at)
    {
        typedef lcos::detail::timed_future_data<void> future_data_type;

        return lcos::detail::make_future_from_data<void>(
            new future_data_type(at, util::unused));
    }

    template <typename Clock, typename Duration>
    inline future<void> make_ready_future_at(
        boost::chrono::time_point<Clock, Duration> const& at)
    {
        return make_ready_future_at(util::to_ptime(at));
    }

    inline future<void> make_ready_future_after(
        boost::posix_time::time_duration const& d)
    {
        typedef lcos::detail::timed_future_data<void> future_data_type;

        return lcos::detail::make_future_from_data<void>(
            new future_data_type(d, util::unused));
    }

    template <typename Rep, typename Period>
    inline future<void> make_ready_future_at(
        boost::chrono::duration<Rep, Period> const& d)
    {
        return make_ready_future_after(util::to_time_duration(d));
    }

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Result>
        inline lcos::future<Result> make_future_from_data(
            boost::intrusive_ptr<detail::future_data<Result> > const& p)
        {
            return lcos::future<Result>(p);
        }

        template <typename Result>
        inline lcos::future<Result> make_future_from_data( //-V659
            BOOST_RV_REF(boost::intrusive_ptr<detail::future_data<Result> >) p)
        {
            return lcos::future<Result>(boost::move(p));
        }

        template <typename Result>
        inline lcos::future<Result> make_future_from_data(
            detail::future_data<Result>* p)
        {
            return lcos::future<Result>(p);
        }

        template <typename Result>
        inline detail::future_data<Result>*
            get_future_data(lcos::future<Result>& f)
        {
            return f.future_data_.get();
        }

        template <typename Result>
        inline detail::future_data<Result> const*
            get_future_data(lcos::future<Result> const& f)
        {
            return f.future_data_.get();
        }
    }
}}

HPX_REGISTER_TYPED_CONTINUATION_DECLARATION(
    hpx::lcos::future<void>,
    hpx_lcos_future_void_typed_continuation)

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    // special handling of actions returning a future
    template <typename Result>
    struct typed_continuation<lcos::future<Result> > : continuation
    {
        typed_continuation()
        {}

        explicit typed_continuation(naming::id_type const& gid)
          : continuation(gid)
        {}

        explicit typed_continuation(BOOST_RV_REF(naming::id_type) gid)
          : continuation(boost::move(gid))
        {}

        template <typename F>
        explicit typed_continuation(naming::id_type const& gid,
                BOOST_FWD_REF(F) f)
          : continuation(gid), f_(boost::forward<F>(f))
        {}

        template <typename F>
        explicit typed_continuation(BOOST_RV_REF(naming::id_type) gid,
                BOOST_FWD_REF(F) f)
          : continuation(boost::move(gid)), f_(boost::forward<F>(f))
        {}

        template <typename F>
        explicit typed_continuation(BOOST_FWD_REF(F) f)
          : f_(boost::forward<F>(f))
        {}

        ~typed_continuation()
        {
            init_registration<typed_continuation>::g.register_continuation();
        }

        void deferred_trigger(lcos::future<Result> result) const
        {
            if (f_.empty()) {
                if (!this->get_gid()) {
                    HPX_THROW_EXCEPTION(invalid_status,
                        "typed_continuation<lcos::future<Result> >::trigger_value",
                        "attempt to trigger invalid LCO (the id is invalid)");
                    return;
                }
                hpx::set_lco_value(this->get_gid(), result.move());
            }
            else {
                f_(this->get_gid(), result.move());
            }
        }

        void trigger_value(BOOST_RV_REF(lcos::future<Result>) result) const
        {
            LLCO_(info)
                << "typed_continuation<lcos::future<hpx::lcos::future<Result> > >::trigger("
                << this->get_gid() << ")";

            // if the future is ready, send the result back immediately
            if (result.is_ready()) {
                deferred_trigger(result);
                return;
            }

            // attach continuation to this future which will send the result back
            // once its ready
            deferred_result_ = result.then(
                util::bind(&typed_continuation::deferred_trigger,
                    boost::static_pointer_cast<typed_continuation const>(
                        shared_from_this()),
                    util::placeholders::_1));
        }

    private:
        char const* get_continuation_name() const
        {
            return detail::get_continuation_name<typed_continuation>();
        }

        /// serialization support
        void load(hpx::util::portable_binary_iarchive& ar)
        {
            // serialize base class
            typedef continuation base_type;
            this->base_type::load(ar);

            // serialize function
            bool have_function = false;
            ar.load(have_function);
            if (have_function)
                ar >> f_;
        }
        void save(hpx::util::portable_binary_oarchive& ar) const
        {
            // serialize base class
            typedef continuation base_type;
            this->base_type::save(ar);

            // serialize function
            bool have_function = !f_.empty();
            ar.save(have_function);
            if (have_function)
                ar << f_;
        }

        util::function<void(naming::id_type, Result)> f_;
        mutable lcos::future<void> deferred_result_;
    };

    // special handling of actions returning a future
    template <>
    struct typed_continuation<lcos::future<void> > : continuation
    {
        typed_continuation()
        {}

        explicit typed_continuation(naming::id_type const& gid)
          : continuation(gid)
        {}

        explicit typed_continuation(BOOST_RV_REF(naming::id_type) gid)
          : continuation(boost::move(gid))
        {}

        template <typename F>
        explicit typed_continuation(naming::id_type const& gid,
                BOOST_FWD_REF(F) f)
          : continuation(gid), f_(boost::forward<F>(f))
        {}

        template <typename F>
        explicit typed_continuation(BOOST_RV_REF(naming::id_type) gid,
                BOOST_FWD_REF(F) f)
          : continuation(boost::move(gid)), f_(boost::forward<F>(f))
        {}

        template <typename F>
        explicit typed_continuation(BOOST_FWD_REF(F) f)
          : f_(boost::forward<F>(f))
        {}

        ~typed_continuation()
        {
            init_registration<typed_continuation>::g.register_continuation();
        }

        void deferred_trigger(lcos::future<void> result) const
        {
            if (f_.empty()) {
                if (!this->get_gid()) {
                    HPX_THROW_EXCEPTION(invalid_status,
                        "typed_continuation<lcos::future<void> >::trigger_value",
                        "attempt to trigger invalid LCO (the id is invalid)");
                    return;
                }
                result.get();
                hpx::trigger_lco_event(this->get_gid());
            }
            else {
                result.get();
                f_(this->get_gid());
            }
        }

        void trigger_value(BOOST_RV_REF(lcos::future<void>) result) const
        {
            LLCO_(info)
                << "typed_continuation<lcos::future<hpx::lcos::future<void> > >::trigger("
                << this->get_gid() << ")";

            // if the future is ready, send the result back immediately
            if (result.is_ready()) {
                deferred_trigger(result);
                return;
            }

            // attach continuation to this future which will send the result back
            // once its ready
            deferred_result_ = result.then(
                util::bind(&typed_continuation::deferred_trigger,
                    boost::static_pointer_cast<typed_continuation const>(
                        shared_from_this()),
                    util::placeholders::_1));
        }

    private:
        char const* get_continuation_name() const
        {
            return detail::get_continuation_name<typed_continuation>();
        }

        /// serialization support
        void load(hpx::util::portable_binary_iarchive& ar)
        {
            // serialize base class
            typedef continuation base_type;
            this->base_type::load(ar);

            // serialize function
            bool have_function = false;
            ar.load(have_function);
            if (have_function)
                ar >> f_;
        }
        void save(hpx::util::portable_binary_oarchive& ar) const
        {
            // serialize base class
            typedef continuation base_type;
            this->base_type::save(ar);

            // serialize function
            bool have_function = !f_.empty();
            ar.save(have_function);
            if (have_function)
                ar << f_;
        }

        util::function<void(naming::id_type)> f_;
        mutable lcos::future<void> deferred_result_;
    };
}}

///////////////////////////////////////////////////////////////////////////////
// hoist names into main namespace
namespace hpx
{
    using lcos::make_ready_future;
    using lcos::make_error_future;
    using lcos::make_ready_future_at;
    using lcos::make_ready_future_after;
}

#endif

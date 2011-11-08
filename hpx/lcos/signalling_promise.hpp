//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_SIGNALLING_PROMISE_NOV_06_2011_0857PM)
#define HPX_LCOS_SIGNALLING_PROMISE_NOV_06_2011_0857PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/promise.hpp>
#include <hpx/lcos/local_mutex.hpp>

#include <boost/exception_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos { namespace detail
{
    /// A promise can be used by a single thread to invoke a (remote)
    /// action and wait for the result.
    template <typename Result, typename RemoteResult>
    class signalling_promise
      : public detail::promise<Result, RemoteResult, 1>
    {
    private:
        typedef detail::promise<Result, RemoteResult, 1> base_type;

    public:
        typedef HPX_STD_FUNCTION<void(Result const&)> completed_callback_type;
        typedef HPX_STD_FUNCTION<void(boost::exception_ptr const&)>
            error_callback_type;

        signalling_promise()
        {}

        signalling_promise(completed_callback_type const& data_sink)
          : on_completed_(data_sink)
        {}

        signalling_promise(completed_callback_type const& data_sink,
                error_callback_type const& error_sink)
          : on_completed_(data_sink), on_error_(error_sink)
        {}

        void set_result (RemoteResult const& result)
        {
            // We first invoke the callback to make sure that it was called
            // when the future is set.
            if (on_completed_) on_completed_(result);
            this->base_type::set_result(result);
        }

        void set_error (boost::exception_ptr const& e)
        {
            // We first invoke the callback to make sure that it was called
            // when the future is set.
            if (on_error_) on_error_(e);
            this->base_type::set_error(e);
        }

    private:
        completed_callback_type on_completed_;
        error_callback_type on_error_;
    };
}}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos
{
    ///////////////////////////////////////////////////////////////////////////
    /// \class signalling_promise signalling_promise.hpp hpx/lcos/signalling_promise.hpp
    ///
    /// A signalling_promise can be used by a single \a thread to invoke a
    /// (remote) action and wait for the result. The result is expected to be
    /// sent back to the promise using the LCO's set_event action
    ///
    /// A signalling_promise is one of the simplest synchronization primitives
    /// provided by HPX. It allows to synchronize on a eager evaluated remote
    /// operation returning a result of the type \a Result. The \a promise
    /// allows to synchronize exactly one \a thread (the one passed during
    /// construction time).
    ///
    /// \tparam Result   The template parameter \a Result defines the type this
    ///                  promise is expected to return from
    ///                  \a promise#get.
    /// \tparam RemoteResult The template parameter \a RemoteResult defines the
    ///                  type this signalling_promise is expected to receive
    ///                  from the remote action.
    ///
    /// \note            The action executed by the signalling_promise must
    ///                  return a value of a type convertible to the type as
    ///                  specified by the template parameter \a RemoteResult.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Result, typename RemoteResult>
    class signalling_promise
      : public promise<Result, RemoteResult>
    {
        typedef promise<Result, RemoteResult> base_type;

    public:
        typedef detail::signalling_promise<Result, RemoteResult> wrapped_type;
        typedef components::managed_component<wrapped_type> wrapping_type;

        typedef typename wrapped_type::completed_callback_type completed_callback_type;
        typedef typename wrapped_type::error_callback_type error_callback_type;

        /// Construct a new \a signalling_promise instance from the given
        /// promise instance.
        signalling_promise()
          : base_type(new wrapping_type(new wrapped_type()))
        {}

        signalling_promise(completed_callback_type const& data_sink)
          : base_type(new wrapping_type(new wrapped_type(data_sink)))
        {}

        signalling_promise(completed_callback_type const& data_sink,
                error_callback_type const& error_sink)
          : base_type(new wrapping_type(new wrapped_type(data_sink, error_sink)))
        {}

        typedef Result result_type;

        ~signalling_promise()
        {}
    };
}}

namespace hpx { namespace components
{
    // This specialization enables to mirrow teh detail::promise object
    // hierarchy for the managed_component<> as well.
    template <typename Derived, typename Result, typename RemoteResult>
    class managed_component<
              lcos::detail::signalling_promise<Result,  RemoteResult>, Derived>
      : public managed_component<
            lcos::detail::promise<Result,  RemoteResult, 1> >
    {
    private:
        typedef lcos::detail::promise<Result,  RemoteResult, 1> detail_base_type;
        typedef managed_component<detail_base_type> base_type;

    public:
        managed_component() : base_type()
        {
        }

        explicit managed_component(
                lcos::detail::signalling_promise<Result,  RemoteResult>* c)
          : base_type(static_cast<detail_base_type*>(c))
        {}

#define MANAGED_COMPONENT_CONSTRUCT(Z, N, _)                                  \
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>                        \
        managed_component(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& t))        \
          : base_type(BOOST_PP_ENUM_PARAMS(N, t))                             \
        {}                                                                    \
    /**/

        BOOST_PP_REPEAT_FROM_TO(1, HPX_COMPONENT_CREATE_ARG_MAX,
            MANAGED_COMPONENT_CONSTRUCT, _)

#undef MANAGED_COMPONENT_CONSTRUCT
    };
}}

#endif

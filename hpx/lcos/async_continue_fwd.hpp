//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

///////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_LCOS_ASYNC_CONTINUE_FWD_JAN_25_2013_0828AM)
#define HPX_LCOS_ASYNC_CONTINUE_FWD_JAN_25_2013_0828AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/traits.hpp>
#include <hpx/util/move.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/result_of.hpp>
#include <hpx/lcos/future.hpp>

namespace hpx
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Action, typename F>
        struct result_of_async_continue
            : actions::detail::remote_action_result<
                typename util::result_of<typename util::decay<F>::type(
                    naming::id_type,
                    typename hpx::actions::extract_action<
                        Action
                    >::remote_result_type
                )>::type
            >
        {};

        template <
            typename Action, typename RemoteResult,
            typename F, typename ...Ts>
        typename boost::enable_if_c<
            util::tuple_size<typename Action::arguments_type>::value == sizeof...(Ts)
          , lcos::future<
                typename traits::promise_local_result<
                    typename result_of_async_continue<Action, F>::type
                >::type
            >
        >::type
        async_continue_r(
            naming::id_type const& gid, F&& f, Ts&&... vs);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Action, typename F, typename ...Ts>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == sizeof...(Ts)
      , lcos::future<
            typename traits::promise_local_result<
                typename detail::result_of_async_continue<Action, F>::type
            >::type
        >
    >::type
    async_continue(naming::id_type const& gid, F&& f, Ts&&... vs);

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename Component, typename Result, typename Arguments,
        typename Derived, typename F, typename ...Ts>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == sizeof...(Ts)
      , lcos::future<
            typename traits::promise_local_result<
                typename detail::result_of_async_continue<Derived, F>::type
            >::type
        >
    >::type
    async_continue(
        hpx::actions::action<Component, Result, Arguments, Derived> /*act*/
      , naming::id_type const& gid, F&& f, Ts&&... vs);
}

#endif

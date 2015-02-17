//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

///////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_LCOS_ASYNC_CONTINUE_JAN_25_2013_0824AM)
#define HPX_LCOS_ASYNC_CONTINUE_JAN_25_2013_0824AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/traits.hpp>
#include <hpx/traits/promise_remote_result.hpp>
#include <hpx/traits/promise_local_result.hpp>
#include <hpx/runtime/actions/action_support.hpp>
#include <hpx/lcos/packaged_action.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/lcos/async_fwd.hpp>
#include <hpx/lcos/async_continue_fwd.hpp>

namespace hpx
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <
            typename Action, typename RemoteResult
          , typename Cont, typename ...Ts>
        lcos::future<
            typename traits::promise_local_result<
                typename result_of_async_continue<Action, Cont>::type
            >::type
        >
        async_continue_r(Cont&& cont, naming::id_type const& gid, Ts&&... vs)
        {
            typedef
                typename traits::promise_local_result<
                    typename result_of_async_continue<Action, Cont>::type
                >::type
            result_type;

            typedef
                typename hpx::actions::extract_action<
                    Action
                >::result_type
            continuation_result_type;

            lcos::promise<result_type, RemoteResult> p;
            apply<Action>(
                new hpx::actions::typed_continuation<continuation_result_type>(
                    p.get_gid(), std::forward<Cont>(cont))
              , gid, std::forward<Ts>(vs)...);
            return p.get_future();
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Action, typename Cont, typename ...Ts>
    lcos::future<
        typename traits::promise_local_result<
            typename detail::result_of_async_continue<Action, Cont>::type
        >::type
    >
    async_continue(Cont&& cont, naming::id_type const& gid, Ts&&... vs)
    {
        typedef
            typename traits::promise_local_result<
                typename detail::result_of_async_continue<Action, Cont>::type
            >::type
        result_type;

        return detail::async_continue_r<Action, result_type>(
            std::forward<Cont>(cont), gid, std::forward<Ts>(vs)...);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename Component, typename Signature, typename Derived,
        typename Cont, typename ...Ts>
    lcos::future<
         typename traits::promise_local_result<
            typename detail::result_of_async_continue<Derived, Cont>::type
        >::type
    >
    async_continue(
        hpx::actions::basic_action<Component, Signature, Derived> /*act*/
      , Cont&& cont, naming::id_type const& gid, Ts&&... vs)
    {
        return async_continue<Derived>(
            std::forward<Cont>(cont), gid, std::forward<Ts>(vs)...);
    }
}

#endif

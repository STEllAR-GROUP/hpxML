// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_1
        {
            template <typename Arg0>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_1<Action, lcos::unique_future<R> >
        {
            template <typename Arg0>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 )));
            }
        };
    }
    
    template <typename Action, typename Arg0>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_1<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_2
        {
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_2<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_2<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_3
        {
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_3<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_3<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_4
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_4<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_4<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_5
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_5<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_5<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_6
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_6<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_6<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_7
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_7<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_7<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_8
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_8<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_8<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_9
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_9<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_9<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
    }
}
namespace hpx
{
    namespace detail
    {
        template <typename Action, typename Result>
        struct sync_local_invoke_10
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE static lcos::unique_future<Result> call(
                naming::id_type const& gid, naming::address const&,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
            {
                lcos::packaged_action<Action, Result> p;
                p.apply(launch::sync, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
                return p.get_future();
            }
        };
        template <typename Action, typename R>
        struct sync_local_invoke_10<Action, lcos::unique_future<R> >
        {
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE static lcos::unique_future<R> call(
                boost::mpl::true_, naming::id_type const&,
                naming::address const& addr, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
            {
                HPX_ASSERT(components::types_are_compatible(addr.type_,
                    components::get_component_type<
                        typename Action::component_type>()));
                return Action::execute_function(addr.address_,
                    util::forward_as_tuple(boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 )));
            }
        };
    }
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename traits::promise_local_result<
            typename action_type::remote_result_type
        >::type result_type;
        naming::address addr;
        if (policy == launch::sync && agas::is_local_address(gid, addr))
        {
            return detail::sync_local_invoke_10<action_type, result_type>::
                call(gid, addr, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
        }
        lcos::packaged_action<action_type, result_type> p;
        if (policy == launch::sync || detail::has_async_policy(policy))
        {
            if (addr)
                p.apply(policy, addr, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
            else
                p.apply(policy, gid, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
        }
        return p.get_future();
    }
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::remote_result_type
        >::type>
    async(naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
    {
        return async<Action>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
    }
    
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const & , naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
    {
        return async<Derived>(policy, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
    }
    template <typename Component, typename Result,
        typename Arguments, typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    lcos::unique_future<
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Derived>::remote_result_type
        >::type>
    async(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > const &, naming::id_type const& gid, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9)
    {
        return async<Derived>(launch::all, gid,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
    }
}

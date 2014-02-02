// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <typename Action, typename Arg0,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 1
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0, F && f);
    template <typename Action, typename Arg0, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 1
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 1
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 1
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 2
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1, F && f);
    template <typename Action, typename Arg0 , typename Arg1, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 2
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 2
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 2
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 3
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 3
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 3
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 3
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 4
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 4
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 4
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 4
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 5
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 5
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 5
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 5
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 6
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 6
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 6
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 6
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 7
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 7
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 7
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 7
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 8
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 8
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 8
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 8
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 9
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 9
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 9
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 9
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8,
        F && f);
}
namespace hpx
{
    
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9,
        typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 10
      , lcos::unique_future<
            typename actions::detail::remote_action_result<
                typename util::result_of_continuation<Action, F>::type
            >::type>
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy, naming::id_type const& gid,
        Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9, F && f);
    template <typename Action, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9, typename F>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 10
      , lcos::unique_future<
            typename util::result_of_continuation<Action, F>::type
        >
    >::type
    async_continue(naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9,
        F && f);
    
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 10
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(BOOST_SCOPED_ENUM(launch) policy,
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9,
        F && f);
    template <typename Component, typename Result, typename Arguments,
        typename Derived, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9, typename F>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 10
      , lcos::unique_future<
            typename util::result_of_continuation<Derived, F>::type
        >
    >::type
    async_continue(
        hpx::actions::action<
            Component, Result, Arguments, Derived
        > , naming::id_type const& gid, Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9,
        F && f);
}

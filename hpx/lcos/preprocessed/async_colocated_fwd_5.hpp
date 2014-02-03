// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <
        typename Action
       >
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 0
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
       );
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
       >
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 0
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
       );
}
namespace hpx
{
    
    template <
        typename Action
      , typename Arg0>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 1
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , Arg0 && arg0);
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
      , typename Arg0>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 1
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
      , Arg0 && arg0);
}
namespace hpx
{
    
    template <
        typename Action
      , typename Arg0 , typename Arg1>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 2
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , Arg0 && arg0 , Arg1 && arg1);
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
      , typename Arg0 , typename Arg1>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 2
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
      , Arg0 && arg0 , Arg1 && arg1);
}
namespace hpx
{
    
    template <
        typename Action
      , typename Arg0 , typename Arg1 , typename Arg2>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 3
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2);
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
      , typename Arg0 , typename Arg1 , typename Arg2>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 3
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2);
}
namespace hpx
{
    
    template <
        typename Action
      , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 4
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3);
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
      , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 4
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3);
}
namespace hpx
{
    
    template <
        typename Action
      , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    typename boost::enable_if_c<
        util::tuple_size<typename Action::arguments_type>::value == 5
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Action>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4);
    
    template <
        typename Component, typename Result, typename Arguments, typename Derived
      , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    typename boost::enable_if_c<
        util::tuple_size<Arguments>::value == 5
      , lcos::unique_future<
            typename traits::promise_local_result<
                typename hpx::actions::extract_action<Derived>::remote_result_type
            >::type>
    >::type
    async_colocated(
        naming::id_type const& gid
      , hpx::actions::action<
            Component, Result, Arguments, Derived
        > 
      , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4);
}

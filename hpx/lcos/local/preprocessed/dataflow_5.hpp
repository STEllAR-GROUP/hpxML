// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}

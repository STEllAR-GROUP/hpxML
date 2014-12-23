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
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}
namespace hpx { namespace lcos { namespace local
{
    
    template <typename Policy, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_launch_policy<
            typename util::decay<Policy>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
            >
        >
    >::type
    dataflow(
        Policy && policy
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14
    )
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Policy>(policy)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)) , hpx::traits::acquire_future_disp()( std::forward<F14>(f14)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Executor, typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14>
    BOOST_FORCEINLINE
    typename boost::lazy_enable_if<
        traits::is_executor<
            typename util::decay<Executor>::type
        >
      , detail::dataflow_frame<
            threads::executor
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
            >
        >
    >::type
    dataflow(
        Executor && sched
      , Func && func
      , F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14
    )
    {
        typedef
            detail::dataflow_frame<
                threads::executor
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                std::forward<Executor>(sched)
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)) , hpx::traits::acquire_future_disp()( std::forward<F14>(f14)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        traits::is_launch_policy_or_executor<
            typename util::decay<Func>::type
        >
      , detail::dataflow_frame<
            BOOST_SCOPED_ENUM(launch)
          , typename hpx::util::decay<Func>::type
          , hpx::util::tuple<
                typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
            >
        >
    >::type
    dataflow(Func && func, F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14)
    {
        typedef
            detail::dataflow_frame<
                BOOST_SCOPED_ENUM(launch)
              , typename hpx::util::decay<Func>::type
              , hpx::util::tuple<
                    typename hpx::traits::acquire_future<F0>::type , typename hpx::traits::acquire_future<F1>::type , typename hpx::traits::acquire_future<F2>::type , typename hpx::traits::acquire_future<F3>::type , typename hpx::traits::acquire_future<F4>::type , typename hpx::traits::acquire_future<F5>::type , typename hpx::traits::acquire_future<F6>::type , typename hpx::traits::acquire_future<F7>::type , typename hpx::traits::acquire_future<F8>::type , typename hpx::traits::acquire_future<F9>::type , typename hpx::traits::acquire_future<F10>::type , typename hpx::traits::acquire_future<F11>::type , typename hpx::traits::acquire_future<F12>::type , typename hpx::traits::acquire_future<F13>::type , typename hpx::traits::acquire_future<F14>::type
                >
            >
            frame_type;
        boost::intrusive_ptr<frame_type> p(new frame_type(
                launch::all
              , std::forward<Func>(func)
              , hpx::util::forward_as_tuple(
                    hpx::traits::acquire_future_disp()( std::forward<F0>(f0)) , hpx::traits::acquire_future_disp()( std::forward<F1>(f1)) , hpx::traits::acquire_future_disp()( std::forward<F2>(f2)) , hpx::traits::acquire_future_disp()( std::forward<F3>(f3)) , hpx::traits::acquire_future_disp()( std::forward<F4>(f4)) , hpx::traits::acquire_future_disp()( std::forward<F5>(f5)) , hpx::traits::acquire_future_disp()( std::forward<F6>(f6)) , hpx::traits::acquire_future_disp()( std::forward<F7>(f7)) , hpx::traits::acquire_future_disp()( std::forward<F8>(f8)) , hpx::traits::acquire_future_disp()( std::forward<F9>(f9)) , hpx::traits::acquire_future_disp()( std::forward<F10>(f10)) , hpx::traits::acquire_future_disp()( std::forward<F11>(f11)) , hpx::traits::acquire_future_disp()( std::forward<F12>(f12)) , hpx::traits::acquire_future_disp()( std::forward<F13>(f13)) , hpx::traits::acquire_future_disp()( std::forward<F14>(f14)))
            ));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}}

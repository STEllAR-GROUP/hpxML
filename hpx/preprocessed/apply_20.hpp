// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    
    template <typename F>
    bool apply(threads::executor& sched, BOOST_FWD_REF(F) f)
    {
        sched.add(boost::forward<F>(f), "hpx::apply");
        return false; 
    }
    template <typename F>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<F()>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f)
    {
        threads::register_thread(boost::forward<F>(f), "hpx::apply");
        return false; 
    }
    
    
    template <typename Action, typename BoundArgs>
    bool apply(hpx::util::detail::bound_action<Action, BoundArgs> const& bound)
    {
        return bound.apply();
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0
    )
    {
        return bound.apply(boost::forward<A0>( a0 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 ));
    }
}
namespace hpx
{
    
    
    
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(threads::executor& sched, BOOST_FWD_REF(F) f,
        BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18 , BOOST_FWD_REF(A19) a19)
    {
        sched.add(util::bind(util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 ) , boost::forward<A19>( a19 )), "hpx::apply");
        return false;
    }
    template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    typename boost::enable_if_c<
        traits::detail::is_callable_not_action<
            F(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)>::value
     && !traits::is_bound_action<typename util::decay<F>::type>::value
      , bool
    >::type
    apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18 , BOOST_FWD_REF(A19) a19)
    {
        threads::register_thread(util::bind(
            util::protect(boost::forward<F>(f)),
            boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 ) , boost::forward<A19>( a19 )), "hpx::apply");
        return false;
    }
    
    template <
        typename Action, typename BoundArgs
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
    >
    bool apply(
        hpx::util::detail::bound_action<Action, BoundArgs> const& bound
      , BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18 , BOOST_FWD_REF(A19) a19
    )
    {
        return bound.apply(boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 ) , boost::forward<A19>( a19 ));
    }
}

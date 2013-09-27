// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ));
    };
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ));
    };
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ));
    };
    template <typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0)
    {
        typedef
            typename invoke_result_of<F(Arg0)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 )
            );
    };
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0);
    }
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0));
    }
    template <typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0);
    }
    template <typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
    };
    template <typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1));
    }
    template <typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1);
    }
    template <typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type , typename boost::add_const<Arg3>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type , typename util::detail::add_rvalue_reference<Arg3>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type , typename boost::add_const<Arg3>::type , typename boost::add_const<Arg4>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type , typename util::detail::add_rvalue_reference<Arg3>::type , typename util::detail::add_rvalue_reference<Arg4>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type , typename boost::add_const<Arg3>::type , typename boost::add_const<Arg4>::type , typename boost::add_const<Arg5>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type , typename util::detail::add_rvalue_reference<Arg3>::type , typename util::detail::add_rvalue_reference<Arg4>::type , typename util::detail::add_rvalue_reference<Arg5>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5 , args.a6);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5) , boost::forward<Arg6>(args.a6));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type , typename boost::add_const<Arg3>::type , typename boost::add_const<Arg4>::type , typename boost::add_const<Arg5>::type , typename boost::add_const<Arg6>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5 , args.a6);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type , typename util::detail::add_rvalue_reference<Arg3>::type , typename util::detail::add_rvalue_reference<Arg4>::type , typename util::detail::add_rvalue_reference<Arg5>::type , typename util::detail::add_rvalue_reference<Arg6>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5) , boost::forward<Arg6>(args.a6));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename boost::disable_if<
        boost::mpl::or_<
            boost::is_member_pointer<typename util::decay<F>::type>
          , boost::is_reference_wrapper<typename util::decay<F>::type>
        >
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return
            util::void_guard<R>(), boost::forward<F>(f)
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_member_pointer<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return
            util::void_guard<R>(), boost::mem_fn(boost::forward<F>(f))
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename boost::enable_if<
        boost::is_reference_wrapper<typename util::decay<F>::type>
      , R
    >::type
    invoke_r(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        return
            util::void_guard<R>(), (f.get())
                (boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
    };
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7)>::type
    invoke(BOOST_FWD_REF(F) f, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7)
    {
        typedef
            typename invoke_result_of<F(Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7)>::type
            result_type;
        return
            util::invoke_r<result_type>(
                boost::forward<F>(f)
              , boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 )
            );
    };
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5 , args.a6 , args.a7);
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5) , boost::forward<Arg6>(args.a6) , boost::forward<Arg7>(args.a7));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename boost::add_const<Arg0>::type , typename boost::add_const<Arg1>::type , typename boost::add_const<Arg2>::type , typename boost::add_const<Arg3>::type , typename boost::add_const<Arg4>::type , typename boost::add_const<Arg5>::type , typename boost::add_const<Arg6>::type , typename boost::add_const<Arg7>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7> const& args)
    {
        return
            invoke(boost::forward<F>(f)
              , args.a0 , args.a1 , args.a2 , args.a3 , args.a4 , args.a5 , args.a6 , args.a7);
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::detail::add_rvalue_reference<Arg0>::type , typename util::detail::add_rvalue_reference<Arg1>::type , typename util::detail::add_rvalue_reference<Arg2>::type , typename util::detail::add_rvalue_reference<Arg3>::type , typename util::detail::add_rvalue_reference<Arg4>::type , typename util::detail::add_rvalue_reference<Arg5>::type , typename util::detail::add_rvalue_reference<Arg6>::type , typename util::detail::add_rvalue_reference<Arg7>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , boost::forward<Arg0>(args.a0) , boost::forward<Arg1>(args.a1) , boost::forward<Arg2>(args.a2) , boost::forward<Arg3>(args.a3) , boost::forward<Arg4>(args.a4) , boost::forward<Arg5>(args.a5) , boost::forward<Arg6>(args.a6) , boost::forward<Arg7>(args.a7));
    }
}}

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
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args));
    }
    template <typename R, typename F, typename Arg0>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)));
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
              , util::get< 0>(args));
    }
    template <typename F, typename Arg0>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args));
    }
    template <typename F, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type , typename util::add_rvalue_reference<Arg3>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type , typename util::add_rvalue_reference<Arg3>::type , typename util::add_rvalue_reference<Arg4>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type , typename util::add_rvalue_reference<Arg3>::type , typename util::add_rvalue_reference<Arg4>::type , typename util::add_rvalue_reference<Arg5>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args) , util::get< 6>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)) , util::get< 6>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args) , util::get< 6>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type , typename util::add_rvalue_reference<Arg3>::type , typename util::add_rvalue_reference<Arg4>::type , typename util::add_rvalue_reference<Arg5>::type , typename util::add_rvalue_reference<Arg6>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)) , util::get< 6>(boost::move(args)));
    }
}}
namespace hpx { namespace util
{
    
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f
      , hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7> const& args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args) , util::get< 6>(args) , util::get< 7>(args));
    }
    template <typename R, typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    R
    invoke_fused_r(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>))) args)
    {
        return
            invoke_r<R>(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)) , util::get< 6>(boost::move(args)) , util::get< 7>(boost::move(args)));
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
              , util::get< 0>(args) , util::get< 1>(args) , util::get< 2>(args) , util::get< 3>(args) , util::get< 4>(args) , util::get< 5>(args) , util::get< 6>(args) , util::get< 7>(args));
    }
    template <typename F, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE
    typename invoke_result_of<
        F(typename util::add_rvalue_reference<Arg0>::type , typename util::add_rvalue_reference<Arg1>::type , typename util::add_rvalue_reference<Arg2>::type , typename util::add_rvalue_reference<Arg3>::type , typename util::add_rvalue_reference<Arg4>::type , typename util::add_rvalue_reference<Arg5>::type , typename util::add_rvalue_reference<Arg6>::type , typename util::add_rvalue_reference<Arg7>::type)
    >::type
    invoke_fused(BOOST_FWD_REF(F) f, BOOST_RV_REF(HPX_UTIL_STRIP((
        hpx::util::tuple<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>))) args)
    {
        return
            invoke(boost::forward<F>(f)
              , util::get< 0>(boost::move(args)) , util::get< 1>(boost::move(args)) , util::get< 2>(boost::move(args)) , util::get< 3>(boost::move(args)) , util::get< 4>(boost::move(args)) , util::get< 5>(boost::move(args)) , util::get< 6>(boost::move(args)) , util::get< 7>(boost::move(args)));
    }
}}

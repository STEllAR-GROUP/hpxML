// Copyright (c) 2007-2012 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    
    template <typename F>
    bool apply(BOOST_FWD_REF(F) f)
    {
        thread t(boost::forward<F>(f));
        t.detach(); 
        return false; 
    }
    
    
    
    
    
    
    
    
    template <typename F, typename A0> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 )); t.detach(); return false; } template <typename F, typename A0 , typename A1> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 )); t.detach(); return false; } template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18> typename boost::enable_if< traits::supports_result_of<F> , bool >::type apply(BOOST_FWD_REF(F) f, BOOST_FWD_REF(A0) a0 , BOOST_FWD_REF(A1) a1 , BOOST_FWD_REF(A2) a2 , BOOST_FWD_REF(A3) a3 , BOOST_FWD_REF(A4) a4 , BOOST_FWD_REF(A5) a5 , BOOST_FWD_REF(A6) a6 , BOOST_FWD_REF(A7) a7 , BOOST_FWD_REF(A8) a8 , BOOST_FWD_REF(A9) a9 , BOOST_FWD_REF(A10) a10 , BOOST_FWD_REF(A11) a11 , BOOST_FWD_REF(A12) a12 , BOOST_FWD_REF(A13) a13 , BOOST_FWD_REF(A14) a14 , BOOST_FWD_REF(A15) a15 , BOOST_FWD_REF(A16) a16 , BOOST_FWD_REF(A17) a17 , BOOST_FWD_REF(A18) a18) { thread t(boost::forward<F>(f), boost::forward<A0>( a0 ) , boost::forward<A1>( a1 ) , boost::forward<A2>( a2 ) , boost::forward<A3>( a3 ) , boost::forward<A4>( a4 ) , boost::forward<A5>( a5 ) , boost::forward<A6>( a6 ) , boost::forward<A7>( a7 ) , boost::forward<A8>( a8 ) , boost::forward<A9>( a9 ) , boost::forward<A10>( a10 ) , boost::forward<A11>( a11 ) , boost::forward<A12>( a12 ) , boost::forward<A13>( a13 ) , boost::forward<A14>( a14 ) , boost::forward<A15>( a15 ) , boost::forward<A16>( a16 ) , boost::forward<A17>( a17 ) , boost::forward<A18>( a18 )); t.detach(); return false; }
}
namespace hpx
{
    
    
    template <
        typename R
      , typename T0
      , typename Arg0
    >
    bool apply(
        BOOST_RV_REF(HPX_UTIL_STRIP((
            hpx::util::detail::bound_function1<
                R
              , T0
              , Arg0
            >
        ))) bound)
    {
        thread t(boost::move(bound));
        t.detach(); 
        return false; 
    }
    
    
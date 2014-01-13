// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


    
    template <
        typename T
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void
      , typename Enable = void
    >
    struct ctor_fun;
    template <typename T>
    struct ctor_fun<T>
    {
        typedef void result_type;
        void operator()(void ** p) const
        {
            T * t = new T();
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive &, unsigned)
        {}
    };
    template <typename T, typename A0>
    struct ctor_fun<T, A0>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0>
        ctor_fun(Arg0 && arg0)
            : a0(std::forward<Arg0>(arg0))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0;
        }
        typename util::decay<A0>::type a0;
    };
    template <typename T, typename A0 , typename A1>
    struct ctor_fun<T, A0 , A1>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1;
    };
    template <typename T, typename A0 , typename A1 , typename A2>
    struct ctor_fun<T, A0 , A1 , A2>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3>
    struct ctor_fun<T, A0 , A1 , A2 , A3>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12)) , a13(std::forward<Arg13>(arg13))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12) , a13(rhs. a13)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12)) , a13(std::move(rhs. a13))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12; ar & a13;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12; typename util::decay<A13>::type a13;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12)) , a13(std::forward<Arg13>(arg13)) , a14(std::forward<Arg14>(arg14))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12) , a13(rhs. a13) , a14(rhs. a14)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12)) , a13(std::move(rhs. a13)) , a14(std::move(rhs. a14))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12; ar & a13; ar & a14;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12; typename util::decay<A13>::type a13; typename util::decay<A14>::type a14;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12)) , a13(std::forward<Arg13>(arg13)) , a14(std::forward<Arg14>(arg14)) , a15(std::forward<Arg15>(arg15))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12) , a13(rhs. a13) , a14(rhs. a14) , a15(rhs. a15)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12)) , a13(std::move(rhs. a13)) , a14(std::move(rhs. a14)) , a15(std::move(rhs. a15))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12; ar & a13; ar & a14; ar & a15;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12; typename util::decay<A13>::type a13; typename util::decay<A14>::type a14; typename util::decay<A15>::type a15;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12)) , a13(std::forward<Arg13>(arg13)) , a14(std::forward<Arg14>(arg14)) , a15(std::forward<Arg15>(arg15)) , a16(std::forward<Arg16>(arg16))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12) , a13(rhs. a13) , a14(rhs. a14) , a15(rhs. a15) , a16(rhs. a16)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12)) , a13(std::move(rhs. a13)) , a14(std::move(rhs. a14)) , a15(std::move(rhs. a15)) , a16(std::move(rhs. a16))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12; ar & a13; ar & a14; ar & a15; ar & a16;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12; typename util::decay<A13>::type a13; typename util::decay<A14>::type a14; typename util::decay<A15>::type a15; typename util::decay<A16>::type a16;
    };
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    struct ctor_fun<T, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
    {
        typedef void result_type;
        ctor_fun() {}
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17>
        ctor_fun(Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17)
            : a0(std::forward<Arg0>(arg0)) , a1(std::forward<Arg1>(arg1)) , a2(std::forward<Arg2>(arg2)) , a3(std::forward<Arg3>(arg3)) , a4(std::forward<Arg4>(arg4)) , a5(std::forward<Arg5>(arg5)) , a6(std::forward<Arg6>(arg6)) , a7(std::forward<Arg7>(arg7)) , a8(std::forward<Arg8>(arg8)) , a9(std::forward<Arg9>(arg9)) , a10(std::forward<Arg10>(arg10)) , a11(std::forward<Arg11>(arg11)) , a12(std::forward<Arg12>(arg12)) , a13(std::forward<Arg13>(arg13)) , a14(std::forward<Arg14>(arg14)) , a15(std::forward<Arg15>(arg15)) , a16(std::forward<Arg16>(arg16)) , a17(std::forward<Arg17>(arg17))
        {}
        ctor_fun(ctor_fun const & rhs)
            : a0(rhs. a0) , a1(rhs. a1) , a2(rhs. a2) , a3(rhs. a3) , a4(rhs. a4) , a5(rhs. a5) , a6(rhs. a6) , a7(rhs. a7) , a8(rhs. a8) , a9(rhs. a9) , a10(rhs. a10) , a11(rhs. a11) , a12(rhs. a12) , a13(rhs. a13) , a14(rhs. a14) , a15(rhs. a15) , a16(rhs. a16) , a17(rhs. a17)
        {}
        ctor_fun(ctor_fun && rhs)
            : a0(std::move(rhs. a0)) , a1(std::move(rhs. a1)) , a2(std::move(rhs. a2)) , a3(std::move(rhs. a3)) , a4(std::move(rhs. a4)) , a5(std::move(rhs. a5)) , a6(std::move(rhs. a6)) , a7(std::move(rhs. a7)) , a8(std::move(rhs. a8)) , a9(std::move(rhs. a9)) , a10(std::move(rhs. a10)) , a11(std::move(rhs. a11)) , a12(std::move(rhs. a12)) , a13(std::move(rhs. a13)) , a14(std::move(rhs. a14)) , a15(std::move(rhs. a15)) , a16(std::move(rhs. a16)) , a17(std::move(rhs. a17))
        {}
        void operator()(void ** p) const
        {
            T * t = new T(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            *p = t;
        }
        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & a0; ar & a1; ar & a2; ar & a3; ar & a4; ar & a5; ar & a6; ar & a7; ar & a8; ar & a9; ar & a10; ar & a11; ar & a12; ar & a13; ar & a14; ar & a15; ar & a16; ar & a17;
        }
        typename util::decay<A0>::type a0; typename util::decay<A1>::type a1; typename util::decay<A2>::type a2; typename util::decay<A3>::type a3; typename util::decay<A4>::type a4; typename util::decay<A5>::type a5; typename util::decay<A6>::type a6; typename util::decay<A7>::type a7; typename util::decay<A8>::type a8; typename util::decay<A9>::type a9; typename util::decay<A10>::type a10; typename util::decay<A11>::type a11; typename util::decay<A12>::type a12; typename util::decay<A13>::type a13; typename util::decay<A14>::type a14; typename util::decay<A15>::type a15; typename util::decay<A16>::type a16; typename util::decay<A17>::type a17;
    };

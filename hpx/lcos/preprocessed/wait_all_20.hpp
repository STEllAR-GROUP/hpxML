// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <typename T0>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type> >
    when_all(T0 && f0, error_code& ec = throws)
    {
        return when_n(1, std::forward<T0>( f0 ), ec);
    }
    template <typename T0>
    void
    wait_all(T0 && f0, error_code& ec = throws)
    {
        return wait_n(1, std::forward<T0>( f0 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type> >
    when_all(T0 && f0 , T1 && f1, error_code& ec = throws)
    {
        return when_n(2, std::forward<T0>( f0 ) , std::forward<T1>( f1 ), ec);
    }
    template <typename T0 , typename T1>
    void
    wait_all(T0 && f0 , T1 && f1, error_code& ec = throws)
    {
        return wait_n(2, std::forward<T0>( f0 ) , std::forward<T1>( f1 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2, error_code& ec = throws)
    {
        return when_n(3, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ), ec);
    }
    template <typename T0 , typename T1 , typename T2>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2, error_code& ec = throws)
    {
        return wait_n(3, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3, error_code& ec = throws)
    {
        return when_n(4, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3, error_code& ec = throws)
    {
        return wait_n(4, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4, error_code& ec = throws)
    {
        return when_n(5, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4, error_code& ec = throws)
    {
        return wait_n(5, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5, error_code& ec = throws)
    {
        return when_n(6, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5, error_code& ec = throws)
    {
        return wait_n(6, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6, error_code& ec = throws)
    {
        return when_n(7, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6, error_code& ec = throws)
    {
        return wait_n(7, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7, error_code& ec = throws)
    {
        return when_n(8, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7, error_code& ec = throws)
    {
        return wait_n(8, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8, error_code& ec = throws)
    {
        return when_n(9, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8, error_code& ec = throws)
    {
        return wait_n(9, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9, error_code& ec = throws)
    {
        return when_n(10, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9, error_code& ec = throws)
    {
        return wait_n(10, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10, error_code& ec = throws)
    {
        return when_n(11, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10, error_code& ec = throws)
    {
        return wait_n(11, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11, error_code& ec = throws)
    {
        return when_n(12, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11, error_code& ec = throws)
    {
        return wait_n(12, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12, error_code& ec = throws)
    {
        return when_n(13, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12, error_code& ec = throws)
    {
        return wait_n(13, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13, error_code& ec = throws)
    {
        return when_n(14, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13, error_code& ec = throws)
    {
        return wait_n(14, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14, error_code& ec = throws)
    {
        return when_n(15, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14, error_code& ec = throws)
    {
        return wait_n(15, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15, error_code& ec = throws)
    {
        return when_n(16, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15, error_code& ec = throws)
    {
        return wait_n(16, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16, error_code& ec = throws)
    {
        return when_n(17, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16, error_code& ec = throws)
    {
        return wait_n(17, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17, error_code& ec = throws)
    {
        return when_n(18, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17, error_code& ec = throws)
    {
        return wait_n(18, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18, error_code& ec = throws)
    {
        return when_n(19, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18, error_code& ec = throws)
    {
        return wait_n(19, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19, error_code& ec = throws)
    {
        return when_n(20, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19, error_code& ec = throws)
    {
        return wait_n(20, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20, error_code& ec = throws)
    {
        return when_n(21, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20, error_code& ec = throws)
    {
        return wait_n(21, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21, error_code& ec = throws)
    {
        return when_n(22, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ) , std::forward<T21>( f21 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21, error_code& ec = throws)
    {
        return wait_n(22, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ) , std::forward<T21>( f21 ), ec);
    }
}
namespace hpx
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    lcos::unique_future<HPX_STD_TUPLE<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type , typename util::decay<T22>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21 , T22 && f22, error_code& ec = throws)
    {
        return when_n(23, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ) , std::forward<T21>( f21 ) , std::forward<T22>( f22 ), ec);
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    void
    wait_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21 , T22 && f22, error_code& ec = throws)
    {
        return wait_n(23, std::forward<T0>( f0 ) , std::forward<T1>( f1 ) , std::forward<T2>( f2 ) , std::forward<T3>( f3 ) , std::forward<T4>( f4 ) , std::forward<T5>( f5 ) , std::forward<T6>( f6 ) , std::forward<T7>( f7 ) , std::forward<T8>( f8 ) , std::forward<T9>( f9 ) , std::forward<T10>( f10 ) , std::forward<T11>( f11 ) , std::forward<T12>( f12 ) , std::forward<T13>( f13 ) , std::forward<T14>( f14 ) , std::forward<T15>( f15 ) , std::forward<T16>( f16 ) , std::forward<T17>( f17 ) , std::forward<T18>( f18 ) , std::forward<T19>( f19 ) , std::forward<T20>( f20 ) , std::forward<T21>( f21 ) , std::forward<T22>( f22 ), ec);
    }
}

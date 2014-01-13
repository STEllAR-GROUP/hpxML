// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get());
    }
    
    template <typename F0 , typename F1 , typename F2>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2)
    {
        f0.get(); f1.get(); f2.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3)
    {
        f0.get(); f1.get(); f2.get(); f3.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type , typename detail::future_traits<F18>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get() , f18.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get(); f18.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type , typename detail::future_traits<F18>::type , typename detail::future_traits<F19>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get() , f18.get() , f19.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get(); f18.get(); f19.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type , typename detail::future_traits<F18>::type , typename detail::future_traits<F19>::type , typename detail::future_traits<F20>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get() , f18.get() , f19.get() , f20.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get(); f18.get(); f19.get(); f20.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20 , typename F21>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value && boost::is_void< typename detail::future_traits<F21>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type , typename detail::future_traits<F18>::type , typename detail::future_traits<F19>::type , typename detail::future_traits<F20>::type , typename detail::future_traits<F21>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20 , F21 && f21)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get() , f18.get() , f19.get() , f20.get() , f21.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20 , typename F21>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value && boost::is_void< typename detail::future_traits<F21>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20 , F21 && f21)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get(); f18.get(); f19.get(); f20.get(); f21.get();
    }
}}
namespace hpx { namespace lcos
{
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20 , typename F21 , typename F22>
    inline typename boost::enable_if_c<
        !(true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value && boost::is_void< typename detail::future_traits<F21>::type>::value && boost::is_void< typename detail::future_traits<F22>::type>::value)
      , HPX_STD_TUPLE<typename detail::future_traits<F0>::type , typename detail::future_traits<F1>::type , typename detail::future_traits<F2>::type , typename detail::future_traits<F3>::type , typename detail::future_traits<F4>::type , typename detail::future_traits<F5>::type , typename detail::future_traits<F6>::type , typename detail::future_traits<F7>::type , typename detail::future_traits<F8>::type , typename detail::future_traits<F9>::type , typename detail::future_traits<F10>::type , typename detail::future_traits<F11>::type , typename detail::future_traits<F12>::type , typename detail::future_traits<F13>::type , typename detail::future_traits<F14>::type , typename detail::future_traits<F15>::type , typename detail::future_traits<F16>::type , typename detail::future_traits<F17>::type , typename detail::future_traits<F18>::type , typename detail::future_traits<F19>::type , typename detail::future_traits<F20>::type , typename detail::future_traits<F21>::type , typename detail::future_traits<F22>::type>
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20 , F21 && f21 , F22 && f22)
    {
        return HPX_STD_MAKE_TUPLE(f0.get() , f1.get() , f2.get() , f3.get() , f4.get() , f5.get() , f6.get() , f7.get() , f8.get() , f9.get() , f10.get() , f11.get() , f12.get() , f13.get() , f14.get() , f15.get() , f16.get() , f17.get() , f18.get() , f19.get() , f20.get() , f21.get() , f22.get());
    }
    
    template <typename F0 , typename F1 , typename F2 , typename F3 , typename F4 , typename F5 , typename F6 , typename F7 , typename F8 , typename F9 , typename F10 , typename F11 , typename F12 , typename F13 , typename F14 , typename F15 , typename F16 , typename F17 , typename F18 , typename F19 , typename F20 , typename F21 , typename F22>
    inline typename boost::enable_if_c<
        (true && boost::is_void< typename detail::future_traits<F0>::type>::value && boost::is_void< typename detail::future_traits<F1>::type>::value && boost::is_void< typename detail::future_traits<F2>::type>::value && boost::is_void< typename detail::future_traits<F3>::type>::value && boost::is_void< typename detail::future_traits<F4>::type>::value && boost::is_void< typename detail::future_traits<F5>::type>::value && boost::is_void< typename detail::future_traits<F6>::type>::value && boost::is_void< typename detail::future_traits<F7>::type>::value && boost::is_void< typename detail::future_traits<F8>::type>::value && boost::is_void< typename detail::future_traits<F9>::type>::value && boost::is_void< typename detail::future_traits<F10>::type>::value && boost::is_void< typename detail::future_traits<F11>::type>::value && boost::is_void< typename detail::future_traits<F12>::type>::value && boost::is_void< typename detail::future_traits<F13>::type>::value && boost::is_void< typename detail::future_traits<F14>::type>::value && boost::is_void< typename detail::future_traits<F15>::type>::value && boost::is_void< typename detail::future_traits<F16>::type>::value && boost::is_void< typename detail::future_traits<F17>::type>::value && boost::is_void< typename detail::future_traits<F18>::type>::value && boost::is_void< typename detail::future_traits<F19>::type>::value && boost::is_void< typename detail::future_traits<F20>::type>::value && boost::is_void< typename detail::future_traits<F21>::type>::value && boost::is_void< typename detail::future_traits<F22>::type>::value)
      , void
    >::type
    wait(F0 && f0 , F1 && f1 , F2 && f2 , F3 && f3 , F4 && f4 , F5 && f5 , F6 && f6 , F7 && f7 , F8 && f8 , F9 && f9 , F10 && f10 , F11 && f11 , F12 && f12 , F13 && f13 , F14 && f14 , F15 && f15 , F16 && f16 , F17 && f17 , F18 && f18 , F19 && f19 , F20 && f20 , F21 && f21 , F22 && f22)
    {
        f0.get(); f1.get(); f2.get(); f3.get(); f4.get(); f5.get(); f6.get(); f7.get(); f8.get(); f9.get(); f10.get(); f11.get(); f12.get(); f13.get(); f14.get(); f15.get(); f16.get(); f17.get(); f18.get(); f19.get(); f20.get(); f21.get(); f22.get();
    }
}}

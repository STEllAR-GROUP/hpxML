// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace lcos
{
    
    template <typename T0>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type> >
    when_all(T0 && f0)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type> >
    when_all(T0 && f0 , T1 && f1)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17) , detail::when_acquire_future<T18>()(f18));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17) , detail::when_acquire_future<T18>()(f18) , detail::when_acquire_future<T19>()(f19));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17) , detail::when_acquire_future<T18>()(f18) , detail::when_acquire_future<T19>()(f19) , detail::when_acquire_future<T20>()(f20));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17) , detail::when_acquire_future<T18>()(f18) , detail::when_acquire_future<T19>()(f19) , detail::when_acquire_future<T20>()(f20) , detail::when_acquire_future<T21>()(f21));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}
namespace hpx { namespace lcos
{
    
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    lcos::future<hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type , typename util::decay<T22>::type> >
    when_all(T0 && f0 , T1 && f1 , T2 && f2 , T3 && f3 , T4 && f4 , T5 && f5 , T6 && f6 , T7 && f7 , T8 && f8 , T9 && f9 , T10 && f10 , T11 && f11 , T12 && f12 , T13 && f13 , T14 && f14 , T15 && f15 , T16 && f16 , T17 && f17 , T18 && f18 , T19 && f19 , T20 && f20 , T21 && f21 , T22 && f22)
    {
        typedef hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type , typename util::decay<T20>::type , typename util::decay<T21>::type , typename util::decay<T22>::type>
            result_type;
        typedef detail::when_all_frame<result_type> frame_type;
        result_type values(detail::when_acquire_future<T0>()(f0) , detail::when_acquire_future<T1>()(f1) , detail::when_acquire_future<T2>()(f2) , detail::when_acquire_future<T3>()(f3) , detail::when_acquire_future<T4>()(f4) , detail::when_acquire_future<T5>()(f5) , detail::when_acquire_future<T6>()(f6) , detail::when_acquire_future<T7>()(f7) , detail::when_acquire_future<T8>()(f8) , detail::when_acquire_future<T9>()(f9) , detail::when_acquire_future<T10>()(f10) , detail::when_acquire_future<T11>()(f11) , detail::when_acquire_future<T12>()(f12) , detail::when_acquire_future<T13>()(f13) , detail::when_acquire_future<T14>()(f14) , detail::when_acquire_future<T15>()(f15) , detail::when_acquire_future<T16>()(f16) , detail::when_acquire_future<T17>()(f17) , detail::when_acquire_future<T18>()(f18) , detail::when_acquire_future<T19>()(f19) , detail::when_acquire_future<T20>()(f20) , detail::when_acquire_future<T21>()(f21) , detail::when_acquire_future<T22>()(f22));
        boost::intrusive_ptr<frame_type> p(new frame_type(std::move(values)));
        p->await();
        using traits::future_access;
        return future_access<typename frame_type::type>::create(std::move(p));
    }
}}

// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0>
    >::result_type> invoke_when_ready(F&& f, T0 && v0)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2 , T3>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2 , T3 , T4>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2 , T3 , T4 , T5>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4 , T5 && v5)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 ) , std::forward<T5>( v5 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2 , T3 , T4 , T5 , T6>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4 , T5 && v5 , T6 && v6)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 ) , std::forward<T5>( v5 ) , std::forward<T6>( v6 )));
    }
}}}}
namespace hpx { namespace lcos { namespace local { namespace detail
{
    
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    future<typename when_ready<
        typename util::decay<F>::type
      , util::tuple<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7>
    >::result_type> invoke_when_ready(F&& f, T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4 , T5 && v5 , T6 && v6 , T7 && v7)
    {
        return invoke_fused_when_ready(std::forward<F>(f),
            util::forward_as_tuple(std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 ) , std::forward<T5>( v5 ) , std::forward<T6>( v6 ) , std::forward<T7>( v7 )));
    }
}}}}

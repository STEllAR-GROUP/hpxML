//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_TRAITS_IS_FUTURE_APR_20_2012_0536PM)
#define HPX_TRAITS_IS_FUTURE_APR_20_2012_0536PM

#include <hpx/traits.hpp>

#include <boost/mpl/bool.hpp>

namespace hpx { namespace lcos
{
    template <typename Result> class future;
    
    template <typename R> class unique_future;
    template <typename R> class shared_future;
}}

namespace hpx { namespace traits
{
    template <typename Future, typename Enable>
    struct is_future
      : boost::mpl::false_
    {};

#if defined(HPX_ENABLE_DEPRECATED_FUTURE)
    template <typename Result>
    struct is_future<lcos::future<Result> >
      : boost::mpl::true_
    {};
#endif

    template <typename R>
    struct is_future<lcos::unique_future<R> >
      : boost::mpl::true_
    {};

    template <typename R>
    struct is_future<lcos::shared_future<R> >
      : boost::mpl::true_
    {};
}}

#endif


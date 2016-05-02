//  Copyright (c) 2013-2015 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_TRAITS_IS_PLACEHOLDER_HPP
#define HPX_TRAITS_IS_PLACEHOLDER_HPP

#include <hpx/config.hpp>

#include <boost/bind/arg.hpp>
#include <boost/type_traits/integral_constant.hpp>

#ifdef HPX_HAVE_CXX11_STD_IS_PLACEHOLDER
#include <functional>
#endif

namespace hpx { namespace traits
{
    template <typename T>
    struct is_placeholder
#ifdef HPX_HAVE_CXX11_STD_IS_PLACEHOLDER
      : boost::integral_constant<
            int,
            std::is_placeholder<T>::value != 0
              ? std::is_placeholder<T>::value
              : boost::is_placeholder<T>::value
        >
#else
      : boost::is_placeholder<T>
#endif
    {};

    template <typename T>
    struct is_placeholder<T const>
      : is_placeholder<T>
    {};
}}

#endif /*HPX_TRAITS_IS_PLACEHOLDER_HPP*/

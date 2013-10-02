//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_UTIL_REMOVE_REFERENCE_HPP
#define HPX_UTIL_REMOVE_REFERENCE_HPP

#include <boost/move/move.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace hpx { namespace util
{
    template <typename T>
    struct remove_reference
    {
        typedef typename boost::remove_reference<T>::type type;
    };

    template <typename T>
    struct remove_reference<BOOST_RV_REF(T)>
    {
        typedef T type;
    };
}}

#endif

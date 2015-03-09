//  Copyright (c) 2014 Thomas Heller
//  Copyright (c) 2014-2015 Anton Bikineev
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_SERIALIZATION_INTRUSIVE_PTR_HPP
#define HPX_SERIALIZATION_INTRUSIVE_PTR_HPP

#include <hpx/runtime/serialization/detail/pointer.hpp>

namespace hpx { namespace serialization {

    template <typename T>
    void serialize(input_archive & ar, boost::intrusive_ptr<T> & ptr, unsigned n)
    {
        detail::serialize_pointer(ar, ptr, n);
    }

    template <typename T>
    void serialize(output_archive & ar, boost::intrusive_ptr<T> ptr, unsigned n)
    {
        detail::serialize_pointer(ar, ptr, n);
    }
}}

#endif

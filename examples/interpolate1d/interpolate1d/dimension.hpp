//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_DIMENSION_AUG_04_2011_0719PM)
#define HPX_DIMENSION_AUG_04_2011_0719PM

#include <hpx/hpx_fwd.hpp>

#include <boost/serialization/serialization.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace interpolate1d
{
    struct dimension
    {
        std::size_t offset_;    // lower index
        std::size_t count_;    // upper index
        std::size_t size_;         // overall size of this dimension
    };
}

///////////////////////////////////////////////////////////////////////////////
// non-intrusive serialization
namespace boost { namespace serialization
{
    template <typename Archive>
    void serialize(Archive&, interpolate1d::dimension&, unsigned int const);
}}

#endif



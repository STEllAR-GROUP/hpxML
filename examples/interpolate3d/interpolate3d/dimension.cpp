//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include "dimension.hpp"

namespace boost { namespace serialization
{
    ///////////////////////////////////////////////////////////////////////////////
    // implement the serialization functions
    template <typename Archive>
    void serialize(Archive& ar, interpolate3d::dimension& dim, unsigned int const)
    {
        ar & dim.offset_ & dim.count_ & dim.size_;
    }

    ///////////////////////////////////////////////////////////////////////////
    // explicit instantiation for the correct archive types
#if HPX_USE_PORTABLE_ARCHIVES != 0
    template HPX_COMPONENT_EXPORT void
    serialize(hpx::util::portable_binary_iarchive&, interpolate3d::dimension&,
        unsigned int const);
    template HPX_COMPONENT_EXPORT void
    serialize(hpx::util::portable_binary_oarchive&, interpolate3d::dimension&,
        unsigned int const);
#else
    template HPX_COMPONENT_EXPORT void
    serialize(boost::archive::binary_iarchive&, interpolate3d::dimension&,
        unsigned int const);
    template HPX_COMPONENT_EXPORT void
    serialize(boost::archive::binary_oarchive&, interpolate3d::dimension&,
        unsigned int const);
#endif
}}



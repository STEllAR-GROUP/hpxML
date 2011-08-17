//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_VERSION_JUN_26_2008_0831PM)
#define HPX_VERSION_JUN_26_2008_0831PM

#include <string>

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#include <hpx/config/export_definitions.hpp>

///////////////////////////////////////////////////////////////////////////////
//  The version of HPX
//
//  HPX_VERSION_FULL & 0x0000FF is the sub-minor version
//  HPX_VERSION_FULL & 0x00FF00 is the minor version
//  HPX_VERSION_FULL & 0xFF0000 is the major version
//
#define HPX_VERSION_FULL         0x000600

#define HPX_VERSION_MAJOR        0
#define HPX_VERSION_MINOR        6
#define HPX_VERSION_SUBMINOR     0

#define HPX_VERSION_DATE         20110811

#if !defined(HPX_AGAS_VERSION)
    #define HPX_AGAS_VERSION 0x20
#endif

#define HPX_VERSION_TAG          "-rc1"

#if !defined(HPX_SVN_REVISION)
    #define HPX_SVN_REVISION     "$Revision$"
#endif

namespace hpx
{
    // Returns the major HPX version.
    HPX_EXPORT boost::uint8_t major_version();

    // Returns the minor HPX version. 
    HPX_EXPORT boost::uint8_t minor_version();

    // Returns the subminor/patchlevel HPX version. 
    HPX_EXPORT boost::uint8_t subminor_version();

    // Returns the full HPX version.
    HPX_EXPORT boost::uint32_t full_version();

    // Returns the AGAS subsystem version. 
    HPX_EXPORT boost::uint8_t agas_version();

    // Returns the tag.
    HPX_EXPORT std::string tag();
}

#endif


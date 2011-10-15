//  Copyright (c) 2007-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_UTIL_MAP_HOSTNAMES_AUG_29_2011_1257PM)
#define HPX_UTIL_MAP_HOSTNAMES_AUG_29_2011_1257PM

#include <hpx/hpx_fwd.hpp>

#include <map>
#include <iostream>
#include <fstream>

namespace hpx { namespace util
{
    ///////////////////////////////////////////////////////////////////////////
    // Try to map a given host name based on the list of mappings read from a 
    // file
    struct HPX_EXPORT map_hostnames
    {
        map_hostnames(bool debug = false) 
          : debug_(debug) 
        {}

        void use_suffix(std::string const& suffix)
        {
            suffix_ = suffix;
        }

        void use_prefix(std::string const& prefix)
        {
            prefix_ = prefix;
        }

        std::string map(std::string const& host_name, boost::uint16_t port) const;

      private:
        std::string suffix_;
        std::string prefix_;
        bool debug_;
    };
}}

#endif

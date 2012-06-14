//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_6E16120B_C251_4FFE_A659_FDA2986A7FE3)
#define HPX_6E16120B_C251_4FFE_A659_FDA2986A7FE3

#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/point.hpp"

namespace gtc { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    struct point : hpx::components::stub_base<server::point>
    {
        static hpx::lcos::future<void>
        setup_async(hpx::naming::id_type const& gid,std::size_t numberpe,std::size_t mype,
                    std::vector<hpx::naming::id_type> const& point_components)
        {
            typedef server::point::setup_action action_type;
            return hpx::async<action_type>(gid,numberpe,mype,point_components);
        }

        static void setup(hpx::naming::id_type const& gid,std::size_t numberpe,std::size_t mype,
                          std::vector<hpx::naming::id_type> const& point_components)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the future.
            setup_async(gid,numberpe,mype,point_components).get();
        }

        static hpx::lcos::future<void>
        chargei_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::chargei_action action_type;
            return hpx::async<action_type>(gid);
        }

        static void chargei(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the future.
            chargei_async(gid).get();
        }
    };
}}

#endif


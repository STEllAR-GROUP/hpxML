//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_85F90266_2241_4547_A2A5_2D1E88242D14)
#define HPX_85F90266_2241_4547_A2A5_2D1E88242D14

#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/point.hpp"

namespace bfs { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    struct point : hpx::components::stub_base<server::point>
    {
        // Read the graph
        static hpx::lcos::promise<void>
        init_async(hpx::naming::id_type const& gid,std::size_t objectid,std::size_t grainsize,
            std::size_t max_num_neighbors,std::vector<std::size_t> const& nodefile,
                                          std::vector<std::size_t> const& neighborfile)
        {
            typedef server::point::init_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,objectid,grainsize,
                max_num_neighbors,nodefile,neighborfile);
        }

        // Read the graph
        static void init(hpx::naming::id_type const& gid,std::size_t objectid,std::size_t grainsize,
            std::size_t max_num_neighbors,std::vector<std::size_t> const& nodefile,
                                          std::vector<std::size_t> const& neighborfile)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            init_async(gid,objectid,grainsize,max_num_neighbors,nodefile,neighborfile).get();
        }

        /// Traverse the graph. 
        static hpx::lcos::promise<std::vector<std::size_t> >
        traverse_async(hpx::naming::id_type const& gid,std::size_t level,
            std::size_t parent)
        {
            typedef server::point::traverse_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,level,parent);
        }

        /// Traverse the graph. 
        static std::vector<std::size_t>
        traverse(hpx::naming::id_type const& gid,std::size_t level,
            std::size_t parent)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            return traverse_async(gid,level,parent).get();
        }
    };
}}

#endif


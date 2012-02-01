//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_85F90266_2241_4547_A2A5_2D1E88242D14)
#define HPX_85F90266_2241_4547_A2A5_2D1E88242D14

#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/point.hpp"

namespace graph500 { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    struct point : hpx::components::stub_base<server::point>
    {
        // Read the graph
        static hpx::lcos::promise<void>
        init_async(hpx::naming::id_type const& gid,std::size_t objectid,std::size_t scale,
                   std::size_t number_partitions,std::vector<hpx::naming::id_type> const& point_components)
        {
            typedef server::point::init_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,objectid,scale,
                                             number_partitions,point_components);
        }

        // Read the graph
        static void init(hpx::naming::id_type const& gid,std::size_t objectid,std::size_t scale,
                         std::size_t number_partitions,
                         std::vector<hpx::naming::id_type> const& point_components)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            init_async(gid,objectid,scale,number_partitions,point_components).get();
        }

        static hpx::lcos::promise<void>
        bfs_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::bfs_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static void bfs(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            bfs_async(gid).get();
        }

        static hpx::lcos::promise<void>
        merge_graph_async(hpx::naming::id_type const& gid,
                          std::size_t parent,
                          std::vector<std::size_t> const& neighbors)
        {
            typedef server::point::merge_graph_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,parent,neighbors);
        }

        static void merge_graph(hpx::naming::id_type const& gid,
                          std::size_t parent,
                          std::vector<std::size_t> const& neighbors)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            merge_graph_async(gid,parent,neighbors).get();
        }

        static hpx::lcos::promise<void>
        reset_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::reset_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static void reset(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            reset_async(gid).get();
        }
    };
}}

#endif


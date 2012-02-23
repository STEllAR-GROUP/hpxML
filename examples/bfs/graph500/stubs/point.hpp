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
                   std::size_t number_partitions,double overlap)
        {
            typedef server::point::init_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,objectid,scale,
                                             number_partitions,overlap);
        }

        // Read the graph
        static void init(hpx::naming::id_type const& gid,std::size_t objectid,std::size_t scale,
                         std::size_t number_partitions,double overlap)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            init_async(gid,objectid,scale,number_partitions,overlap).get();
        }

        static hpx::lcos::promise<void>
        root_async(hpx::naming::id_type const& gid,std::vector<int64_t> const& bfs_roots)
        {
            typedef server::point::root_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,bfs_roots);
        }

        static void root(hpx::naming::id_type const& gid,std::vector<int64_t> const& bfs_roots)
        {
            root_async(gid,bfs_roots).get();
        }

        static hpx::lcos::promise<void>
        receive_duplicates_async(hpx::naming::id_type const& gid,
                                 int64_t j,
                                 std::vector<hpx::naming::id_type> const& duplicate_components)
        {
            typedef server::point::receive_duplicates_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,j,duplicate_components);
        }

        static void receive_duplicates(hpx::naming::id_type const& gid,
                                       int64_t j,
                                       std::vector<hpx::naming::id_type> const& duplicate_components)
        {
            receive_duplicates_async(gid,j,duplicate_components).get();
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
        resolve_conflict_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::resolve_conflict_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static void resolve_conflict(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            resolve_conflict_async(gid).get();
        }

        static hpx::lcos::promise< int >
        distributed_validate_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::distributed_validate_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static int distributed_validate(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            return distributed_validate_async(gid).get();
        }

        static hpx::lcos::promise< std::vector<int64_t> >
        get_numedges_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_numedges_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<int64_t> get_numedges(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            return get_numedges_async(gid).get();
        }

        static hpx::lcos::promise< bool >
        has_edge_async(hpx::naming::id_type const& gid,int64_t edge)
        {
            typedef server::point::has_edge_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,edge);
        }

        static bool has_edge(hpx::naming::id_type const& gid,int64_t edge)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return has_edge_async(gid,edge).get();
        }

        static hpx::lcos::promise< resolvedata >
        get_parent_async(hpx::naming::id_type const& gid,int64_t edge)
        {
            typedef server::point::get_parent_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,edge);
        }

        static resolvedata get_parent(hpx::naming::id_type const& gid,int64_t edge)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_parent_async(gid,edge).get();
        }
    };
}}

#endif


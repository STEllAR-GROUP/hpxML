//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_EXAMPLE_BFS_STUBS_CONCURRENT_BGL_GRAPH_JAN_02_2012_0529PM)
#define HPX_EXAMPLE_BFS_STUBS_CONCURRENT_BGL_GRAPH_JAN_02_2012_0529PM

#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/concurrent_bgl_graph.hpp"

namespace bfs { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    struct concurrent_bgl_graph 
      : hpx::components::stub_base<server::concurrent_bgl_graph>
    {
        // initialize the graph
        static hpx::lcos::promise<void>
        init_async(hpx::naming::id_type const& gid,
            std::size_t idx, std::size_t grainsize,
            std::vector<std::pair<std::size_t, std::size_t> > const& edgelist)
        {
            typedef server::concurrent_bgl_graph::init_action action_type;
            return hpx::lcos::eager_future<action_type>(gid, idx, grainsize,
                edgelist);
        }

        static void init(hpx::naming::id_type const& gid,
            std::size_t idx, std::size_t grainsize,
            std::vector<std::pair<std::size_t, std::size_t> > const& edgelist)
        {
            init_async(gid, idx, grainsize, edgelist).get();
        }

        /// Perform a BFS on the graph.
        static hpx::lcos::promise<double>
        bfs_async(hpx::naming::id_type const& gid, std::size_t root)
        {
            typedef server::concurrent_bgl_graph::bfs_action action_type;
            return hpx::lcos::eager_future<action_type>(gid, root);
        }

        static double
        bfs(hpx::naming::id_type const& gid, std::size_t root)
        {
            return bfs_async(gid, root).get();
        }

        /// validate the BFS on the graph.
        static hpx::lcos::promise<std::vector<std::size_t> >
        get_parents_async(hpx::naming::id_type const& gid)
        {
            typedef server::concurrent_bgl_graph::get_parents_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<std::size_t>
        get_parents(hpx::naming::id_type const& gid)
        {
            return get_parents_async(gid).get();
        }

        /// Reset for the next BFS
        static hpx::lcos::promise<void>
        reset_async(hpx::naming::id_type const& gid)
        {
            typedef server::concurrent_bgl_graph::reset_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static void
        reset(hpx::naming::id_type const& gid)
        {
            reset_async(gid).get();
        }
    };
}}

#endif


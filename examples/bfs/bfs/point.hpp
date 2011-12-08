//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_68F602E3_C235_4660_AEAC_D5BD7AEC4805)
#define HPX_68F602E3_C235_4660_AEAC_D5BD7AEC4805

#include <hpx/runtime/components/client_base.hpp>

#include "stubs/point.hpp"

namespace bfs
{
    ///////////////////////////////////////////////////////////////////////////
    /// The client side representation of a \a bfs::server::point components.
    class point : public hpx::components::client_base<point, stubs::point>
    {
        typedef hpx::components::client_base<point, stubs::point>
            base_type;

    public:
        /// Default construct an empty client side representation (not
        /// connected to any existing component).
        point()
        {}

        /// Create a client side representation for the existing
        /// \a bfs::server::point instance with the given GID.
        point(hpx::naming::id_type const& gid)
          : base_type(gid)
        {}

        ///////////////////////////////////////////////////////////////////////
        // Exposed functionality of this component.

        /// Kernel 1
        hpx::lcos::promise<void> init_async(std::size_t objectid,
            std::size_t max_num_neighbors,std::string const& graphfile)
        {
            BOOST_ASSERT(gid_);
            return this->base_type::init_async(gid_,objectid,max_num_neighbors,
                graphfile);
        }

        /// Kernel 1
        void init(std::size_t objectid,std::size_t max_num_neighbors,
            std::string const& graphfile)
        {
            BOOST_ASSERT(gid_);
            this->base_type::init_async(gid_,objectid,max_num_neighbors,
                graphfile);
        }

        // Read in the graph
        hpx::lcos::promise<void> read_async(std::size_t objectid,
            std::size_t grainsize,std::size_t max_num_neighbors,std::string const& graphfile)
        {
            BOOST_ASSERT(gid_);
            return this->base_type::read_async(gid_,objectid,grainsize,
                                                max_num_neighbors, graphfile);
        }

        // Read in the graph
        void read(std::size_t objectid,std::size_t grainsize,
            std::size_t max_num_neighbors, std::string const& graphfile)
        {
            BOOST_ASSERT(gid_);
            this->base_type::read_async(gid_,objectid, grainsize,
                                        max_num_neighbors, graphfile);
        }

        /// Traverse the graph. 
        hpx::lcos::promise<std::vector<std::size_t> >
        traverse_async(std::size_t level, std::size_t parent)
        {
            BOOST_ASSERT(gid_);
            return this->base_type::traverse_async(gid_,level,parent);
        }

        /// Traverse the graph. 
        std::vector<std::size_t> traverse(std::size_t level,std::size_t parent)
        {
            BOOST_ASSERT(gid_);
            return this->base_type::traverse(gid_,level,parent);
        }
    };
}

#endif


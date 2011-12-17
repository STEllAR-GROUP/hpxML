//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_69F602E3_C235_4660_AEAC_D5BD7AEC4805)
#define HPX_69F602E3_C235_4660_AEAC_D5BD7AEC4805

#include <hpx/runtime/components/client_base.hpp>

#include "stubs/point_tm.hpp"

namespace bfs_tm
{
    ///////////////////////////////////////////////////////////////////////////
    /// The client side representation of a \a bfs_tm::server::point components.
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
        /// \a bfs_tm::server::point instance with the given GID.
        point(hpx::naming::id_type const& gid)
          : base_type(gid)
        {}

        ///////////////////////////////////////////////////////////////////////
        // Exposed functionality of this component.

        void manager_async(std::size_t level,std::size_t edge,
                           std::vector<std::size_t> const& neighbors)
        {
            BOOST_ASSERT(gid_);
            this->base_type::manager_async(gid_,level,edge,neighbors);
        }

        void manager(std::size_t level,std::size_t edge,
                    std::vector<std::size_t> const& neighbors)
        {
            BOOST_ASSERT(gid_);
            this->base_type::manager_async(gid_,level,edge,neighbors);
        }

        hpx::lcos::promise<void> init_async(std::size_t objectid,
                 boost::numeric::ublas::mapped_vector<std::size_t> const& index,
                 std::vector<hpx::naming::id_type> const& points_components)
        {
            BOOST_ASSERT(gid_);
            return this->base_type::init_async(gid_,objectid,index,points_components);
        }

        void init(std::size_t objectid,
                  boost::numeric::ublas::mapped_vector<std::size_t> const& index,
                  std::vector<hpx::naming::id_type> const& points_components)
        {
            BOOST_ASSERT(gid_);
            this->base_type::init_async(gid_,objectid,index,points_components);
        }
    };
}

#endif


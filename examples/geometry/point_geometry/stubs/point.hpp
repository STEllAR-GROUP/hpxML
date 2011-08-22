//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2007-2011 Matthew Anderson
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_STUBS_POINT)
#define HPX_COMPONENTS_STUBS_POINT

#include <hpx/hpx.hpp>
#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/point.hpp"

namespace hpx { namespace geometry { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    /// The \a stubs#point class is the client side representation of all
    /// \a server#point components
    struct point : components::stub_base<server::point>
    {
        ///////////////////////////////////////////////////////////////////////
        // exposed functionality of this component

        /// Initialize the server#point instance with the given \a gid
        static lcos::future_value<void> 
        init_async(naming::id_type gid, double xmin, double xmax,double ymin,double ymax,double velx,double vely,std::size_t numpoints,std::size_t objectid) 
        {
            typedef server::point::init_action action_type;
            return lcos::eager_future<action_type>(gid,xmin,xmax,ymin,ymax,velx,vely,numpoints,objectid);
        }

        static void init(naming::id_type const& gid,double xmin, double xmax,double ymin,double ymax,double velx, double vely,std::size_t numpoints,std::size_t objectid) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            init_async(gid,xmin,xmax,ymin,ymax,velx,vely,numpoints,objectid).get();
        }

        static lcos::future_value<int> 
        search_async(naming::id_type gid, std::vector<hpx::naming::id_type> const& search_objects) 
        {
            typedef server::point::search_action action_type;
            return lcos::eager_future<action_type>(gid, search_objects);
        }

        static int search(naming::id_type const& gid, std::vector<hpx::naming::id_type> const& search_objects) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            return search_async(gid, search_objects).get();
        }

        static lcos::future_value<polygon_type> 
        get_poly_async(naming::id_type gid) 
        {
            typedef server::point::get_poly_action action_type;
            return lcos::eager_future<action_type>(gid);
        }

        static polygon_type get_poly(naming::id_type const& gid) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            return get_poly_async(gid).get();
        }

        static lcos::future_value<void> 
        move_async(naming::id_type gid,double dt) 
        {
            typedef server::point::move_action action_type;
            return lcos::eager_future<action_type>(gid,dt);
        }

        static lcos::future_value<void> 
        enforce_async(naming::id_type gid,std::vector<hpx::naming::id_type> const& master_gids) 
        {
            typedef server::point::enforce_action action_type;
            return lcos::eager_future<action_type>(gid,master_gids);
        }

        static lcos::future_value<hpx::geometry::server::vertex_data> 
        iterate_async(naming::id_type gid,hpx::geometry::server::vertex_data slave,
                        std::size_t master_vertex) 
        {
            typedef server::point::iterate_action action_type;
            return lcos::eager_future<action_type>(gid, slave,master_vertex);
        }

        static void move(naming::id_type const& gid,double dt) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            move_async(gid,dt).get();
        }

        static void enforce(naming::id_type const& gid,std::vector<hpx::naming::id_type> const& master_gids) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            enforce_async(gid,master_gids).get();
        }

        static hpx::geometry::server::vertex_data iterate(naming::id_type const& gid,
                                   hpx::geometry::server::vertex_data slave,std::size_t master_vertex) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            return iterate_async(gid,slave,master_vertex).get();
        }

        /// Query the current coordinate values of the server#point 
        /// instance with the given \a gid. 
        static lcos::future_value<double> 
        get_X_async(naming::id_type const& gid) 
        {
            // Create an eager_future, execute the required action,
            // we simply return the initialized eager_future, the caller needs
            // to call get() on the return value to obtain the result
            typedef server::point::get_X_action action_type;
            return lcos::eager_future<action_type>(gid);
        }
        static lcos::future_value<double> 
        get_Y_async(naming::id_type const& gid) 
        {
            // Create an eager_future, execute the required action,
            // we simply return the initialized eager_future, the caller needs
            // to call get() on the return value to obtain the result
            typedef server::point::get_Y_action action_type;
            return lcos::eager_future<action_type>(gid);
        }

        static double get_X(naming::id_type const& gid) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            return get_X_async(gid).get();
        }
        static double get_Y(naming::id_type const& gid) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            return get_Y_async(gid).get();
        }

        /// Modify the current coordinate values of the server#point 
        /// instance with the given \a gid. 
        static lcos::future_value<void> 
        set_X_async(naming::id_type const& gid, double x) 
        {
            // Create an eager_future, execute the required action,
            // we simply return the initialized eager_future, the caller needs
            // to call get() on the return value to obtain the result
            typedef server::point::set_X_action action_type;
            return lcos::eager_future<action_type>(gid, x);
        }
        static lcos::future_value<void> 
        set_Y_async(naming::id_type const& gid, double y) 
        {
            // Create an eager_future, execute the required action,
            // we simply return the initialized eager_future, the caller needs
            // to call get() on the return value to obtain the result
            typedef server::point::set_Y_action action_type;
            return lcos::eager_future<action_type>(gid, y);
        }

        static void set_X(naming::id_type const& gid, double x) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            set_X_async(gid, x).get();
        }
        static void set_Y(naming::id_type const& gid, double y) 
        {
            // The following get yields control while the action above 
            // is executed and the result is returned to the future_value
            set_Y_async(gid, y).get();
        }
    };

}}}

#endif

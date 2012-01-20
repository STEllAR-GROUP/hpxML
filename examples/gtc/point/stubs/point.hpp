//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_STUBS_POINT)
#define HPX_COMPONENTS_STUBS_POINT

#include <hpx/hpx.hpp>
#include <hpx/runtime/components/stubs/stub_base.hpp>

#include "../server/point.hpp"

namespace gtc { namespace stubs
{
    ///////////////////////////////////////////////////////////////////////////
    struct point : hpx::components::stub_base<server::point>
    {
        ///////////////////////////////////////////////////////////////////////
        // Exposed functionality of this component.

        /// Initialize the \a gtc::server::point instance with the
        /// given point file. 
        static hpx::lcos::promise<void>
        init_async(hpx::naming::id_type gid,std::size_t objectid,
            parameter const& par)
        {
            typedef server::point::init_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,objectid,par);
        }

        /// Initialize the \a gtc::server::point instance with the
        /// given point file.  
        static void init(hpx::naming::id_type const& gid,std::size_t objectid,
                         parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            init_async(gid,objectid,par).get();
        }

        static hpx::lcos::promise<void>
        load_async(hpx::naming::id_type gid,std::size_t objectid,
            parameter const& par)
        {
            typedef server::point::load_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,objectid,par);
        }

        static void load(hpx::naming::id_type const& gid,std::size_t objectid,
                         parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            load_async(gid,objectid,par).get();
        }

        static hpx::lcos::promise<void>
        chargei_async(hpx::naming::id_type const& gid,
           std::size_t istep,std::vector<hpx::naming::id_type> const& point_components,
            hpx::components::gtc::parameter const& par)
        {
            typedef server::point::chargei_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,istep,
                point_components,par);
        }

        static void chargei(hpx::naming::id_type const& gid,
               std::size_t istep,std::vector<hpx::naming::id_type> const& point_components,
               hpx::components::gtc::parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            chargei_async(gid,istep,point_components,par).get();
        }

        static hpx::lcos::promise< std::valarray<double> >
        get_densityi_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_densityi_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::valarray<double> get_densityi(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_densityi_async(gid).get();
        }

        static hpx::lcos::promise< std::vector<double> >
        get_zonali_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_zonali_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<double> get_zonali(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_zonali_async(gid).get();
        }

        static hpx::lcos::promise<void>
        smooth_async(hpx::naming::id_type const& gid,
           std::size_t iflag,std::vector<hpx::naming::id_type> const& point_components,
            std::size_t idiag,
            hpx::components::gtc::parameter const& par)
        {
            typedef server::point::smooth_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,iflag,
                point_components,idiag,par);
        }

        static void smooth(hpx::naming::id_type const& gid,
               std::size_t iflag,std::vector<hpx::naming::id_type> const& point_components,
               std::size_t idiag,
               hpx::components::gtc::parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            smooth_async(gid,iflag,point_components,idiag,par).get();
        }

        static hpx::lcos::promise< std::valarray<double> >
        get_phi_async(hpx::naming::id_type const& gid,std::size_t depth)
        {
            typedef server::point::get_phi_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,depth);
        }

        static std::valarray<double> get_phi(hpx::naming::id_type const& gid,std::size_t depth)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_phi_async(gid,depth).get();
        }

        static hpx::lcos::promise< std::vector<double> >
        get_eachzeta_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_eachzeta_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<double> get_eachzeta(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_eachzeta_async(gid).get();
        }

        static hpx::lcos::promise<void>
        field_async(hpx::naming::id_type const& gid,
           std::vector<hpx::naming::id_type> const& point_components,
            hpx::components::gtc::parameter const& par)
        {
            typedef server::point::field_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,
                point_components,par);
        }

        static void field(hpx::naming::id_type const& gid,
               std::vector<hpx::naming::id_type> const& point_components,
               hpx::components::gtc::parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            field_async(gid,point_components,par).get();
        }

        static hpx::lcos::promise< std::valarray<double> >
        get_evector_async(hpx::naming::id_type const& gid,std::size_t depth,std::size_t extent)
        {
            typedef server::point::get_evector_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,depth,extent);
        }

        static std::valarray<double> get_evector(hpx::naming::id_type const& gid,std::size_t depth,std::size_t extent)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_evector_async(gid,depth,extent).get();
        }

        static hpx::lcos::promise<void>
        pushi_async(hpx::naming::id_type const& gid,std::size_t irk,std::size_t istep,std::size_t idiag,
           std::vector<hpx::naming::id_type> const& point_components,
            hpx::components::gtc::parameter const& par)
        {
            typedef server::point::pushi_action action_type;
            return hpx::lcos::eager_future<action_type>(gid,irk,istep,idiag,
                point_components,par);
        }

        static void pushi(hpx::naming::id_type const& gid,std::size_t irk,std::size_t istep,std::size_t idiag,
               std::vector<hpx::naming::id_type> const& point_components,
               hpx::components::gtc::parameter const& par)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise.
            pushi_async(gid,irk,istep,idiag,point_components,par).get();
        }

        static hpx::lcos::promise< std::vector<double> >
        get_dden_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_dden_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<double> get_dden(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_dden_async(gid).get();
        }

        static hpx::lcos::promise< std::vector<double> >
        get_dtem_async(hpx::naming::id_type const& gid)
        {
            typedef server::point::get_dtem_action action_type;
            return hpx::lcos::eager_future<action_type>(gid);
        }

        static std::vector<double> get_dtem(hpx::naming::id_type const& gid)
        {
            // The following get yields control while the action above
            // is executed and the result is returned to the promise
            return get_dtem_async(gid).get();
        }

    };
}}

#endif


//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_E7A92B7F_BA91_423C_ADB1_B88A0A48D03E)
#define HPX_E7A92B7F_BA91_423C_ADB1_B88A0A48D03E

#include <cmath>

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/runtime/actions/component_action.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace gtc { namespace server
{

    ///////////////////////////////////////////////////////////////////////////
    class HPX_COMPONENT_EXPORT particle
      : public hpx::components::detail::managed_component_base<particle>
    {
    public:
        enum actions
        {
            particle_init = 0,
            particle_distance = 1,
            particle_get_index = 2
        };

        particle()
        {}

        ///////////////////////////////////////////////////////////////////////
        // Exposed functionality of this component.

        /// Initialize the point with the given particle file. 
        void init(std::size_t objectid,std::string const& particlefile);

        /// Calculate the distance from this particle to the specified
        /// coordinates.
        double distance(double posx,double posy,double posz)
        {
            return std::sqrt( std::pow(posx_ - posx,2)
                            + std::pow(posy_ - posy,2)
                            + std::pow(posz_ - posz,2) );
        }

        /// Get the index of the particle.
        std::size_t get_index()
        {
            return idx_;
        }

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into an
        // action type, generating all required boilerplate code for threads,
        // serialization, etc.
        typedef hpx::actions::action2<
            // Component server type.
            particle,
            // Action code.
            particle_init,
            // Arguments of this action.
            std::size_t,
            std::string const&,
            // Method bound to this action.
            &particle::init
        > init_action;

        typedef hpx::actions::result_action3<
            // Component server type.
            particle,
            // Return type.
            double,
            // Action code.
            particle_distance,
            // Arguments of this action.
            double,
            double,
            double,
            // Method bound to this action.
            &particle::distance
        > distance_action;

        typedef hpx::actions::result_action0<
            // Component server type.
            particle,
            // Return type.
            std::size_t,
            // Action code.
            particle_get_index,
            // Method bound to this action.
            &particle::get_index
        > get_index_action;

    private:
        std::size_t idx_;
        double posx_,posy_,posz_;
    };

}}

HPX_REGISTER_ACTION_DECLARATION_EX(
              gtc::server::particle::init_action,
              gtc_particle_init_action)

HPX_REGISTER_ACTION_DECLARATION_EX(
              gtc::server::particle::distance_action,
              gtc_particle_distance_action)

HPX_REGISTER_ACTION_DECLARATION_EX(
              gtc::server::particle::get_index_action,
              gtc_particle_get_index_action)


#endif


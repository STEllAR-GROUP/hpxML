//  Copyright (c) 2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_A07C7784_8AD2_4A12_B5BA_174DFBE03222)
#define HPX_A07C7784_8AD2_4A12_B5BA_174DFBE03222

#include <vector>
#include <queue>

#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/local_lcos.hpp>
#include <hpx/include/util.hpp>

#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/util/unlock_lock.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace gtc { namespace server
{

    ///////////////////////////////////////////////////////////////////////////
    class HPX_COMPONENT_EXPORT point
      : public hpx::components::managed_component_base<point>
    {
    public:
        point()
        {}

        ///////////////////////////////////////////////////////////////////////
        // Exposed functionality of this component.

        void setup(std::size_t numberpe,std::size_t mype,
                   std::vector<hpx::naming::id_type> const& point_components);
        void chargei();
        void partd_allreduce(double *dnitmp,double *densityi,int *mgrid,int *mzetap1);
        void partd_allreduce_receive(std::vector<double> const&receive,std::size_t i);

        // Each of the exposed functions needs to be encapsulated into an
        // action type, generating all required boilerplate code for threads,
        // serialization, etc.
        HPX_DEFINE_COMPONENT_ACTION(point, setup, setup_action);
        HPX_DEFINE_COMPONENT_ACTION(point, chargei, chargei_action);
        HPX_DEFINE_COMPONENT_ACTION(point, partd_allreduce_receive, partd_allreduce_receive_action);

    private:
        hpx::lcos::local::mutex mtx_;
        std::size_t item_;
        std::vector<hpx::naming::id_type> toroidal_comm_,partd_comm_;
        std::size_t left_pe_,right_pe_;

        hpx::lcos::local::and_gate gate_; // synchronization gate
    };
}}

// Declaration of serialization support for the actions
HPX_REGISTER_ACTION_DECLARATION_EX(
    gtc::server::point::setup_action,
    gtc_point_setup_action);

HPX_REGISTER_ACTION_DECLARATION_EX(
    gtc::server::point::chargei_action,
    gtc_point_chargei_action);

HPX_REGISTER_ACTION_DECLARATION_EX(
    gtc::server::point::partd_allreduce_receive_action,
    gtc_point_partd_allreduce_receive_action);

#endif


//  Copyright (c) 2007-2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/runtime/components/component_factory.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

#include "server/point.hpp"

///////////////////////////////////////////////////////////////////////////////
// Add factory registration functionality
HPX_REGISTER_COMPONENT_MODULE();

///////////////////////////////////////////////////////////////////////////////
typedef hpx::components::managed_component<
    gtc::server::point
> gtc_point_type;

HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(gtc_point_type, gtc_point);

///////////////////////////////////////////////////////////////////////////////
HPX_REGISTER_ACTION_EX(
    gtc_point_type::wrapped_type::setup_action,
    gtc_point_setup_action);

HPX_REGISTER_ACTION_EX(
    gtc_point_type::wrapped_type::chargei_action,
    gtc_point_chargei_action);

HPX_REGISTER_ACTION_EX(
    gtc_point_type::wrapped_type::partd_allreduce_receive_action,
    gtc_point_partd_allreduce_receive_action);

HPX_REGISTER_ACTION_EX(
    gtc_point_type::wrapped_type::allreduce_action,
    gtc_point_allreduce_action);

HPX_REGISTER_ACTION_EX(
    gtc_point_type::wrapped_type::setdata_action,
    gtc_point_setdata_action);

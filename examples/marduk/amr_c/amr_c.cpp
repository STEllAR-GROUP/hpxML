//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011 Matt Anderson
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>
#include <hpx/runtime/components/component_factory.hpp>
#include <hpx/runtime/components/derived_component_factory.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

#include "stencil.hpp"
#include "logging.hpp"

///////////////////////////////////////////////////////////////////////////////
// Add factory registration functionality
HPX_REGISTER_COMPONENT_MODULE();

///////////////////////////////////////////////////////////////////////////////
typedef hpx::components::amr::stencil marduk_stencil_type;
typedef hpx::components::amr::server::logging marduk_logging_type;

///////////////////////////////////////////////////////////////////////////////
/// The following construct registers a minimal factory needed for the creation
/// of new stencil instances. The name used as the second macro parameter
/// must match the component name used in the ini configuration file used
/// for this component. For instance the configuration file amr.ini may look 
/// like:
/// 
/// [hpx.components.marduk_stencil]  # this must match the string below
/// name = had_amr_test           # this must match the name of the shared library
/// path = $[hpx.location]/lib    # this is the default location where to find the shared library
///
HPX_REGISTER_DERIVED_COMPONENT_FACTORY(
    hpx::components::simple_component<marduk_stencil_type>, 
    marduk_stencil, "marduk_functional_component_type");

HPX_DEFINE_GET_COMPONENT_TYPE(marduk_stencil_type);

/// [hpx.components.had_logging]  # this must match the string below
/// name = had_amr_test           # this must match the name of the shared library
/// path = $[hpx.location]/lib    # this is the default location where to find the shared library
///
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    hpx::components::simple_component<marduk_logging_type>, marduk_logging3d);

HPX_REGISTER_ACTION_EX(marduk_logging_type::logentry_action, marduk_logentry_action);
HPX_DEFINE_GET_COMPONENT_TYPE(marduk_logging_type);

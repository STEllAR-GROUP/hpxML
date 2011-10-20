//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/components/component_factory.hpp>
#include <hpx/runtime/components/derived_component_factory_one.hpp>
#include <hpx/runtime/actions/continuation_impl.hpp>
#include <hpx/lcos/base_lco.hpp>
#include <hpx/util/ini.hpp>
#include <hpx/util/serialize_exception.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

///////////////////////////////////////////////////////////////////////////////
// Serialization support for the base LCO actions
HPX_REGISTER_ACTION_EX(hpx::lcos::base_lco::set_event_action, base_set_event_action);
HPX_REGISTER_ACTION_EX(hpx::lcos::base_lco::set_error_action, base_set_error_action);

///////////////////////////////////////////////////////////////////////////////
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::naming::gid_type>::set_result_action,
    set_result_action_gid_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::naming::gid_type>::get_value_action,
    get_value_action_gid_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::gid_type> >::set_result_action,
    set_result_action_vector_gid_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::gid_type> >::get_value_action,
    get_value_action_vector_gid_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::naming::id_type>::set_result_action,
    set_result_action_id_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::naming::id_type>::get_value_action,
    get_value_action_id_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::id_type> >::set_result_action,
    set_result_action_vector_id_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::id_type> >::get_value_action,
    get_value_action_vector_id_type);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<double>::set_result_action,
    set_result_action_double);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<double>::get_value_action,
    get_value_action_double);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<int>::set_result_action,
    set_result_action_int);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<int>::get_value_action,
    get_value_action_int);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<bool>::set_result_action,
    set_result_action_bool);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<bool>::get_value_action,
    get_value_action_bool);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::util::section>::set_result_action,
    set_result_action_section);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::util::section>::get_value_action,
    get_value_action_section);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::util::unused_type>::set_result_action,
    set_result_action_void);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::util::unused_type>::get_value_action,
    get_value_action_void);

///////////////////////////////////////////////////////////////////////////////
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco, hpx::components::component_base_lco);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<hpx::naming::gid_type>,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::gid_type> >,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<hpx::naming::id_type>,
    hpx::components::component_base_lco_with_value);
typedef
    hpx::lcos::base_lco_with_value<hpx::naming::id_type, hpx::naming::gid_type>
remote_id_type_retval;
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    remote_id_type_retval,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<std::vector<hpx::naming::id_type> >,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<double>,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<int>,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<bool>,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<hpx::util::section>,
    hpx::components::component_base_lco_with_value);
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(
    hpx::lcos::base_lco_with_value<hpx::util::unused_type>,
    hpx::components::component_base_lco_with_value);

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    template hpx::util::section const&
    continuation::trigger(hpx::util::section const&);
}}


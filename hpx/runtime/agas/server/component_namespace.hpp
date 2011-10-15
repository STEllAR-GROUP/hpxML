////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_A16135FC_AA32_444F_BB46_549AD456A661)
#define HPX_A16135FC_AA32_444F_BB46_549AD456A661

#include <map>
#include <set>

#include <boost/format.hpp>
#include <boost/assert.hpp>
#include <boost/utility/binary.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/runtime/agas/request.hpp>
#include <hpx/runtime/agas/response.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/components/server/fixed_component_base.hpp>
#include <hpx/util/insert_checked.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/lcos/local_mutex.hpp>

namespace hpx { namespace agas
{

HPX_EXPORT naming::gid_type bootstrap_component_namespace_gid();
HPX_EXPORT naming::id_type bootstrap_component_namespace_id();

namespace server
{

struct component_namespace :
    components::fixed_component_base<
        HPX_AGAS_COMPONENT_NS_MSB, HPX_AGAS_COMPONENT_NS_LSB, // constant GID
        component_namespace
    >
{
    // {{{ nested types
    typedef lcos::local_mutex mutex_type;

    typedef boost::int32_t component_id_type;

    typedef std::set<boost::uint32_t> prefixes_type;

    typedef std::map<std::string, component_id_type> component_id_table_type;

    typedef std::map<component_id_type, prefixes_type> factory_table_type;
    // }}}

  private:
    mutex_type mutex_;
    component_id_table_type component_ids_;
    factory_table_type factories_;
    component_id_type type_counter;

  public:
    component_namespace()
      : mutex_()
      , component_ids_()
      , factories_()
      , type_counter(components::component_first_dynamic)
    {}

    response service(
        request const& req
        )
    {
        return service(req, throws);
    }

    response service(
        request const& req
      , error_code& ec
        );

    response bind_prefix(
        request const& req
      , error_code& ec = throws
        );

    response bind_name(
        request const& req
      , error_code& ec = throws
        );

    response resolve_id(
        request const& req
      , error_code& ec = throws
        );

    response unbind(
        request const& req
      , error_code& ec = throws
        );

    enum actions
    { // {{{ action enum
        // Actual actions
        namespace_service      = BOOST_BINARY_U(0100000)

        // Pseudo-actions
      , namespace_bind_prefix  = BOOST_BINARY_U(0100001)
      , namespace_bind_name    = BOOST_BINARY_U(0100010)
      , namespace_resolve_id   = BOOST_BINARY_U(0100011)
      , namespace_unbind       = BOOST_BINARY_U(0100100)
    }; // }}}

    typedef hpx::actions::result_action1<
        component_namespace
      , /* return type */ response
      , /* enum value */  namespace_service
      , /* arguments */   request const&
      , &component_namespace::service
      , threads::thread_priority_critical
    > service_action;
};

}}}

#endif // HPX_A16135FC_AA32_444F_BB46_549AD456A661


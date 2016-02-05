//  Copyright (c) 2016 Hartmut Kaiser
//  Copyright (c) 2016 Parsa Amini
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_AGAS_CLIENT_BOOTSTRAP_FEB_05_2016_114AM)
#define HPX_AGAS_CLIENT_BOOTSTRAP_FEB_05_2016_114AM

#include <hpx/runtime/agas/detail/agas_service_client.hpp>
#include <hpx/runtime/agas/component_namespace.hpp>
#include <hpx/runtime/agas/locality_namespace.hpp>
#include <hpx/runtime/agas/primary_namespace.hpp>
#include <hpx/runtime/agas/symbol_namespace.hpp>
#include <hpx/runtime/agas/server/component_namespace.hpp>
#include <hpx/runtime/agas/server/locality_namespace.hpp>
#include <hpx/runtime/agas/server/primary_namespace.hpp>
#include <hpx/runtime/agas/server/symbol_namespace.hpp>

namespace hpx { namespace agas { namespace detail
{
    struct bootstrap_data_type
    { // {{{
        bootstrap_data_type()
          : primary_ns_server_()
          , locality_ns_server_(&primary_ns_server_)
          , component_ns_server_()
          , symbol_ns_server_()
        {}

        void register_counter_types()
        {
            server::locality_namespace::register_counter_types();
            server::locality_namespace::register_global_counter_types();
            server::primary_namespace::register_counter_types();
            server::primary_namespace::register_global_counter_types();
            server::component_namespace::register_counter_types();
            server::component_namespace::register_global_counter_types();
            server::symbol_namespace::register_counter_types();
            server::symbol_namespace::register_global_counter_types();
        }

        void register_server_instance(char const* servicename)
        {
            locality_ns_server_.register_server_instance(servicename);
            primary_ns_server_.register_server_instance(servicename);
            component_ns_server_.register_server_instance(servicename);
            symbol_ns_server_.register_server_instance(servicename);
        }

        void unregister_server_instance(error_code& ec)
        {
            locality_ns_server_.unregister_server_instance(ec);
            if (!ec) primary_ns_server_.unregister_server_instance(ec);
            if (!ec) component_ns_server_.unregister_server_instance(ec);
            if (!ec) symbol_ns_server_.unregister_server_instance(ec);
        }

        server::primary_namespace primary_ns_server_;
        server::locality_namespace locality_ns_server_;
        server::component_namespace component_ns_server_;
        server::symbol_namespace symbol_ns_server_;
    }; // }}}

    ///////////////////////////////////////////////////////////////////////////
    struct bootstrap_service_client : agas_service_client
    {
        void set_local_locality(naming::gid_type const& g);
        response service_primary_ns(request const& req, error_code& ec);
        /*response service_component_ns(request const& req, error_code& ec);*/
        response service_symbol_ns(request const& req, error_code& ec);
        /*response service_locality_ns(request const& req, error_code& ec);*/

        bootstrap_data_type data_;
    };
}}}

#endif


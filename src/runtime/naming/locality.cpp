//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception_list.hpp>
#include <hpx/runtime/naming/locality.hpp>
#include <hpx/util/stringstream.hpp>
#include <hpx/util/asio_util.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/host_name.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace naming
{
    ///////////////////////////////////////////////////////////////////////////
    locality::iterator_type accept_begin(locality const& loc,
        boost::asio::io_service& io_service)
    {
        using boost::asio::ip::tcp;

        // collect errors here
        exception_list errors;

        std::string port_str(boost::lexical_cast<std::string>(loc.get_port()));

        // try to directly create an endpoint from the address
        try {
            tcp::endpoint ep;
            if (util::get_endpoint(loc.get_address(), loc.get_port(), ep))
            {
                return locality::iterator_type(
                    tcp::resolver::iterator::create(ep, loc.get_address(), port_str));
            }
        }
        catch (boost::system::system_error const& e) {
            errors.add(e);
        }

        // it's not an address, try to treat it as a host name
        try {
            // resolve the given address
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(loc.get_address(), port_str);

            return locality::iterator_type(resolver.resolve(query));
        }
        catch (boost::system::system_error const& e) {
            errors.add(e);
        }

        // it's not a host name either, create a custom iterator allowing to
        // filter the returned endpoints, for this we use "localhost" as the
        // address to enumerate endpoints
        try {
            // resolve the given address
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(boost::asio::ip::host_name(), port_str);

            return locality::iterator_type(detail::is_valid_endpoint(
                loc.get_address()), resolver.resolve(query));
        }
        catch (boost::system::system_error const& e) {
            errors.add(e);
        }

        // report errors
        hpx::util::osstream strm;
        strm << errors.get_message() << " (while trying to resolve: "
             << loc.get_address() << ":" << loc.get_port() << ")";

        HPX_THROW_EXCEPTION(network_error, "accept_begin",
            hpx::util::osstream_get_string(strm));
        return locality::iterator_type();
    }

    //////////////////////////////////////////////////////////////////////////
    locality::iterator_type connect_begin(locality const& loc,
        boost::asio::io_service& io_service)
    {
        using boost::asio::ip::tcp;

        // collect errors here
        exception_list errors;

        std::string port_str(boost::lexical_cast<std::string>(loc.get_port()));

        // try to directly create an endpoint from the address
        try {
            tcp::endpoint ep;
            if (util::get_endpoint(loc.get_address(), loc.get_port(), ep))
            {
                return locality::iterator_type(tcp::resolver::iterator::create(
                    ep, loc.get_address(), port_str));
            }
        }
        catch (boost::system::system_error const& e) {
            errors.add(e);
        }

        // it's not an address, try to treat it as a host name
        try {
            // resolve the given address
            tcp::resolver resolver(io_service);
            tcp::resolver::query query(
                !loc.get_address().empty() ? 
                    loc.get_address() : 
                    boost::asio::ip::host_name(),
                port_str);

            return locality::iterator_type(resolver.resolve(query));
        }
        catch (boost::system::system_error const& e) {
            errors.add(e);
        }

        // report errors
        hpx::util::osstream strm;
        strm << errors.get_message() << " (while trying to connect to: "
             << loc.get_address() << ":" << loc.get_port() << ")";

        HPX_THROW_EXCEPTION(network_error, "connect_begin",
            hpx::util::osstream_get_string(strm));

        return locality::iterator_type();
    }
}}

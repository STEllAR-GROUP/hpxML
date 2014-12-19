//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2014 Thomas Heller
//  Copyright (c) 2007 Richard D Guidry Jr
//  Copyright (c) 2011 Bryce Lelbach
//  Copyright (c) 2011 Katelyn Kufahl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_PARCELSET_POLICIES_TCP_LOCALITY_HPP
#define HPX_PARCELSET_POLICIES_TCP_LOCALITY_HPP

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/parcelset/locality.hpp>
#include <hpx/util/safe_bool.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/host_name.hpp>

#include <string>

namespace hpx { namespace parcelset
{
    namespace policies { namespace tcp
    {
        class locality
        {
        public:
            locality()
              : port_(boost::uint16_t(-1))
            {}

            locality(std::string const& addr, boost::uint16_t port)
              : address_(addr), port_(port)
            {}

            std::string const & address() const
            {
                return address_;
            }

            boost::uint16_t port() const
            {
                return port_;
            }

            static const char *type()
            {
                return "tcp";
            }

            operator util::safe_bool<locality>::result_type() const
            {
                return util::safe_bool<locality>()(port_ != boost::uint16_t(-1));
            }

            void save(util::portable_binary_oarchive & ar) const
            {
                ar.save(address_);
                ar.save(port_);
            }

            void load(util::portable_binary_iarchive & ar)
            {
                ar.load(address_);
                ar.load(port_);
            }

        private:
            friend bool operator==(locality const & lhs, locality const & rhs)
            {
                return lhs.port_ == rhs.port_ && lhs.address_ == rhs.address_;
            }

            friend bool operator<(locality const & lhs, locality const & rhs)
            {
                return lhs.address_ < rhs.address_ ||
                    (lhs.address_ == rhs.address_ && lhs.port_ < rhs.port_);
            }

            friend std::ostream & operator<<(std::ostream & os, locality const & loc)
            {
                boost::io::ios_flags_saver ifs(os);
                os << loc.address_ << ":" << loc.port_;

                return os;
            }

            std::string address_;
            boost::uint16_t port_;
        };
    }}
}}

#endif


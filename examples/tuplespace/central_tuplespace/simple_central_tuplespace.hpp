//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_SIMPLE_CENTRAL_TUPLESPACE_MAR_31_2013_0555PM)
#define HPX_SIMPLE_CENTRAL_TUPLESPACE_MAR_31_2013_0555PM

#include <hpx/include/components.hpp>

#include "stubs/simple_central_tuplespace.hpp"

namespace examples
{
    ///////////////////////////////////////////////////////////////////////////
    /// Client for the \a server::simple_central_tuplespace component.
    //[simple_central_tuplespace_client_inherit
    class simple_central_tuplespace
      : public hpx::components::client_base<
            simple_central_tuplespace, stubs::simple_central_tuplespace
        >
    //]
    {
        //[simple_central_tuplespace_base_type
        typedef hpx::components::client_base<
            simple_central_tuplespace, stubs::simple_central_tuplespace
        > base_type;
        //]

        typedef base_type::tuple_type tuple_type;

    public:
        /// Default construct an empty client side representation (not
        /// connected to any existing component).
        simple_central_tuplespace()
        {}

        /// Create a client side representation for the existing
        /// \a server::simple_central_tuplespace instance with the given GID.
        simple_central_tuplespace(hpx::future<hpx::naming::id_type> const& gid)
          : base_type(gid)
        {}

        simple_central_tuplespace(hpx::naming::id_type const& gid)
          : base_type(gid)
        {}
        ///////////////////////////////////////////////////////////////////////
        /// put \p tuple into tuplespace.
        ///
        /// \note This function has fire-and-forget semantics. It will not wait
        ///       for the action to be executed. Instead, it will return
        ///       immediately after the action has has been dispatched.
        //[simple_central_tuplespace_client_write_async
        hpx::lcos::future<int> write_async(const tuple_type tuple)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::write_async(this->get_gid(), tuple);
        }
        //]

        /// put \p tuple into tuplespace.
        ///
        /// \note This function is fully synchronous.
        int write_sync(const tuple_type tuple)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::write_sync(this->get_gid(), tuple);
        }

        ///////////////////////////////////////////////////////////////////////
        /// read matching tuple from tuplespace within \p timeout.
        ///
        /// \note This function has fire-and-forget semantics. It will not wait
        ///       for the action to be executed. Instead, it will return
        ///       immediately after the action has has been dispatched.
        hpx::lcos::future<tuple_type> read_async(const tuple_type tp, long timeout)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::read_async(this->get_gid(), tp, timeout);
        }

        /// read matching tuple from tuplespace within \p timeout.
        ///
        /// \note This function is fully synchronous.
        //[simple_central_tuplespace_client_read_sync
        tuple_type read_sync(const tuple_type tp, long timeout)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::read_sync(this->get_gid(), tp, timeout);
        }
        //]

        ///////////////////////////////////////////////////////////////////////
        /// take matching tuple from tuplespace within \p timeout.
        ///
        /// \returns This function returns an \a hpx::lcos::future. When the
        ///          value of this computation is needed, the get() method of
        ///          the future should be called. If the value is available,
        ///          get() will return immediately; otherwise, it will block
        ///          until the value is ready.
        //[simple_central_tuplespace_client_take_async
        hpx::lcos::future<tuple_type> take_async(const tuple_type tp, long timeout)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::take_async(this->get_gid(), tp, timeout);
        }
        //]

        /// take matching tuple from tuplespace within \p timeout.
        ///
        /// \note This function is fully synchronous.
        tuple_type take_sync(const tuple_type tp, long timeout)
        {
            BOOST_ASSERT(this->get_gid());
            return this->base_type::take_sync(this->get_gid(), tp, timeout);
        }
    };
} // examples

#endif


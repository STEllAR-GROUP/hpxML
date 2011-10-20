////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_E42C5C50_811E_454F_887A_DE7175E72EE9)
#define HPX_E42C5C50_811E_454F_887A_DE7175E72EE9

#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/cstdint.hpp>

#include <hpx/config.hpp>
#include <hpx/hpx_fwd.hpp>

namespace hpx { namespace parcelset
{

struct parcelhandler_queue_base
{
    typedef boost::signals2::scoped_connection connection_type;

    typedef boost::function<void(parcelhandler&, naming::address const&)>
        callback_type;

    virtual ~parcelhandler_queue_base() {}

    /// add a new parcel to the end of the parcel queue
    virtual void add_parcel(parcel const& p) = 0;

    /// return next available parcel
    virtual bool get_parcel(parcel& p) = 0;

    /// register event handler to be notified whenever a parcel arrives
    virtual bool register_event_handler(
        callback_type const& sink
    ) = 0;

    virtual bool register_event_handler(
        callback_type const& sink
      , connection_type& conn
    ) = 0;

    virtual void set_parcelhandler(parcelhandler* ph) = 0;

    virtual boost::int64_t get_queue_length() const = 0;
};

}}

#endif // HPX_E42C5C50_811E_454F_887A_DE7175E72EE9


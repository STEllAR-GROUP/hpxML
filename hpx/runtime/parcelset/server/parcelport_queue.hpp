//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2007 Alexandre (aka Alex) TABBAL
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_SERVER_PARCELPORTQUEUE_MAR_26_2008_1219PM)
#define HPX_PARCELSET_SERVER_PARCELPORTQUEUE_MAR_26_2008_1219PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/parcelset/parcel.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset { namespace server
{
    class parcelport_queue
    {
    public:
        parcelport_queue(hpx::parcelset::parcelport& pp)
          : parcel_port_(pp)
        {}

        /// add a new parcel to the end of the parcel queue
        void add_parcel(boost::shared_ptr<std::vector<char> > const& data,
                        threads::thread_priority priority)
        {
            notify_(parcel_port_, data, priority);      // do some work (notify event handlers)
        }

        /// register event handler to be notified whenever a parcel arrives
        template <typename F>
        void register_event_handler(F sink)
        {
            notify_ = sink;
        }

    private:
        hpx::parcelset::parcelport& parcel_port_;
        typedef void callback_type(parcelport&,
            boost::shared_ptr<std::vector<char> > const&,
            threads::thread_priority);
        boost::function<callback_type> notify_;
    };

///////////////////////////////////////////////////////////////////////////////
}}}

#endif

//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2007      Richard D Guidry Jr
//  Copyright (c) 2011      Bryce Lelbach & Katelyn Kufahl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/state.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/container_device.hpp>
#include <hpx/runtime/naming/resolver_client.hpp>
#include <hpx/runtime/parcelset/parcelhandler.hpp>
#include <hpx/runtime/threads/threadmanager.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/lcos/local_counting_semaphore.hpp>
#include <hpx/include/performance_counters.hpp>
#include <hpx/performance_counters/counter_creators.hpp>

#include <string>
#include <algorithm>

#include <boost/version.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/format.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    ///////////////////////////////////////////////////////////////////////////
    // A parcel is submitted for transport at the source locality site to
    // the parcel set of the locality with the put-parcel command
    // This function is synchronous.

    struct wait_for_put_parcel
    {
        wait_for_put_parcel() : sema_(new lcos::local_counting_semaphore) {}

        wait_for_put_parcel(wait_for_put_parcel const& other)
            : sema_(other.sema_) {}

        void operator()(boost::system::error_code const&, std::size_t)
        {
            sema_->signal();
        }

        void wait()
        {
            sema_->wait();
        }

        boost::shared_ptr<lcos::local_counting_semaphore> sema_;
    };

    void parcelhandler::sync_put_parcel(parcel& p)
    {
        wait_for_put_parcel wfp;
        put_parcel(p, wfp);  // schedule parcel send
        wfp.wait();          // wait for the parcel to be sent
    }

    void parcelhandler::parcel_sink(parcelport& pp,
        boost::shared_ptr<std::vector<char> > const& parcel_data,
        threads::thread_priority priority)
    {
        // wait for thread-manager to become active
        while (tm_->status() & starting)
        {
            boost::this_thread::sleep(boost::get_system_time() +
                boost::posix_time::milliseconds(HPX_NETWORK_RETRIES_SLEEP));
        }

        // Give up if we're shutting down.
        if (tm_->status() & stopping)
        {
            LPT_(debug) << "parcel_sink: dropping late parcel";
            return;
        }
        else
        {
            // create a new thread which decodes and handles the parcel
            threads::thread_init_data data(
                boost::bind(&parcelhandler::decode_parcel, this, parcel_data),
                "decode_parcel", 0, priority);
            tm_->register_thread(data);
        }
    }

    threads::thread_state_enum parcelhandler::decode_parcel(
        boost::shared_ptr<std::vector<char> > const& parcel_data)
    {
        // protect from unhandled exceptions bubbling up into thread manager
        try {
            try {
                // create a special io stream on top of in_buffer_
                typedef util::container_device<std::vector<char> > io_device_type;
                boost::iostreams::stream<io_device_type> io(*parcel_data.get());

                // De-serialize the parcel data
                hpx::util::portable_binary_iarchive archive(io);

                std::size_t parcel_count = 0;
                archive >> parcel_count;
                while(parcel_count-- != 0)
                {
                    // de-serialize parcel and add it to incoming parcel queue
                    parcel p;
                    archive >> p;
                    parcels_->add_parcel(p);
                }
            }
            catch (std::exception const& e) {
                // We have to repackage all exceptions thrown by the
                // serialization library as otherwise we will loose the
                // e.what() description of the problem, due to slicing.
                boost::throw_exception(boost::enable_error_info(
                    hpx::exception(unhandled_exception, e.what())));
            }
        }
        catch (hpx::exception const& e) {
            LPT_(error)
                << "decode_parcel: caught hpx::exception: "
                << e.what();
            hpx::report_error(boost::current_exception());
        }
        catch (boost::system::system_error const& e) {
            LPT_(error)
                << "decode_parcel: caught boost::system::error: "
                << e.what();
            hpx::report_error(boost::current_exception());
        }
        catch (boost::exception const&) {
            LPT_(error)
                << "decode_parcel: caught boost::exception.";
            hpx::report_error(boost::current_exception());
        }
        catch (...) {
            // Prevent exceptions from boiling up into the thread-manager.
            LPT_(error)
                << "decode_parcel: caught unknown exception.";
            hpx::report_error(boost::current_exception());
        }

        return threads::terminated;
    }

    parcelhandler::parcelhandler(naming::resolver_client& resolver,
            parcelport& pp, threads::threadmanager_base* tm,
            parcelhandler_queue_base* policy)
      : resolver_(resolver)
      , pp_(pp)
      , tm_(tm)
      , parcels_(policy)
    {
        BOOST_ASSERT(parcels_);

        // AGAS v2 registers itself in the client before the parcelhandler
        // is booted.
        locality_ = resolver_.local_locality();

        parcels_->set_parcelhandler(this);

        // register our callback function with the parcelport
        pp_.register_event_handler(
            boost::bind(&parcelhandler::parcel_sink, this, _1, _2, _3));
    }

    naming::resolver_client& parcelhandler::get_resolver()
    {
        return resolver_;
    }

    bool parcelhandler::get_raw_remote_localities(
        std::vector<naming::gid_type>& locality_ids,
        components::component_type type) const
    {
        std::vector<naming::gid_type> allprefixes;
        error_code ec;
        bool result = resolver_.get_localities(allprefixes, type, ec);
        if (ec || !result) return false;

        using boost::lambda::_1;
        std::remove_copy_if(allprefixes.begin(), allprefixes.end(),
            std::back_inserter(locality_ids), _1 == locality_);
        return !locality_ids.empty();
    }

    bool parcelhandler::get_raw_localities(
        std::vector<naming::gid_type>& locality_ids,
        components::component_type type) const
    {
        error_code ec;
        bool result = resolver_.get_localities(locality_ids, type, ec);
        if (ec || !result) return false;

        return !locality_ids.empty();
    }

    void parcelhandler::put_parcel(parcel& p, write_handler_type f)
    {
        // properly initialize parcel
        init_parcel(p);

        if (!p.get_destination_addr())
        {
            naming::address addr;

            if (!resolver_.resolve_cached(p.get_destination(), addr))
            {
                // resolve the remote address
                resolver_.resolve(p.get_destination(), addr);
                p.set_destination_addr(addr);
            }

            else
                p.set_destination_addr(addr);
        }

        pp_.put_parcel(p, f);
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelhandler::register_counter_types()
    {
        HPX_STD_FUNCTION<boost::int64_t()> num_sends(
            boost::bind(&parcelport::total_sends_completed, &pp_));
        HPX_STD_FUNCTION<boost::int64_t()> num_receives(
            boost::bind(&parcelport::total_receives_completed, &pp_));
        HPX_STD_FUNCTION<boost::int64_t()> queue_length(
            boost::bind(&parcelhandler::get_queue_length, this));

        performance_counters::generic_counter_type_data const counter_types[] =
        {
            { "/parcels/count/sent", performance_counters::counter_raw,
              "returns the number of sent parcels for the referenced locality",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_sends, _2),
              &performance_counters::locality_counter_discoverer
            },
            { "/parcels/count/received", performance_counters::counter_raw,
              "returns the number of received parcels for the referenced locality",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_receives, _2),
              &performance_counters::locality_counter_discoverer
            },
            { "/parcelqueue/length/instantaneous", performance_counters::counter_raw,
              "returns the number current length of the queue of incoming threads",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, queue_length, _2),
              &performance_counters::locality_counter_discoverer
            }
        };
        performance_counters::install_counter_types(
            counter_types, sizeof(counter_types)/sizeof(counter_types[0]));
    }
}}


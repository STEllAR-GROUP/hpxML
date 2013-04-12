//  Copyright (c)      2013 Thomas Heller
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>

#if defined(HPX_HAVE_PARCELPORT_IBVERBS)
#include <hpx/exception_list.hpp>
#include <hpx/runtime/naming/locality.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/runtime/parcelset/ibverbs/parcelport.hpp>
#include <hpx/runtime/parcelset/ibverbs/data_buffer.hpp>
#include <hpx/runtime/parcelset/detail/call_for_each.hpp>
#include <hpx/util/runtime_configuration.hpp>
#include <hpx/util/io_service_pool.hpp>
#include <hpx/util/stringstream.hpp>
#include <hpx/util/logging.hpp>

#include <boost/version.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/placeholders.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset { namespace ibverbs
{
    ///////////////////////////////////////////////////////////////////////////
    parcelport::parcelport(util::runtime_configuration const& ini,
            HPX_STD_FUNCTION<void(std::size_t, char const*)> const& on_start_thread,
            HPX_STD_FUNCTION<void()> const& on_stop_thread)
      : parcelset::parcelport(naming::locality(ini.get_parcelport_address())),
        io_service_pool_(ini.get_thread_pool_size("parcel_pool"),
            on_start_thread, on_stop_thread, "parcel_pool_ibverbs", "-ibverbs"),
        acceptor_(NULL),
        connection_cache_(ini.get_max_connections(), ini.get_max_connections_per_loc())
    {
    }

    parcelport::~parcelport()
    {
        // make sure all existing connections get destroyed first
        connection_cache_.clear();
        if (NULL != acceptor_) {
            boost::system::error_code ec;
            acceptor_->close(ec);
            delete acceptor_;
        }
    }

    util::io_service_pool* parcelport::get_thread_pool(char const* name)
    {
        if (0 == std::strcmp(name, io_service_pool_.get_name()))
            return &io_service_pool_;
        return 0;
    }

    bool parcelport::run(bool blocking)
    {
        io_service_pool_.run(false);    // start pool

        if (NULL == acceptor_)
            acceptor_ = new acceptor(io_service_pool_.get_io_service(0));

        // initialize network
        std::size_t tried = 0;
        exception_list errors;
        naming::locality::iterator_type end = accept_end(here_);
        for (naming::locality::iterator_type it =
                accept_begin(here_, io_service_pool_.get_io_service(0));
             it != end; ++it, ++tried)
        {
            try {
                server::ibverbs::parcelport_connection_ptr conn(
                    new server::ibverbs::parcelport_connection(
                        io_service_pool_.get_io_service(1), *this));

                boost::asio::ip::tcp::endpoint ep = *it;

                acceptor_->bind(ep);

                acceptor_->async_accept(conn,
                    boost::bind(&parcelport::handle_accept, this,
                        boost::asio::placeholders::error, conn));
            }
            catch (boost::system::system_error const& e) {
                errors.add(e);   // store all errors
                continue;
            }
        }

        if (errors.get_error_count() == tried) {
            // all attempts failed
            HPX_THROW_EXCEPTION(network_error,
                "ibverbs::parcelport::run", errors.get_message());
            return false;
        }

        if (blocking)
            io_service_pool_.join();

        return true;
    }

    void parcelport::stop(bool blocking)
    {
        // now it's safe to take everything down
        connection_cache_.shutdown();

        connection_cache_.clear();

        // cancel all pending accept operations
        if (NULL != acceptor_)
        {
            boost::system::error_code ec;
            acceptor_->close(ec);
            delete acceptor_;
            acceptor_ = NULL;
        }

        // make sure no more work is pending, wait for service pool to get empty
        io_service_pool_.stop();
        if (blocking) {
            io_service_pool_.join();
            io_service_pool_.clear();
        }
    }

    /// accepted new incoming connection
    void parcelport::handle_accept(boost::system::error_code const& e,
        server::ibverbs::parcelport_connection_ptr conn)
    {
        if (!e) {
            // handle this incoming parcel
            server::ibverbs::parcelport_connection_ptr c(conn);    // hold on to conn

            // create new connection waiting for next incoming parcel
            conn.reset(new server::ibverbs::parcelport_connection(
                io_service_pool_.get_io_service(1), *this));
        
            acceptor_->async_accept(conn,
                boost::bind(&parcelport::handle_accept, this,
                    boost::asio::placeholders::error, conn));

            // now accept the incoming connection by starting to read from the
            // context
            c->async_read(boost::bind(&parcelport::handle_read_completion,
                this, boost::asio::placeholders::error, c));
        }
    }

    /// Handle completion of a read operation.
    void parcelport::handle_read_completion(boost::system::error_code const& e,
        server::ibverbs::parcelport_connection_ptr c)
    {
        if (!e) return;

        if (e != boost::asio::error::operation_aborted &&
            e != boost::asio::error::eof)
        {
            LPT_(error)
                << "handle read operation completion: error: "
                << e.message();
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelport::put_parcels(std::vector<parcel> const & parcels,
        std::vector<write_handler_type> const& handlers)
    {
        typedef pending_parcels_map::iterator iterator;
        typedef pending_parcels_map::mapped_type mapped_type;

        if (parcels.size() != handlers.size())
        {
            HPX_THROW_EXCEPTION(bad_parameter, "parcelport::put_parcels",
                "mismatched number of parcels and handlers");
            return;
        }

        naming::locality locality_id = parcels[0].get_destination_locality();
        naming::gid_type parcel_id = parcels[0].get_parcel_id();

#if defined(HPX_DEBUG)
        // make sure all parcels go to the same locality
        for (std::size_t i = 1; i != parcels.size(); ++i)
        {
            BOOST_ASSERT(locality_id == parcels[i].get_destination_locality());
        }
#endif

        // enqueue the outgoing parcels ...
        {
            util::spinlock::scoped_lock l(mtx_);

            mapped_type& e = pending_parcels_[locality_id];
            for (std::size_t i = 0; i != parcels.size(); ++i)
            {
                e.first.push_back(parcels[i]);
                e.second.push_back(handlers[i]);
            }
        }

        error_code ec;
        parcelport_connection_ptr client_connection =
            get_connection(locality_id, ec);

        if (!client_connection)
        {
            if (ec)
                report_potential_connection_error(locality_id, parcel_id, ec);

            // We can safely return if no connection is available at this point.
            // As soon as a connection becomes available it checks for pending
            // parcels and sends those out.
            return;
        }

        send_parcels_or_reclaim_connection(locality_id, client_connection);
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelport::put_parcel(parcel const& p, write_handler_type f)
    {
        typedef pending_parcels_map::iterator iterator;
        typedef pending_parcels_map::mapped_type mapped_type;

        naming::locality locality_id = p.get_destination_locality();
        naming::gid_type parcel_id = p.get_parcel_id();

        // enqueue the outgoing parcel ...
        {
            util::spinlock::scoped_lock l(mtx_);

            mapped_type& e = pending_parcels_[locality_id];
            e.first.push_back(p);
            e.second.push_back(f);
        }

        error_code ec;
        parcelport_connection_ptr client_connection =
            get_connection(locality_id, ec);

        if (!client_connection)
        {
            if (ec)
                report_potential_connection_error(locality_id, parcel_id, ec);

            // We can safely return if no connection is available at this point.
            // As soon as a connection becomes available it checks for pending
            // parcels and sends those out.
            return;
        }

        send_parcels_or_reclaim_connection(locality_id, client_connection);
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelport::send_parcels_or_reclaim_connection(
        naming::locality const& locality_id, 
        parcelport_connection_ptr const& client_connection)
    {
        typedef pending_parcels_map::iterator iterator;

        std::vector<parcel> parcels;
        std::vector<write_handler_type> handlers;

        {
            util::spinlock::scoped_lock l(mtx_);
            iterator it = pending_parcels_.find(locality_id);

            if (it != pending_parcels_.end())
            {
                BOOST_ASSERT(it->first == locality_id);
                std::swap(parcels, it->second.first);
                std::swap(handlers, it->second.second);

                if (parcels.empty())
                {
                    // if no parcels are pending re-add the connection to
                    // the cache
                    BOOST_ASSERT(handlers.empty());
                    BOOST_ASSERT(locality_id == client_connection->destination());
                    connection_cache_.reclaim(locality_id, client_connection);
                    return;
                }
            }
        }

        // send parcels if they didn't get sent by another connection
        send_pending_parcels(client_connection, parcels, handlers);
    }

    void parcelport::send_pending_parcels_trampoline(
        boost::system::error_code const& ec,
        naming::locality const& locality_id,
        parcelport_connection_ptr client_connection)
    {
        typedef pending_parcels_map::iterator iterator;

        std::vector<parcel> parcels;
        std::vector<write_handler_type> handlers;

        {
            util::spinlock::scoped_lock l(mtx_);
            iterator it = pending_parcels_.find(locality_id);

            if (it != pending_parcels_.end())
            {
                std::swap(parcels, it->second.first);
                std::swap(handlers, it->second.second);

                if (parcels.empty())
                {
                    // Give this connection back to the cache as it's not
                    // needed anymore.
                    BOOST_ASSERT(handlers.empty());
                    BOOST_ASSERT(locality_id == client_connection->destination());
                    connection_cache_.reclaim(locality_id, client_connection);
                    return;
                }
            }
        }

        // Create a new thread which sends parcels that are still pending.
        hpx::applier::register_thread_nullary(
            HPX_STD_BIND(&parcelport::send_pending_parcels, this,
                client_connection, boost::move(parcels),
                boost::move(handlers)), "send_pending_parcels");
    }

    void parcelport::send_pending_parcels(
        parcelport_connection_ptr client_connection,
        std::vector<parcel> const & parcels,
        std::vector<write_handler_type> const & handlers)
    {
        // store parcels in connection
        // The parcel gets serialized inside set_parcel, no
        // need to keep the original parcel alive after this call returned.
        client_connection->set_parcel(parcels);

        // ... start an asynchronous write operation now.
        client_connection->async_write(
            hpx::parcelset::detail::call_for_each(handlers),
            boost::bind(&parcelport::send_pending_parcels_trampoline, this,
                boost::asio::placeholders::error, ::_2, ::_3));
    }

    ///////////////////////////////////////////////////////////////////////////
    parcelport_connection_ptr parcelport::get_connection_wait(
        naming::locality const& l, error_code& ec)
    {
        parcelport_connection_ptr client_connection;
        bool got_cache_space = false;

        for (std::size_t i = 0; i < HPX_MAX_NETWORK_RETRIES; ++i)
        {
            // Get a connection or reserve space for a new connection.
            if (connection_cache_.get_or_reserve(l, client_connection))
            {
                got_cache_space = true;
                break;
            }

            // Wait for a really short amount of time.
            boost::this_thread::sleep(boost::get_system_time() +
                boost::posix_time::milliseconds(HPX_NETWORK_RETRIES_SLEEP));
        }

        // If we didn't get a connection or permission to create one (which is
        // unlikely), bail.
        if (!got_cache_space)
        {
            HPX_THROWS_IF(ec, invalid_status, "parcelport::get_connection_wait",
                "didn't get a connection slot from connection cache, bailing out");
            return client_connection;
        }

        return get_connection(l, client_connection, ec);
    }
    
    parcelport_connection_ptr parcelport::get_connection(
        naming::locality const& l, error_code& ec)
    {
        parcelport_connection_ptr client_connection;

        // Get a connection or reserve space for a new connection.
        if (!connection_cache_.get_or_reserve(l, client_connection))
        {
            // if no slot is available it's not a problem as the parcel will
            // sent out whenever the next connection is returned to the cache
            if (&ec != &throws)
                ec = make_success_code();
            return client_connection;
        }

        return get_connection(l, client_connection, ec);
    }

    parcelport_connection_ptr parcelport::get_connection(
        naming::locality const& l, parcelport_connection_ptr client_connection,
        error_code& ec)
    {
        // Check if we need to create the new connection.
        if (!client_connection)
        {
            // The parcel gets serialized inside the connection constructor, no
            // need to keep the original parcel alive after this call returned.
            client_connection.reset(new parcelport_connection(
                io_service_pool_.get_io_service(1), l, parcels_sent_));

            // Connect to the target locality, retry if needed
            boost::system::error_code error = boost::asio::error::try_again;
            for (std::size_t i = 0; i < HPX_MAX_NETWORK_RETRIES; ++i)
            {
                try {
                    naming::locality::iterator_type end = connect_end(l);
                    for (naming::locality::iterator_type it =
                            connect_begin(l, io_service_pool_.get_io_service(0));
                         it != end; ++it)
                    {
                        boost::asio::ip::tcp::endpoint const& ep = *it;

                        parcelset::ibverbs::client_context& ctx = client_connection->context();
                        ctx.close();
                        ctx.connect(ep, error);
                        if (!error)
                            break;
                    }
                    if (!error)
                        break;

                    // wait for a really short amount of time
                    if (hpx::threads::get_self_ptr()) {
                        this_thread::suspend();
                    }
                    else {
                        boost::this_thread::sleep(boost::get_system_time() +
                            boost::posix_time::milliseconds(
                                HPX_NETWORK_RETRIES_SLEEP));
                    }
                }
                catch (boost::system::system_error const& e) {
                    client_connection->context().close();
                    client_connection.reset();

                    HPX_THROWS_IF(ec, network_error,
                        "ibverbs::parcelport::get_connection", e.what());
                    return client_connection;
                }
            }

            if (error) {
                client_connection->context().close();
                client_connection.reset();

                hpx::util::osstream strm;
                strm << error.message() << " (while trying to connect to: "
                     << l << ")";

                HPX_THROWS_IF(ec, network_error,
                    "ibverbs::parcelport::get_connection",
                    hpx::util::osstream_get_string(strm));
                return client_connection;
            }
        }

        if (&ec != &throws)
            ec = make_success_code();

        return client_connection;
    }

    /// Return the given connection cache statistic
    boost::int64_t parcelport::get_connection_cache_statistics(
        connection_cache_statistics_type t, bool reset)
    {
        switch (t) {
        case connection_cache_insertions:
            return connection_cache_.get_cache_insertions(reset);

        case connection_cache_evictions:
            return connection_cache_.get_cache_evictions(reset);

        case connection_cache_hits:
            return connection_cache_.get_cache_hits(reset);

        case connection_cache_misses:
            return connection_cache_.get_cache_misses(reset);

        default:
            break;
        }

        HPX_THROW_EXCEPTION(bad_parameter,
            "ibverbs::parcelport::get_connection_cache_statistics",
            "invalid connection cache statistics type");
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    void decode_message(parcelport& pp,
        data_buffer const & parcel_data,
        boost::uint64_t inbound_data_size,
        performance_counters::parcels::data_point receive_data)
    {
        // protect from un-handled exceptions bubbling up
        try {
            try {
                // mark start of serialization
                util::high_resolution_timer timer;
                boost::int64_t overall_add_parcel_time = 0;

                {
                    // De-serialize the parcel data
                    util::portable_binary_iarchive archive(parcel_data,
                        parcel_data.size(), boost::archive::no_header);

                    std::size_t parcel_count = 0;

                    archive >> parcel_count;
                    for(std::size_t i = 0; i < parcel_count; ++i)
                    {
                        // de-serialize parcel and add it to incoming parcel queue
                        parcel p;
                        archive >> p;

                        // make sure this parcel ended up on the right locality
                        BOOST_ASSERT(p.get_destination_locality() == pp.here());

                        // be sure not to measure add_parcel as serialization time
                        boost::int64_t add_parcel_time = timer.elapsed_nanoseconds();
                        pp.add_received_parcel(p);
                        overall_add_parcel_time += timer.elapsed_nanoseconds() -
                            add_parcel_time;
                    }

                    // complete received data with parcel count
                    receive_data.num_parcels_ = parcel_count;
                    receive_data.raw_bytes_ = archive.bytes_read();
                }

                // store the time required for serialization
                receive_data.serialization_time_ = timer.elapsed_nanoseconds() -
                    overall_add_parcel_time;

                pp.add_received_data(receive_data);
            }
            catch (hpx::exception const& e) {
                LPT_(error)
                    << "decode_message: caught hpx::exception: "
                    << e.what();
                hpx::report_error(boost::current_exception());
            }
            catch (boost::system::system_error const& e) {
                LPT_(error)
                    << "decode_message: caught boost::system::error: "
                    << e.what();
                hpx::report_error(boost::current_exception());
            }
            catch (boost::exception const&) {
                LPT_(error)
                    << "decode_message: caught boost::exception.";
                hpx::report_error(boost::current_exception());
            }
            catch (std::exception const& e) {
                // We have to repackage all exceptions thrown by the
                // serialization library as otherwise we will loose the
                // e.what() description of the problem, due to slicing.
                boost::throw_exception(boost::enable_error_info(
                    hpx::exception(serialization_error, e.what())));
            }
        }
        catch (...) {
            LPT_(error)
                << "decode_message: caught unknown exception.";
            hpx::report_error(boost::current_exception());
        }
    }
}}}

#endif

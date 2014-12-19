//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2013-2014 Thomas Heller
//  Copyright (c) 2007      Richard D Guidry Jr
//  Copyright (c) 2011      Bryce Lelbach & Katelyn Kufahl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/state.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/io_service_pool.hpp>
#include <hpx/util/safe_lexical_cast.hpp>
#include <hpx/util/stringstream.hpp>
#include <hpx/util/runtime_configuration.hpp>
#include <hpx/runtime/naming/resolver_client.hpp>
#include <hpx/runtime/parcelset/parcelhandler.hpp>
#include <hpx/runtime/threads/threadmanager.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/lcos/local/counting_semaphore.hpp>
#include <hpx/include/performance_counters.hpp>
#include <hpx/performance_counters/counter_creators.hpp>

#include <hpx/plugins/parcelport_factory_base.hpp>

#include <string>
#include <algorithm>

#include <boost/version.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    bool is_stopped_or_shutting_down();
}

namespace hpx { namespace detail
{
    void dijkstra_make_black();     // forward declaration only
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    ///////////////////////////////////////////////////////////////////////////
    policies::message_handler* get_message_handler(
        parcelhandler* ph, char const* action, char const* type, std::size_t num,
        std::size_t interval, locality const& loc,
        error_code& ec)
    {
        return ph->get_message_handler(action, type, num, interval, loc, ec);
    }

    ///////////////////////////////////////////////////////////////////////////
    // A parcel is submitted for transport at the source locality site to
    // the parcel set of the locality with the put-parcel command
    // This function is synchronous.

    struct wait_for_put_parcel
    {
        wait_for_put_parcel() : sema_(new lcos::local::counting_semaphore) {}

        void operator()(boost::system::error_code const&, parcel const&)
        {
            sema_->signal();
        }

        void wait()
        {
            sema_->wait();
        }

        boost::shared_ptr<lcos::local::counting_semaphore> sema_;
    };

    void parcelhandler::sync_put_parcel(parcel& p) //-V669
    {
        wait_for_put_parcel wfp;
        put_parcel(p, wfp);  // schedule parcel send
        wfp.wait();          // wait for the parcel to be sent
    }

    void parcelhandler::parcel_sink(parcel const& p)
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

        parcels_->add_parcel(p);
    }

    parcelhandler::parcelhandler(
            util::runtime_configuration & cfg,
            naming::resolver_client& resolver,
            threads::threadmanager_base* tm, parcelhandler_queue_base* policy,
            HPX_STD_FUNCTION<void(std::size_t, char const*)> const& on_start_thread,
            HPX_STD_FUNCTION<void()> const& on_stop_thread)
      : resolver_(resolver),
        tm_(tm),
        parcels_(policy),
        use_alternative_parcelports_(false),
        enable_parcel_handling_(true),
        count_routed_(0)
    {
        namespace fs = boost::filesystem;
        // load all parcelports as described in the configuration information
        if (!cfg.has_section("hpx.parcel")) {
            LRT_(info) << "No parcelports found/loaded.";
            return;     // no plugins to load
        }

        util::section* sec = cfg.get_section("hpx.parcel");
        if (NULL == sec)
        {
            LRT_(error) << "NULL section found";
            return;     // something bad happened
        }

        util::section::section_map const& s = (*sec).get_sections();
        typedef util::section::section_map::const_iterator iterator;
        iterator end = s.end();
        for (iterator i = s.begin (); i != end; ++i)
        {
            // the section name is the instance name of the component
            util::section const& sect = i->second;
            std::string instance (sect.get_name());
            std::string parcelport;

            if (i->second.has_entry("name"))
                parcelport = sect.get_entry("name");
            else
                parcelport = instance;

            bool isenabled = true;
            if (sect.has_entry("enabled")) {
                std::string tmp = sect.get_entry("enabled");
                boost::algorithm::to_lower (tmp);
                if (tmp == "no" || tmp == "false" || tmp == "0") {
                    LRT_(info) << "parcelport factory disabled: " << instance;
                    isenabled = false;     // this parcelport has been disabled
                }
            }
            fs::path lib;
            try {
                if (sect.has_entry("path"))
                    lib = hpx::util::create_path(sect.get_entry("path"));
                else
                    lib = hpx::util::create_path(HPX_DEFAULT_COMPONENT_PATH);

                if (sect.get_entry("static", "0") == "1") {
                    // FIXME: implement statically linked plugins
                }
                else {
#if defined(HPX_STATIC_LINKING)
                    HPX_THROW_EXCEPTION(service_unavailable,
                        "parcelset::parcelset",
                        "static linking configuration does not support dynamic "
                        "loading of parcelport '" + instance + "'");
#else
                    // first, try using the path as the full path to the library
                    if (!load_parcelport(cfg, instance, parcelport, lib, isenabled, on_start_thread, on_stop_thread))
                    {
                        // build path to component to load
                        std::string libname(HPX_MAKE_DLL_STRING(parcelport));
                        lib /= hpx::util::create_path(libname);
                        if (!load_parcelport(cfg, instance, parcelport, lib, isenabled, on_start_thread, on_stop_thread))
                        {
                            continue;   // next please :-P
                        }
                    }
#endif
                }
            }
            catch (hpx::exception const& e) {
                LRT_(warning) << "caught exception while loading " << instance
                              << ", " << e.get_error_code().get_message()
                              << ": " << e.what();
            }
        } // for
    }

    std::vector<std::string> parcelhandler::load_runtime_configuration()
    {
        /// TODO: properly hide this in plugins ...
        std::vector<std::string> ini_defs;

        using namespace boost::assign;
        ini_defs +=
            "[hpx.parcel]",
            "address = ${HPX_PARCEL_SERVER_ADDRESS:" HPX_INITIAL_IP_ADDRESS "}",
            "port = ${HPX_PARCEL_SERVER_PORT:"
                BOOST_PP_STRINGIZE(HPX_INITIAL_IP_PORT) "}",
            "bootstrap = ${HPX_PARCEL_BOOTSTRAP:" HPX_PARCEL_BOOTSTRAP "}",
            "max_connections = ${HPX_PARCEL_MAX_CONNECTIONS:"
                BOOST_PP_STRINGIZE(HPX_PARCEL_MAX_CONNECTIONS) "}",
            "max_connections_per_locality = ${HPX_PARCEL_MAX_CONNECTIONS_PER_LOCALITY:"
                BOOST_PP_STRINGIZE(HPX_PARCEL_MAX_CONNECTIONS_PER_LOCALITY) "}",
            "max_message_size = ${HPX_PARCEL_MAX_MESSAGE_SIZE:"
                BOOST_PP_STRINGIZE(HPX_PARCEL_MAX_MESSAGE_SIZE) "}",
            "max_outbound_message_size = ${HPX_PARCEL_MAX_OUTBOUND_MESSAGE_SIZE:"
                BOOST_PP_STRINGIZE(HPX_PARCEL_MAX_OUTBOUND_MESSAGE_SIZE) "}",
#ifdef BOOST_BIG_ENDIAN
            "endian_out = ${HPX_PARCEL_ENDIAN_OUT:big}",
#else
            "endian_out = ${HPX_PARCEL_ENDIAN_OUT:little}",
#endif
            "array_optimization = ${HPX_PARCEL_ARRAY_OPTIMIZATION:1}",
            "zero_copy_optimization = ${HPX_PARCEL_ZERO_COPY_OPTIMIZATION:"
                "$[hpx.parcel.array_optimization]}",
            "enable_security = ${HPX_PARCEL_ENABLE_SECURITY:0}",
            "async_serialization = ${HPX_PARCEL_ASYNC_SERIALIZATION:1}"
            ;


        return ini_defs;
    }

    boost::shared_ptr<parcelport> parcelhandler::get_bootstrap_parcelport() const
    {
        if(!pports_.empty())
        {
            std::string cfgkey("hpx.parcel.bootstrap");
            pports_type::const_iterator it = pports_.find(get_priority(get_config_entry(cfgkey, "tcp")));
            if(it != pports_.end() && it->first > 0) return it->second;
        }
        BOOST_FOREACH(pports_type::value_type const & pp, pports_)
        {
            if(pp.first > 0 && pp.second->can_bootstrap())
                return pp.second;
        }
        return boost::shared_ptr<parcelport>();
    }


    void parcelhandler::initialize()
    {
        HPX_ASSERT(parcels_);

        parcels_->set_parcelhandler(this);
        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            if(pp.second != get_bootstrap_parcelport())
            {
                if(pp.first > 0)
                    pp.second->run(false);
            }
            else
                pp.second->register_event_handler(boost::bind(&parcelhandler::parcel_sink, this, _1));

        }
    }

    void parcelhandler::list_parcelport(util::osstream& strm, std::string const& ppname, int priority,
        bool bootstrap) const
    {
        strm << "parcel port: " << ppname;

        std::string cfgkey("hpx.parcel." + ppname + ".enable");
        std::string enabled = get_config_entry(cfgkey, "0");
        strm << ", " << (hpx::util::safe_lexical_cast<int>(enabled, 0) ? "" : "not ")
             << "enabled";

        if (bootstrap)
            strm << ", bootstrap";

        strm << ", priority " << priority;

        strm << '\n';
    }

    // list available parcel ports
    void parcelhandler::list_parcelports(util::osstream& strm) const
    {
        BOOST_FOREACH(pports_type::value_type const & pp, pports_)
        {
            list_parcelport(
                strm
              , pp.second->type()
              , pp.second->priority()
              , pp.second == get_bootstrap_parcelport()
            );
        }
        strm << '\n';
    }

    bool parcelhandler::load_parcelport(util::section& ini,
        std::string const& instance, std::string const& plugin,
        boost::filesystem::path const& lib, bool isenabled,
        HPX_STD_FUNCTION<void(std::size_t, char const*)> const& on_start_thread,
        HPX_STD_FUNCTION<void()> const& on_stop_thread)
    {
        namespace fs = boost::filesystem;
        if (fs::extension(lib) != HPX_SHARED_LIB_EXTENSION)
            return false;

        try {
            // get the handle of the library
            error_code ec(lightweight);
            hpx::util::plugin::dll d(lib.string(), HPX_MANGLE_STRING(plugin));

            d.load_library(ec);
            if (ec) {
                LRT_(warning) << "dynamic loading failed: " << lib.string()
                              << ": " << instance << ": " << get_error_what(ec);
                return false;
            }

            // initialize the factory instance using the preferences from the
            // ini files
            util::section const* glob_ini = NULL;
            if (ini.has_section("settings"))
                glob_ini = ini.get_section("settings");

            util::section const* plugin_ini = NULL;
            std::string plugin_section("hpx.parcel." + instance);
            if (ini.has_section(plugin_section))
                plugin_ini = ini.get_section(plugin_section);

            if (0 != plugin_ini &&
                "0" != plugin_ini->get_entry("no_factory", "0"))
            {
                return false;
            }

            // get the factory
            hpx::util::plugin::plugin_factory<plugins::plugin_factory_base>
                pf (d, "factory");

            // create the component factory object, if not disabled
            boost::shared_ptr<plugins::plugin_factory_base> factory (
                pf.create(plugin, ec, glob_ini, plugin_ini, isenabled));
            if (ec) {
                LRT_(warning) << "dynamic loading failed: " << lib.string()
                              << ": " << instance << ": " << get_error_what(ec);
                return false;
            }

            attach_parcelport(
                boost::shared_ptr<parcelport>(
                    boost::static_pointer_cast<plugins::parcelport_factory_base>(
                        factory
                    )->create(
                        hpx::get_config()
                      , on_start_thread
                      , on_stop_thread
                    )
                )
            );

            LRT_(info) << "dynamic loading succeeded: " << lib.string()
                        << ": " << instance;
        }
        catch (hpx::exception const&) {
            throw;
        }
        catch (std::logic_error const& e) {
            LRT_(warning) << "dynamic loading failed: " << lib.string()
                          << ": " << instance << ": " << e.what();
            return false;
        }
        catch (std::exception const& e) {
            LRT_(warning) << "dynamic loading failed: " << lib.string()
                          << ": " << instance << ": " << e.what();
            return false;
        }
        return true;    // component got loaded
    }

    void parcelhandler::attach_parcelport(boost::shared_ptr<parcelport> const& pp)
    {
        if(!pp) return;

        // register our callback function with the parcelport
        pp->register_event_handler(boost::bind(&parcelhandler::parcel_sink, this, _1));

        // add the new parcelport to the list of parcel-ports we care about
        int priority = pp->priority();
        std::string cfgkey(std::string("hpx.parcel.") + pp->type() + ".enable");
        if(get_config_entry(cfgkey, "0") != "1")
        {
            priority = -priority;
        }
        pports_[priority] = pp;
        priority_[pp->type()] = priority;

        // add the endpoint of the new parcelport
        HPX_ASSERT(pp->type() == pp->here().type());
        if(priority > 0)
            endpoints_[pp->type()] = pp->here();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Make sure the specified locality is not held by any
    /// connection caches anymore
    void parcelhandler::remove_from_connection_cache(endpoints_type const& endpoints)
    {
        BOOST_FOREACH(endpoints_type::value_type const & loc, endpoints)
        {
            BOOST_FOREACH(pports_type::value_type & pp, pports_)
            {
                if(std::string(pp.second->type()) == loc.second.type())
                {
                    pp.second->remove_from_connection_cache(loc.second);
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelhandler::do_background_work(bool stop_buffering)
    {
        // flush all parcel buffers
        {
            mutex_type::scoped_lock l(handlers_mtx_);

            message_handler_map::iterator end = handlers_.end();
            for (message_handler_map::iterator it = handlers_.begin(); it != end; ++it)
            {
                if ((*it).second)
                {
                    boost::shared_ptr<policies::message_handler> p((*it).second);
                    util::scoped_unlock<mutex_type::scoped_lock> ul(l);
                    p->flush(stop_buffering);
                }
            }
        }

        // make sure all pending parcels are being handled
        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            pp.second->do_background_work();
        }
    }

    void parcelhandler::stop(bool blocking)
    {
        // now stop all parcel ports
        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            if(pp.first > 0)
            {
                pp.second->stop(blocking);
            }
        }
    }

    naming::resolver_client& parcelhandler::get_resolver()
    {
        return resolver_;
    }

    naming::gid_type const& parcelhandler::get_locality() const
    {
        return resolver_.get_local_locality();
    }

    bool parcelhandler::get_raw_remote_localities(
        std::vector<naming::gid_type>& locality_ids,
        components::component_type type, error_code& ec) const
    {
        std::vector<naming::gid_type> allprefixes;

        bool result = resolver_.get_localities(allprefixes, type, ec);
        if (ec || !result) return false;

        std::remove_copy(allprefixes.begin(), allprefixes.end(),
            std::back_inserter(locality_ids), get_locality());

        return !locality_ids.empty();
    }

    bool parcelhandler::get_raw_localities(
        std::vector<naming::gid_type>& locality_ids,
        components::component_type type, error_code& ec) const
    {
        bool result = resolver_.get_localities(locality_ids, type, ec);
        if (ec || !result) return false;

        return !locality_ids.empty();
    }

    std::pair<boost::shared_ptr<parcelport>, locality> parcelhandler::find_appropriate_destination(
        naming::gid_type const& dest_gid)
    {
        endpoints_type const & dest_endpoints = resolver_.resolve_locality(dest_gid);

        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            if(pp.first > 0)
            {
                locality const & dest = find_endpoint(dest_endpoints, pp.second->type());
                if(dest && pp.second->can_connect(dest, use_alternative_parcelports_))
                    return std::make_pair(pp.second, dest);
            }
        }

        HPX_THROW_EXCEPTION(network_error, "parcelhandler::find_appropriate_destination",
            "The locality gid cannot be resolved to a valid endpoint. No valid parcelport configured.");
        return std::pair<boost::shared_ptr<parcelport>, locality>();
    }

    locality parcelhandler::find_endpoint(endpoints_type const & eps, std::string const & name)
    {
        endpoints_type::const_iterator it = eps.find(name);
        if(it != eps.end()) return it->second;
        return locality();
    }

    /// Return the reference to an existing io_service
    util::io_service_pool* parcelhandler::get_thread_pool(char const* name)
    {
        util::io_service_pool* result = 0;
        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            result = pp.second->get_thread_pool(name);
            if (result) return result;
        }
        return result;
    }

    void parcelhandler::rethrow_exception()
    {
        boost::exception_ptr exception;
        {
            // store last error for now only
            mutex_type::scoped_lock l(mtx_);
            boost::swap(exception, exception_);
        }

        if (exception) {
            // report any pending exceptions
            boost::rethrow_exception(exception);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        // The original parcel-sent handler is wrapped to keep the parcel alive
        // until after the data has been reliably sent (which is needed for zero
        // copy serialization).
        void parcel_sent_handler(boost::system::error_code const& ec,
            parcelhandler::write_handler_type const& f, parcel const& p)
        {
            // invoke the original handler
            f(ec, p);

            // inform termination detection of a sent message
            if (!p.does_termination_detection())
                hpx::detail::dijkstra_make_black();
        }
    }

    void parcelhandler::put_parcel(parcel& p, write_handler_type const& f)
    {
        rethrow_exception();

        // properly initialize parcel
        init_parcel(p);

        naming::id_type const* ids = p.get_destinations();
        naming::address* addrs = p.get_destination_addrs();

        bool resolved_locally = true;

#if !defined(HPX_SUPPORT_MULTIPLE_PARCEL_DESTINATIONS)
        if (!addrs[0])
        {
            resolved_locally = resolver_.resolve_local(ids[0], addrs[0]);
        }
#else
        std::size_t size = p.size();

        if (0 == size) {
            HPX_THROW_EXCEPTION(network_error, "parcelhandler::put_parcel",
                "no destination address given");
            return;
        }

        if (1 == size) {
            if (!addrs[0])
                resolved_locally = resolver_.resolve_local(ids[0], addrs[0]);
        }
        else {
            boost::dynamic_bitset<> locals;
            resolved_locally = resolver_.resolve_local(ids, addrs, size, locals);
        }
#endif

        if (!p.get_parcel_id())
            p.set_parcel_id(parcel::generate_unique_id());

        // If we were able to resolve the address(es) locally we send the
        // parcel directly to the destination.
        if (resolved_locally) {

            // re-wrap the given parcel-sent handler
            using util::placeholders::_1;
            write_handler_type wrapped_f =
                util::bind(&detail::parcel_sent_handler, _1, f, p);

            // dispatch to the message handler which is associated with the
            // encapsulated action
            typedef std::pair<boost::shared_ptr<parcelport>, locality> destination_pair;
            destination_pair dest = find_appropriate_destination(addrs[0].locality_);
            policies::message_handler* mh =
                p.get_message_handler(this, dest.second);

            if (mh) {
                mh->put_parcel(dest.second, p, wrapped_f);
                return;
            }

            dest.first->put_parcel(dest.second, p, wrapped_f);
            return;
        }

        // At least one of the addresses is locally unknown, route the parcel
        // to the AGAS managing the destination.
        ++count_routed_;
        resolver_.route(p, f);
    }

    std::size_t parcelhandler::get_outgoing_queue_length(bool reset) const
    {
        std::size_t parcel_count = 0;
        BOOST_FOREACH(pports_type::value_type const& pp, pports_)
        {
            parcel_count += pp.second->get_pending_parcels_count(reset);
        }
        return parcel_count;
    }

    ///////////////////////////////////////////////////////////////////////////
    // default callback for put_parcel
    void parcelhandler::default_write_handler(
        boost::system::error_code const& ec, parcel const& p)
    {
        if (ec) {
            // If we are in a stopped state, ignore some errors
            if (hpx::is_stopped_or_shutting_down())
            {
                if (ec == boost::asio::error::connection_aborted ||
                    ec == boost::asio::error::broken_pipe ||
                    ec == boost::asio::error::not_connected ||
                    ec == boost::asio::error::eof)
                {
                    return;
                }
            }

            boost::exception_ptr exception =
                hpx::detail::get_exception(hpx::exception(ec),
                    "parcelhandler::default_write_handler", __FILE__,
                    __LINE__, parcelset::dump_parcel(p));

            // store last error for now only
            mutex_type::scoped_lock l(mtx_);
            exception_ = exception;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    policies::message_handler* parcelhandler::get_message_handler(
        char const* action, char const* message_handler_type,
        std::size_t num_messages, std::size_t interval,
        locality const& loc, error_code& ec)
    {
        mutex_type::scoped_lock l(handlers_mtx_);
        handler_key_type key(loc, action);
        message_handler_map::iterator it = handlers_.find(key);
        if (it == handlers_.end()) {
            boost::shared_ptr<policies::message_handler> p;

            {
                util::scoped_unlock<mutex_type::scoped_lock> ul(l);
                p.reset(hpx::create_message_handler(message_handler_type,
                    action, find_parcelport(loc.type()), num_messages, interval, ec));
            }

            it = handlers_.find(key);
            if (it != handlers_.end()) {
                // if some other thread has created the entry in the mean time
                l.unlock();
                if (&ec != &throws) {
                    if ((*it).second.get())
                        ec = make_success_code();
                    else
                        ec = make_error_code(bad_parameter, lightweight);
                }
                return (*it).second.get();
            }

            if (ec || !p.get()) {
                // insert an empty entry into the map to avoid trying to
                // create this handler again
                p.reset();
                std::pair<message_handler_map::iterator, bool> r =
                    handlers_.insert(message_handler_map::value_type(key, p));

                l.unlock();
                if (!r.second) {
                    HPX_THROWS_IF(ec, internal_server_error,
                        "parcelhandler::get_message_handler",
                        "could not store empty message handler");
                    return 0;
                }
                return 0;           // no message handler available
            }

            std::pair<message_handler_map::iterator, bool> r =
                handlers_.insert(message_handler_map::value_type(key, p));

            l.unlock();
            if (!r.second) {
                HPX_THROWS_IF(ec, internal_server_error,
                    "parcelhandler::get_message_handler",
                    "could not store newly created message handler");
                return 0;
            }
            it = r.first;
        }
        else if (!(*it).second.get()) {
            l.unlock();
            if (&ec != &throws)
                ec = make_error_code(bad_parameter, lightweight);
            return 0;           // no message handler available
        }

        if (&ec != &throws)
            ec = make_success_code();

        return (*it).second.get();
    }

    ///////////////////////////////////////////////////////////////////////////
    bool parcelhandler::enable(bool new_state)
    {
        new_state = enable_parcel_handling_.exchange(new_state, boost::memory_order_acquire);
        BOOST_FOREACH(pports_type::value_type & pp, pports_)
        {
            if(pp.first > 0)
                pp.second->enable(enable_parcel_handling_);
        }

        return new_state;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Performance counter data

    // number of parcels sent
    std::size_t parcelhandler::get_parcel_send_count(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_parcel_send_count(reset) : 0;
    }

    // number of parcels routed
    boost::int64_t parcelhandler::get_parcel_routed_count(bool reset)
    {
        return util::get_and_reset_value(count_routed_, reset);
    }

    // number of messages sent
    std::size_t parcelhandler::get_message_send_count(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_message_send_count(reset) : 0;
    }

    // number of parcels received
    std::size_t parcelhandler::get_parcel_receive_count(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_parcel_receive_count(reset) : 0;
    }

    // number of messages received
    std::size_t parcelhandler::get_message_receive_count(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_message_receive_count(reset) : 0;
    }

    // the total time it took for all sends, from async_write to the
    // completion handler (nanoseconds)
    boost::int64_t parcelhandler::get_sending_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_sending_time(reset) : 0;
    }

    // the total time it took for all receives, from async_read to the
    // completion handler (nanoseconds)
    boost::int64_t parcelhandler::get_receiving_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_receiving_time(reset) : 0;
    }

    // the total time it took for all sender-side serialization operations
    // (nanoseconds)
    boost::int64_t parcelhandler::get_sending_serialization_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_sending_serialization_time(reset) : 0;
    }

    // the total time it took for all receiver-side serialization
    // operations (nanoseconds)
    boost::int64_t parcelhandler::get_receiving_serialization_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_receiving_serialization_time(reset) : 0;
    }

#if defined(HPX_HAVE_SECURITY)
    // the total time it took for all sender-side security operations
    // (nanoseconds)
    boost::int64_t parcelhandler::get_sending_security_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_sending_security_time(reset) : 0;
    }

    // the total time it took for all receiver-side security
    // operations (nanoseconds)
    boost::int64_t parcelhandler::get_receiving_security_time(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_receiving_security_time(reset) : 0;
    }
#endif

    // total data sent (bytes)
    std::size_t parcelhandler::get_data_sent(std::string const& pp_type,
        bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_data_sent(reset) : 0;
    }

    // total data (uncompressed) sent (bytes)
    std::size_t parcelhandler::get_raw_data_sent(std::string const& pp_type,
        bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_raw_data_sent(reset) : 0;
    }

    // total data received (bytes)
    std::size_t parcelhandler::get_data_received(std::string const& pp_type,
        bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_data_received(reset) : 0;
    }

    // total data (uncompressed) received (bytes)
    std::size_t parcelhandler::get_raw_data_received(std::string const& pp_type,
        bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_raw_data_received(reset) : 0;
    }

    boost::int64_t parcelhandler::get_buffer_allocate_time_sent(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_buffer_allocate_time_sent(reset) : 0;
    }
    boost::int64_t parcelhandler::get_buffer_allocate_time_received(
        std::string const& pp_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_buffer_allocate_time_received(reset) : 0;
    }

    // connection stack statistics
    boost::int64_t parcelhandler::get_connection_cache_statistics(
        std::string const& pp_type,
        parcelport::connection_cache_statistics_type stat_type, bool reset) const
    {
        error_code ec(lightweight);
        parcelport* pp = find_parcelport(pp_type, ec);
        return pp ? pp->get_connection_cache_statistics(stat_type, reset) : 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    void parcelhandler::register_counter_types()
    {
        // register connection specific counters
        BOOST_FOREACH(pports_type::value_type const & pp, pports_)
        {
            register_counter_types(pp.second->type());
        }

        // register common counters
        HPX_STD_FUNCTION<boost::int64_t(bool)> incoming_queue_length(
            boost::bind(&parcelhandler::get_incoming_queue_length, this, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> outgoing_queue_length(
            boost::bind(&parcelhandler::get_outgoing_queue_length, this, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> outgoing_routed_count(
            boost::bind(&parcelhandler::get_parcel_routed_count, this, ::_1));

        performance_counters::generic_counter_type_data const counter_types[] =
        {
            { "/parcelqueue/length/receive",
              performance_counters::counter_raw,
              "returns the number current length of the queue of incoming parcels",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, incoming_queue_length, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { "/parcelqueue/length/send",
              performance_counters::counter_raw,
              "returns the number current length of the queue of outgoing parcels",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, outgoing_queue_length, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { "/parcels/count/routed",
              performance_counters::counter_raw,
              "returns the number of (outbound) parcel routed through the "
                  "responsible AGAS service",
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, outgoing_routed_count, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            }
        };
        performance_counters::install_counter_types(
            counter_types, sizeof(counter_types)/sizeof(counter_types[0]));
    }

    void parcelhandler::register_counter_types(std::string const& pp_type)
    {
        HPX_STD_FUNCTION<boost::int64_t(bool)> num_parcel_sends(
            boost::bind(&parcelhandler::get_parcel_send_count, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> num_parcel_receives(
            boost::bind(&parcelhandler::get_parcel_receive_count, this, pp_type, ::_1));

        HPX_STD_FUNCTION<boost::int64_t(bool)> num_message_sends(
            boost::bind(&parcelhandler::get_message_send_count, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> num_message_receives(
            boost::bind(&parcelhandler::get_message_receive_count, this, pp_type, ::_1));

        HPX_STD_FUNCTION<boost::int64_t(bool)> sending_time(
            boost::bind(&parcelhandler::get_sending_time, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> receiving_time(
            boost::bind(&parcelhandler::get_receiving_time, this, pp_type, ::_1));

        HPX_STD_FUNCTION<boost::int64_t(bool)> sending_serialization_time(
            boost::bind(&parcelhandler::get_sending_serialization_time, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> receiving_serialization_time(
            boost::bind(&parcelhandler::get_receiving_serialization_time, this, pp_type, ::_1));

#if defined(HPX_HAVE_SECURITY)
        HPX_STD_FUNCTION<boost::int64_t(bool)> sending_security_time(
            boost::bind(&parcelhandler::get_sending_security_time, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> receiving_security_time(
            boost::bind(&parcelhandler::get_receiving_security_time, this, pp_type, ::_1));
#endif
        HPX_STD_FUNCTION<boost::int64_t(bool)> data_sent(
            boost::bind(&parcelhandler::get_data_sent, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> data_received(
            boost::bind(&parcelhandler::get_data_received, this, pp_type, ::_1));

        HPX_STD_FUNCTION<boost::int64_t(bool)> data_raw_sent(
            boost::bind(&parcelhandler::get_raw_data_sent, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> data_raw_received(
            boost::bind(&parcelhandler::get_raw_data_received, this, pp_type, ::_1));

        HPX_STD_FUNCTION<boost::int64_t(bool)> buffer_allocate_time_sent(
            boost::bind(&parcelhandler::get_buffer_allocate_time_sent, this, pp_type, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> buffer_allocate_time_received(
            boost::bind(&parcelhandler::get_buffer_allocate_time_received, this, pp_type, ::_1));

        performance_counters::generic_counter_type_data const counter_types[] =
        {
            { boost::str(boost::format("/parcels/count/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of parcels sent using the %s "
                  "connection type for the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_parcel_sends, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/parcels/count/%s/received") % pp_type),
               performance_counters::counter_raw,
              boost::str(boost::format("returns the number of parcels received using the %s "
                  "connection type for the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_parcel_receives, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/messages/count/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of messages sent using the %s "
                  "connection type for the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_message_sends, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/messages/count/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of messages received using the %s "
                  "connection type for the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, num_message_receives, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },

            { boost::str(boost::format("/data/time/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time between the start of "
                  "each asynchronous write and the invocation of the write callback "
                  "using the %s connection type for the referenced locality") %
                      pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, sending_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
            { boost::str(boost::format("/data/time/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time between the start of "
                  "each asynchronous read and the invocation of the read callback "
                  "using the %s connection type for the referenced locality") %
                      pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, receiving_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
            { boost::str(boost::format("/serialize/time/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time required to serialize "
                  "all sent parcels using the %s connection type for the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, sending_serialization_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
            { boost::str(boost::format("/serialize/time/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time required to de-serialize "
                  "all received parcels using the %s connection type for the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, receiving_serialization_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },

#if defined(HPX_HAVE_SECURITY)
            { boost::str(boost::format("/security/time/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time required to perform "
                  "tasks related to security in the parcel layer for all sent parcels "
                  "using the %s connection type for the referenced locality") %
                        pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, sending_security_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
            { boost::str(boost::format("/security/time/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the total time required to perform "
                  "tasks related to security in the parcel layer for all received parcels "
                  "using the %s connection type for the referenced locality") %
                        pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, receiving_security_time, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
#endif
            { boost::str(boost::format("/data/count/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the amount of (uncompressed) parcel "
                  "argument data sent using the %s connection type by the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, data_raw_sent, _2),
              &performance_counters::locality_counter_discoverer,
              "bytes"
            },
            { boost::str(boost::format("/data/count/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the amount of (uncompressed) parcel "
                  "argument data received using the %s connection type by the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, data_raw_received, _2),
              &performance_counters::locality_counter_discoverer,
              "bytes"
            },
            { boost::str(boost::format("/serialize/count/%s/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the amount of parcel data (including "
                  "headers, possibly compressed) sent using the %s connection type "
                  "by the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, data_sent, _2),
              &performance_counters::locality_counter_discoverer,
              "bytes"
            },
            { boost::str(boost::format("/serialize/count/%s/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the amount of parcel data (including "
                  "headers, possibly compressed) received using the %s connection type "
                  "by the referenced locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, data_received, _2),
              &performance_counters::locality_counter_discoverer,
              "bytes"
            },
            { boost::str(boost::format("/parcels/time/%s/buffer_allocate/received") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the time needed to allocate the buffers for serializing using the %s connection type") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, buffer_allocate_time_received, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
            { boost::str(boost::format("/parcels/time/%s/buffer_allocate/sent") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the time needed to allocate the buffers for serializing using the %s connection type") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, buffer_allocate_time_sent, _2),
              &performance_counters::locality_counter_discoverer,
              "ns"
            },
        };
        performance_counters::install_counter_types(
            counter_types, sizeof(counter_types)/sizeof(counter_types[0]));

        // register connection specific performance counters related to connection
        // caches
        HPX_STD_FUNCTION<boost::int64_t(bool)> cache_insertions(
            boost::bind(&parcelhandler::get_connection_cache_statistics,
                this, pp_type, parcelport::connection_cache_insertions, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> cache_evictions(
            boost::bind(&parcelhandler::get_connection_cache_statistics,
                this, pp_type, parcelport::connection_cache_evictions, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> cache_hits(
            boost::bind(&parcelhandler::get_connection_cache_statistics,
                this, pp_type, parcelport::connection_cache_hits, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> cache_misses(
            boost::bind(&parcelhandler::get_connection_cache_statistics,
                this, pp_type, parcelport::connection_cache_misses, ::_1));
        HPX_STD_FUNCTION<boost::int64_t(bool)> cache_reclaims(
            boost::bind(&parcelhandler::get_connection_cache_statistics,
                this, pp_type, parcelport::connection_cache_reclaims, ::_1));

        performance_counters::generic_counter_type_data const connection_cache_types[] =
        {
            { boost::str(boost::format("/parcelport/count/%s/cache-insertions") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of cache insertions while accessing "
                  "the connection cache for the %s connection type on the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, cache_insertions, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/parcelport/count/%s/cache-evictions") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of cache evictions while accessing "
                  "the connection cache for the %s connection type on the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, cache_evictions, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/parcelport/count/%s/cache-hits") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of cache hits while accessing "
                  "the connection cache for the %s connection type on the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, cache_hits, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/parcelport/count/%s/cache-misses") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of cache misses while accessing "
                  "the connection cache for the %s connection type on the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, cache_misses, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            },
            { boost::str(boost::format("/parcelport/count/%s/cache-reclaims") % pp_type),
              performance_counters::counter_raw,
              boost::str(boost::format("returns the number of cache reclaims while accessing "
                  "the connection cache for the %s connection type on the referenced "
                  "locality") % pp_type),
              HPX_PERFORMANCE_COUNTER_V1,
              boost::bind(&performance_counters::locality_raw_counter_creator,
                  _1, cache_reclaims, _2),
              &performance_counters::locality_counter_discoverer,
              ""
            }
        };
        performance_counters::install_counter_types(connection_cache_types,
            sizeof(connection_cache_types)/sizeof(connection_cache_types[0]));
    }
}}


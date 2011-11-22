////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach and Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/config.hpp>
#include <hpx/exception.hpp>
#include <hpx/hpx.hpp>
#include <hpx/runtime/agas/addressing_service.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/include/performance_counters.hpp>

#include <boost/format.hpp>

namespace hpx { namespace agas
{

addressing_service::addressing_service(
    parcelset::parcelport& pp
  , util::runtime_configuration const& ini_
  , runtime_mode runtime_type_
    )
  : console_cache_(0)
  , resolve_throttle_(ini_.get_agas_max_resolve_requests())
  , service_type(ini_.get_agas_service_mode())
  , runtime_type(runtime_type_)
  , caching_(ini_.get_agas_caching_mode())
  , range_caching_(caching_ ? ini_.get_agas_range_caching_mode() : false)
  , here_(get_runtime().here())
  , rts_lva_(get_runtime().get_runtime_support_lva())
  , state_(starting)
  , prefix_()
{ // {{{
    // boot the parcel port
    pp.run(false);

    create_big_boot_barrier(pp, ini_, runtime_type_);

    if (caching_)
        gva_cache_.reserve(ini_.get_agas_gva_cache_size());

    if (service_type == service_mode_bootstrap)
        launch_bootstrap(pp, ini_);
    else
        launch_hosted(pp, ini_);
} // }}}

void addressing_service::launch_bootstrap(
    parcelset::parcelport& pp
  , util::runtime_configuration const& ini_
    )
{ // {{{
    bootstrap = boost::make_shared<bootstrap_data_type>();

    const naming::locality ep = ini_.get_agas_locality();
    const naming::gid_type here
        = naming::get_gid_from_prefix(HPX_AGAS_BOOTSTRAP_PREFIX);

    const naming::gid_type primary_gid = bootstrap_primary_namespace_gid();
    const naming::gid_type component_gid = bootstrap_component_namespace_gid();
    const naming::gid_type symbol_gid = bootstrap_symbol_namespace_gid();

    gva primary_gva(ep,
        server::primary_namespace::get_component_type(), 1U,
            static_cast<void*>(&bootstrap->primary_ns_server));
    gva component_gva(ep,
        server::component_namespace::get_component_type(), 1U,
            static_cast<void*>(&bootstrap->component_ns_server));
    gva symbol_gva(ep,
        server::symbol_namespace::get_component_type(), 1U,
            static_cast<void*>(&bootstrap->symbol_ns_server));

    local_prefix(here);
    get_runtime().get_config().parse("assigned locality",
        boost::str(boost::format("hpx.locality=%1%")
                  % naming::get_prefix_from_gid(here)));

    request reqs[] =
    {
        request(primary_ns_allocate, ep, 3)
      , request(primary_ns_bind_gid, primary_gid, primary_gva)
      , request(primary_ns_bind_gid, component_gid, component_gva)
      , request(primary_ns_bind_gid, symbol_gid, symbol_gva)
    };

    for (std::size_t i = 0; i < (sizeof(reqs) / sizeof(request)); ++i)
        bootstrap->primary_ns_server.service(reqs[i]);

    bootstrap->symbol_ns_server.service(
        request(symbol_ns_bind, "/locality(agas#0)", here));

    if (runtime_type == runtime_mode_console)
        bootstrap->symbol_ns_server.service(
            request(symbol_ns_bind, "/locality(console)", here));

    naming::gid_type lower, upper;
    get_id_range(ep, HPX_INITIAL_GID_RANGE, lower, upper);
    get_runtime().get_id_pool().set_range(lower, upper);

    get_big_boot_barrier().wait();

    state_.store(running);
} // }}}

void addressing_service::launch_hosted(
    parcelset::parcelport& pp
  , util::runtime_configuration const& ini_
    )
{ // {{{
    hosted = boost::make_shared<hosted_data_type>();

    get_big_boot_barrier().wait();

    state_.store(running);
} // }}}

response addressing_service::service(
    request const& req
  , error_code& ec
    )
{ // {{{
    if (req.get_action_code() & primary_ns_service)
    {
        if (is_bootstrap())
            return bootstrap->primary_ns_server.service(req, ec);
        else
            return hosted->primary_ns_.service(req, ec);
    }

    else if (req.get_action_code() & component_ns_service)
    {
        if (is_bootstrap())
            return bootstrap->component_ns_server.service(req, ec);
        else
            return hosted->component_ns_.service(req, ec);
    }

    else if (req.get_action_code() & symbol_ns_service)
    {
        if (is_bootstrap())
            return bootstrap->symbol_ns_server.service(req, ec);
        else
            return hosted->symbol_ns_.service(req, ec);
    }

    HPX_THROWS_IF(ec, bad_action_code
        , "addressing_service::service"
        , "invalid action code encountered in request")
    return response();
} // }}}

bool addressing_service::register_locality(
    naming::locality const& ep
  , naming::gid_type& prefix
  , error_code& ec
    )
{ // {{{
    try {
        request req(primary_ns_allocate, ep, 0);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return false;

        prefix = naming::get_gid_from_prefix(rep.get_prefix());

        return true;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::allocate", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

boost::uint32_t addressing_service::resolve_locality(
    naming::locality const& ep
  , error_code& ec
    )
{ // {{{
    try {
        request req(primary_ns_resolve_locality, ep);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return 0;

        return rep.get_prefix();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::resolve_locality", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return 0;
    }
} // }}}

// TODO: We need to ensure that the locality isn't unbound while it still holds
// referenced objects.
bool addressing_service::unregister_locality(
    naming::locality const& ep
  , error_code& ec
    )
{ // {{{
    try {
        request req(primary_ns_free, ep);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return false;

        return true;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::unregister_locality", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::get_console_prefix(
    naming::gid_type& prefix
  , error_code& ec
    )
{ // {{{
    try {
        if (status() != running)
        {
            if (&ec != &throws)
                ec = make_success_code();
            return false;
        }

        if (is_console())
        {
            prefix = local_prefix();
            if (&ec != &throws)
                ec = make_success_code();
            return true;
        }

        mutex_type::scoped_lock lock(console_cache_mtx_);

        if (console_cache_)
        {
            prefix = naming::get_gid_from_prefix(console_cache_);
            if (&ec != &throws)
                ec = make_success_code();
            return true;
        }

        request req(symbol_ns_resolve, "/locality(console)");
        response rep;

        if (is_bootstrap())
            rep = bootstrap->symbol_ns_server.service(req, ec);
        else
            rep = hosted->symbol_ns_.service(req, ec);

        if (!ec && (rep.get_gid() != naming::invalid_gid) &&
            (rep.get_status() == success))
        {
            prefix = rep.get_gid();

            console_cache_ = naming::get_prefix_from_gid(prefix);

            LAS_(debug) <<
                ( boost::format("caching console locality, prefix(%1%)")
                % console_cache_);

            return true;
        }

        return false;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::get_console_prefix", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::get_prefixes(
    std::vector<naming::gid_type>& prefixes
  , components::component_type type
  , error_code& ec
    )
{ // {{{ get_prefixes implementation
    try {
        if (type != components::component_invalid)
        {
            request req(component_ns_resolve_id, type);
            response rep;

            if (is_bootstrap())
                rep = bootstrap->component_ns_server.service(req, ec);
            else
                rep = hosted->component_ns_.service(req, ec);

            if (ec || (success != rep.get_status()))
                return false;

            const std::vector<boost::uint32_t> p = rep.get_localities();

            if (!p.size())
                return false;

            prefixes.clear();
            for (boost::uint64_t i = 0; i < p.size(); ++i)
                prefixes.push_back(naming::get_gid_from_prefix(p[i]));

            return true;
        }

        else
        {
            request req(primary_ns_localities);
            response rep;

            if (is_bootstrap())
                rep = bootstrap->primary_ns_server.service(req, ec);
            else
                rep = hosted->primary_ns_.service(req, ec);

            if (ec || (success != rep.get_status()))
                return false;

            const std::vector<boost::uint32_t> p = rep.get_localities();

            if (!p.size())
                return false;

            prefixes.clear();
            for (boost::uint64_t i = 0; i < p.size(); ++i)
                prefixes.push_back(naming::get_gid_from_prefix(p[i]));

            return true;
        }
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::get_prefixes", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

components::component_type addressing_service::get_component_id(
    std::string const& name
  , error_code& ec
    )
{ /// {{{
    try {
        request req(component_ns_bind_name, name);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->component_ns_server.service(req, ec);
        else
            rep = hosted->component_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return components::component_invalid;

        return (components::component_type) rep.get_component_type();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::get_component_id", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return components::component_invalid;
    }
} // }}}

void addressing_service::iterate_types(
    iterate_types_function_type const& f
  , error_code& ec
    )
{ // {{{
    try {
        request req(component_ns_iterate_types, f);

        if (is_bootstrap())
            bootstrap->symbol_ns_server.service(req, ec);
        else
            hosted->symbol_ns_.service(req, ec);
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::iterate_types"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }
    }
} // }}}

components::component_type addressing_service::register_factory(
    boost::uint32_t prefix
  , std::string const& name
  , error_code& ec
    )
{ // {{{
    try {
        request req(component_ns_bind_prefix, name, prefix);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->component_ns_server.service(req, ec);
        else
            rep = hosted->component_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return components::component_invalid;

        return (components::component_type) rep.get_component_type();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(),
                "addressing_service::register_factory", e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return components::component_invalid;
    }
} // }}}

bool addressing_service::route_parcel(
    parcelset::parcel const& p
    )
{
    if (is_bootstrap())
        return bootstrap->primary_ns_server.route(p);
    else
        return hosted->primary_ns_.route(p);
}

///////////////////////////////////////////////////////////////////////////////
struct lock_semaphore
{
    lock_semaphore(lcos::local_counting_semaphore& sem)
      : sem_(sem)
    {
        // this needs to be invoked from a px-thread
        BOOST_ASSERT(NULL != threads::get_self_ptr());
        sem_.wait(1);
    }

    ~lock_semaphore()
    {
        sem_.signal(1);
    }

    lcos::local_counting_semaphore& sem_;
};

template <typename Pool, typename Future, typename Promise>
struct checkout_promise
{
    checkout_promise(Pool& pool, Promise*& promise)
      : result_ok_(false), pool_(pool), promise_(promise)
    {
        pool_.dequeue(promise_);
        BOOST_ASSERT(promise_);

        promise_->reset(); // reset the promise
    }
    ~checkout_promise()
    {
        // return the future to the pool
        if (result_ok_)
            pool_.enqueue(promise_);
    }

    Future* operator->() { return reinterpret_cast<Future*>(promise_); }
    void set_ok() { result_ok_ = true; }

private:
    bool result_ok_;
    Pool& pool_;
    Promise*& promise_;
};

///////////////////////////////////////////////////////////////////////////////
bool addressing_service::get_id_range(
    naming::locality const& ep
  , boost::uint64_t count
  , naming::gid_type& lower_bound
  , naming::gid_type& upper_bound
  , error_code& ec
    )
{ // {{{ get_id_range implementation
    typedef lcos::eager_future<server::primary_namespace::service_action>
        future_type;

    lcos::promise<response>* f = 0;

    try {
        request req(primary_ns_allocate, ep, count);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);

        else
        {
            // WARNING: this deadlocks if AGAS is unresponsive and all response
            // futures are checked out and pending.

            // wait for the semaphore to become available
            lock_semaphore lock(hosted->promise_pool_semaphore_);

            // get a future
            typedef checkout_promise<
                promise_pool_type
              , future_type
              , lcos::promise<response>
            > checkout_promise_type;

            checkout_promise_type cf(hosted->promise_pool_, f);

            // execute the action (synchronously)
            cf->apply(bootstrap_primary_namespace_id(), req);
            rep = cf->get(ec);

            cf.set_ok();
        }

        error const s = rep.get_status();

        if (ec || (success != s && repeated_request != s))
            return false;

        lower_bound = rep.get_lower_bound();
        upper_bound = rep.get_upper_bound();

        return success == s;
    }
    catch (hpx::exception const& e) {
        // Replace the future in the pool. To be able to return the future to
        // the pool, we'd have to ensure that all threads (pending, suspended,
        // active, or in flight) that might read/write from it are aborted.
        // There's no guarantee that the future isn't corrupted in some other
        // way, and the aforementioned code would be lengthy, and would have to
        // be meticulously exception-free. So, for now, we just allocate a new
        // future for the pool, and let the old future stay in memory.
        if (!is_bootstrap() && f)
        {
            hosted->promise_pool_.enqueue(new lcos::promise<response>);
            f->invalidate(boost::current_exception());
        }

        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::get_id_range"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::bind_range(
    naming::gid_type const& lower_id
  , boost::uint64_t count
  , naming::address const& baseaddr
  , boost::uint64_t offset
  , error_code& ec
    )
{ // {{{ bind_range implementation
    typedef lcos::eager_future<server::primary_namespace::service_action>
        future_type;

    lcos::promise<response>* f = 0;

    try {
        naming::locality const& ep = baseaddr.locality_;

        // Create a global virtual address from the legacy calling convention
        // parameters.
        gva const g(ep, baseaddr.type_, count, baseaddr.address_, offset);

        request req(primary_ns_bind_gid, lower_id, g);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);

        else
        {
            // WARNING: this deadlocks if AGAS is unresponsive and all response
            // futures are checked out and pending.

            // wait for the semaphore to become available
            lock_semaphore lock(hosted->promise_pool_semaphore_);

            // get a future
            typedef checkout_promise<
                promise_pool_type
              , future_type
              , lcos::promise<response>
            > checkout_promise_type;

            checkout_promise_type cf(hosted->promise_pool_, f);

            // execute the action (synchronously)
            cf->apply(bootstrap_primary_namespace_id(), req);
            rep = cf->get(ec);

            cf.set_ok();
        }

        const error s = rep.get_status();

        if (ec || (success != s && repeated_request != s))
            return false;

        if (caching_)
        {
            if (range_caching_)
                // Put the range into the cache.
                update_cache(lower_id, g, ec);

            else
            {
                // Only put the first GID in the range into the cache.
                gva const first_g = g.resolve(lower_id, lower_id);
                update_cache(lower_id, first_g, ec);
            }
        }

        if (ec)
            return false;

        return true;
    }
    catch (hpx::exception const& e) {
        // Replace the future in the pool. See get_id_range above for an
        // explanation.
        if (!is_bootstrap() && f)
        {
            hosted->promise_pool_.enqueue(new lcos::promise<response>);
            f->invalidate(boost::current_exception());
        }

        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::bind_range"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::unbind_range(
    naming::gid_type const& lower_id
  , boost::uint64_t count
  , naming::address& addr
  , error_code& ec
    )
{ // {{{ unbind_range implementation
    try {
        request req(primary_ns_unbind_gid, lower_id, count);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return false;

        // I'm afraid that this will break the first form of paged caching,
        // so it's commented out for now.
        //mutex_type::scoped_lock lock(hosted->gva_cache_mtx_);
        //gva_erase_policy ep(lower_id, count);
        //hosted->gva_cache_.erase(ep);
        addr.locality_ = rep.get_gva().endpoint;
        addr.type_ = rep.get_gva().type;
        addr.address_ = rep.get_gva().lva();

        return true;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::unbind_range"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::resolve(
    naming::gid_type const& id
  , naming::address& addr
  , bool try_cache
  , error_code& ec
    )
{ // {{{ resolve implementation
    try {
        // {{{ special cases

        // LVA-encoded GIDs (located on this machine)
        if (naming::strip_credit_from_gid(id.get_msb())
            == local_prefix().get_msb())
        {
            addr.locality_ = here_;

            // An LSB of 0 references the runtime support component
            if (0 == id.get_lsb() || id.get_lsb() == rts_lva_)
            {
                addr.type_ = components::component_runtime_support;
                addr.address_ = rts_lva_;
            }

            else
            {
                addr.type_ = components::component_memory;
                addr.address_ = id.get_lsb();
            }

            if (&ec != &throws)
                ec = make_success_code();

            return true;
        }

        // authoritative AGAS component address resolution
        else if (id == bootstrap_primary_namespace_gid())
        {
            addr = hosted->primary_ns_addr_;
            if (&ec != &throws)
                ec = make_success_code();
            return true;
        }

        else if (id == bootstrap_component_namespace_gid())
        {
            addr = hosted->component_ns_addr_;
            if (&ec != &throws)
                ec = make_success_code();
            return true;
        }

        else if (id == bootstrap_symbol_namespace_gid())
        {
            addr = hosted->symbol_ns_addr_;
            if (&ec != &throws)
                ec = make_success_code();
            return true;
        }
        // }}}

        lock_semaphore lock(resolve_throttle_);

        // Try the cache if applicable.
        if (try_cache && caching_)
        {
            if (resolve_cached(id, addr, ec))
                return true;

            if (ec)
                return false;
        }

        request req(primary_ns_resolve_gid, id);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return false;

        // Resolve the gva to the real resolved address (which is just a gva
        // with as fully resolved LVA and an offset of zero).
        gva const g = rep.get_gva().resolve(id, rep.get_base_gid());

        addr.locality_ = g.endpoint;
        addr.type_ = g.type;
        addr.address_ = g.lva();

        if (caching_)
        {
            if (range_caching_)
                // Put the gva range into the cache.
                update_cache(rep.get_base_gid(), rep.get_gva(), ec);
            else
                // Put the fully resolve gva into the cache.
                update_cache(id, g, ec);
        }

        if (ec)
            return false;

        if (&ec != &throws)
            ec = make_success_code();

        return true;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(), "addressing_service::resolve",
                e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::resolve_cached(
    naming::gid_type const& id
  , naming::address& addr
  , error_code& ec
    )
{ // {{{ resolve_cached implementation
    // {{{ special cases

    // LVA-encoded GIDs (located on this machine)
    if (naming::strip_credit_from_gid(id.get_msb()) == local_prefix().get_msb())
    {
        addr.locality_ = here_;

        // An LSB of 0 references the runtime support component
        if (0 == id.get_lsb() || id.get_lsb() == rts_lva_)
        {
            addr.type_ = components::component_runtime_support;
            addr.address_ = rts_lva_;
        }

        else
        {
            addr.type_ = components::component_memory;
            addr.address_ = id.get_lsb();
        }

        if (&ec != &throws)
            ec = make_success_code();

        return true;
    }

    // authoritative AGAS component address resolution
    else if (id == bootstrap_primary_namespace_gid())
    {
        addr = hosted->primary_ns_addr_;
        if (&ec != &throws)
            ec = make_success_code();
        return true;
    }

    else if (id == bootstrap_component_namespace_gid())
    {
        addr = hosted->component_ns_addr_;
        if (&ec != &throws)
            ec = make_success_code();
        return true;
    }

    else if (id == bootstrap_symbol_namespace_gid())
    {
        addr = hosted->symbol_ns_addr_;
        if (&ec != &throws)
            ec = make_success_code();
        return true;
    }
    // }}}

    // If caching is disabled, bail
    if (!caching_)
    {
        if (&ec != &throws)
            ec = make_success_code();
        return false;
    }

    // first look up the requested item in the cache
    gva_cache_key k(id);
    mutex_type::scoped_lock lock(gva_cache_mtx_);
    gva_cache_key idbase;
    gva_cache_type::entry_type e;

    // Check if the entry is currently in the cache
    if (gva_cache_.get_entry(k, idbase, e))
    {
        const boost::uint64_t id_msb
            = naming::strip_credit_from_gid(id.get_msb());

        if (HPX_UNLIKELY(id_msb != idbase.get_gid().get_msb()))
        {
            HPX_THROWS_IF(ec, internal_server_error
              , "addressing_service::resolve_cached"
              , "bad entry in cache, MSBs of GID base and GID do not match");
            return false;
        }

        gva const& g = e.get();

        addr.locality_ = g.endpoint;
        addr.type_ = g.type;
        addr.address_ = g.lva(id, idbase.get_gid());

        if (&ec != &throws)
            ec = make_success_code();

        LAS_(debug) <<
            ( boost::format(
                "cache hit for address %1%, lva %2% (base %3%, lva %4%)")
            % id
            % reinterpret_cast<void*>(addr.address_)
            % idbase.get_gid()
            % reinterpret_cast<void*>(g.lva()));

        return true;
    }

    if (&ec != &throws)
        ec = make_success_code();

    LAS_(debug) << (boost::format("cache miss for address %1%") % id);

    return false;
} // }}}

boost::uint64_t addressing_service::incref(
    naming::gid_type const& id
  , boost::uint64_t credits
  , error_code& ec
    )
{ // {{{ incref implementation
    try {
        request req(primary_ns_increment, id, credits);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return 0;

        return rep.get_count();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(), "addressing_service::incref",
                e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return 0;
    }
} // }}}

boost::uint64_t addressing_service::decref(
    naming::gid_type const& id
  , components::component_type& t
  , boost::uint64_t credits
  , error_code& ec
    )
{ // {{{ decref implementation
    try {
        request req(primary_ns_decrement, id, credits);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->primary_ns_server.service(req, ec);
        else
            rep = hosted->primary_ns_.service(req, ec);

        if (ec || (success != rep.get_status()))
            return 0;

        if (0 == rep.get_count())
        {
            t = (components::component_type) rep.get_component_type();

            if (HPX_UNLIKELY(components::component_invalid != t))
            {
                HPX_THROWS_IF(ec, bad_component_type
                  , "addressing_service::decref"
                  , boost::str(boost::format(
                    "received invalid component type when decrementing last "
                    "GID to 0, gid(%1%)")
                    % id));
                return 0;
            }
        }

        return rep.get_count();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error(), "addressing_service::decref",
                e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::register_name(
    std::string const& name
  , naming::gid_type const& id
  , error_code& ec
    )
{ // {{{
    try {
        request req(symbol_ns_bind, name, id);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->symbol_ns_server.service(req, ec);
        else
            rep = hosted->symbol_ns_.service(req, ec);

        return !ec && (success == rep.get_status());
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::register_name"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::unregister_name(
    std::string const& name
  , naming::gid_type& id
  , error_code& ec
    )
{ // {{{
    try {
        request req(symbol_ns_unbind, name);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->symbol_ns_server.service(req, ec);
        else
            rep = hosted->symbol_ns_.service(req, ec);

        if (!ec && (success == rep.get_status()))
        {
            id = rep.get_gid();
            return true;
        }

        return false;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::unregister_name"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

bool addressing_service::resolve_name(
    std::string const& name
  , naming::gid_type& id
  , error_code& ec
    )
{ // {{{
    try {
        request req(symbol_ns_resolve, name);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->symbol_ns_server.service(req, ec);
        else
            rep = hosted->symbol_ns_.service(req, ec);

        if (!ec && (success == rep.get_status()))
        {
            id = rep.get_gid();
            return true;
        }

        else
            return false;
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::resolve_name"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

/// Invoke the supplied hpx::function for every registered global name
bool addressing_service::iterateids(
    iterate_names_function_type const& f
  , error_code& ec
    )
{ // {{{
    try {
        request req(symbol_ns_iterate, f);
        response rep;

        if (is_bootstrap())
            rep = bootstrap->symbol_ns_server.service(req, ec);
        else
            rep = hosted->symbol_ns_.service(req, ec);

        return !ec && (success == rep.get_status());
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::iterateids"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }

        return false;
    }
} // }}}

void addressing_service::update_cache(
    naming::gid_type const& gid
  , gva const& g
  , error_code& ec
    )
{ // {{{
    if (!caching_)
    {
        HPX_THROWS_IF(ec, service_unavailable
          , "addressing_service::update_cache"
          , "AGAS caching is disabled");
        return;
    }

    try {
        mutex_type::scoped_lock lock(gva_cache_mtx_);

        gva_cache_key key(gid, g.count);
        gva_cache_.insert(key, g);

        if (&ec != &throws)
            ec = make_success_code();
    }
    catch (hpx::exception const& e) {
        if (&ec == &throws) {
            HPX_RETHROW_EXCEPTION(e.get_error()
              , "addressing_service::update_cache"
              , e.what());
        }
        else {
            ec = e.get_error_code(hpx::rethrow);
        }
    }
} // }}}

///////////////////////////////////////////////////////////////////////////////
// Helper functions to access the current cache statistics
std::size_t addressing_service::get_cache_hits() const
{
    mutex_type::scoped_lock lock(gva_cache_mtx_);
    return gva_cache_.get_statistics().hits();
}

std::size_t addressing_service::get_cache_misses() const
{
    mutex_type::scoped_lock lock(gva_cache_mtx_);
    return gva_cache_.get_statistics().misses();
}

std::size_t addressing_service::get_cache_evictions() const
{
    mutex_type::scoped_lock lock(gva_cache_mtx_);
    return gva_cache_.get_statistics().evictions();
}

std::size_t addressing_service::get_cache_insertions() const
{
    mutex_type::scoped_lock lock(gva_cache_mtx_);
    return gva_cache_.get_statistics().insertions();
}

/// Install performance counters exposing properties from the local cache.
void addressing_service::install_counters()
{ // {{{
    // install
    performance_counters::raw_counter_type_data const counter_types[] =
    {
        { "/agas/cache/hits", performance_counters::counter_raw,
          "returns the number of cache hits while accessing the AGAS cache",
          HPX_PERFORMANCE_COUNTER_V1 },
        { "/agas/cache/misses", performance_counters::counter_raw,
          "returns the number of cache misses while accessing the AGAS cache",
          HPX_PERFORMANCE_COUNTER_V1 },
        { "/agas/cache/evictions", performance_counters::counter_raw,
          "returns the number of cache evictions from the AGAS cache",
          HPX_PERFORMANCE_COUNTER_V1 },
        { "/agas/cache/insertions", performance_counters::counter_raw,
          "returns the number of cache insertions into the AGAS cache",
          HPX_PERFORMANCE_COUNTER_V1 }
    };
    performance_counters::install_counter_types(
        counter_types, sizeof(counter_types)/sizeof(counter_types[0]));

    boost::uint32_t const prefix = applier::get_applier().get_prefix_id();
    boost::format cache_statistics("/agas(locality#%d/total)/cache/%s");

    performance_counters::raw_counter_data const counters[] =
    {
        { boost::str(cache_statistics % prefix % "hits"),
          boost::bind(&addressing_service::get_cache_hits, this) },
        { boost::str(cache_statistics % prefix % "misses"),
          boost::bind(&addressing_service::get_cache_misses, this) },
        { boost::str(cache_statistics % prefix % "evictions"),
          boost::bind(&addressing_service::get_cache_evictions, this) },
        { boost::str(cache_statistics % prefix % "insertions"),
          boost::bind(&addressing_service::get_cache_insertions, this) }
    };

    performance_counters::install_counters(
        counters, sizeof(counters)/sizeof(counters[0]));
} // }}}

}}


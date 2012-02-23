////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/version.hpp>
#include <hpx/hpx.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/lcos/barrier.hpp>
#include <hpx/lcos/future_wait.hpp>
#include <hpx/runtime/agas/interface.hpp>

namespace hpx
{

///////////////////////////////////////////////////////////////////////////////
// Create a new barrier and register its gid with the given symbolic name.
inline lcos::barrier
create_barrier(naming::resolver_client& agas_client,
    std::size_t num_localities, char const* symname)
{
    lcos::barrier b;
    b.create_one(agas_client.local_locality(), num_localities);

    using naming::strip_credit_from_cgid;

    agas::register_name(symname, strip_credit_from_cgid(b.get_gid().get_gid()));
    return b;
}

///////////////////////////////////////////////////////////////////////////////
// Find a registered barrier object from its symbolic name.
inline lcos::barrier
find_barrier(char const* symname)
{
    naming::id_type barrier_id;
    for (std::size_t i = 0; i < HPX_MAX_NETWORK_RETRIES; ++i)
    {
        if (agas::resolve_name(symname, barrier_id))
            break;

        boost::this_thread::sleep(boost::get_system_time() +
            boost::posix_time::milliseconds(HPX_NETWORK_RETRIES_SLEEP));
    }
    if (HPX_UNLIKELY(!barrier_id))
    {
        HPX_THROW_EXCEPTION(network_error, "pre_main::find_barrier",
            std::string("couldn't find stage boot barrier ") + symname);
    }
    return lcos::barrier(barrier_id);
}

///////////////////////////////////////////////////////////////////////////////
// Symbolic names of global boot barrier objects
const char* second_barrier = "/barrier(agas#0)/second_stage";
const char* third_barrier = "/barrier(agas#0)/third_stage";

///////////////////////////////////////////////////////////////////////////////
// Install performance counter startup functions for core subsystems.
void register_counter_types()
{
     naming::get_agas_client().register_counter_types();
     LBT_(info) << "(3rd stage) pre_main: registered AGAS client-side "
                   "performance counter types";

     get_runtime().register_counter_types();
     LBT_(info) << "(3rd stage) pre_main: registered runtime performance "
                   "counter types";

     threads::get_thread_manager().register_counter_types();
     LBT_(info) << "(3rd stage) pre_main: registered thread-manager performance "
                   "counter types";

     applier::get_applier().get_parcel_handler().register_counter_types();
     LBT_(info) << "(3rd stage) pre_main: registered parcelset performance "
                   "counter types";

     util::detail::register_counter_types();
     LBT_(info) << "(3rd stage) pre_main: registered full_empty_entry "
                   "performance counter types";
}

///////////////////////////////////////////////////////////////////////////////
void garbage_collect_non_blocking()
{
    agas::garbage_collect_non_blocking();
}

void garbage_collect()
{
    agas::garbage_collect();
}

///////////////////////////////////////////////////////////////////////////////
// Implements second and third stage bootstrapping.
bool pre_main(runtime_mode mode)
{
    naming::resolver_client& agas_client = naming::get_agas_client();
    util::runtime_configuration const& cfg = get_runtime().get_config();

    bool exit_requested = false;
    if (runtime_mode_connect == mode)
    {
        LBT_(info) << "(2nd stage) pre_main: locality is in connect mode, "
                      "skipping 2nd and 3rd stage startup synchronization";

        std::size_t const pool_size = cfg.get_agas_promise_pool_size();

        // Unblock the AGAS router by adding the initial pool size to the
        // promise pool semaphores.
        agas_client.hosted->promise_pool_semaphore_.signal(pool_size);
        LBT_(info) << "(2nd stage) pre_main: addressing services enabled";

        // Load components, so that we can use the barrier LCO.
        exit_requested = !components::stubs::runtime_support::load_components(find_here());
        LBT_(info) << "(2nd stage) pre_main: loaded components"
            << (exit_requested ? ", application exit has been requested" : "");

        register_counter_types();

        components::stubs::runtime_support::call_startup_functions(find_here());
        LBT_(info) << "(3rd stage) pre_main: ran startup functions";
    }

    else
    {
        // {{{ unblock addressing_service
        if (!agas_client.is_bootstrap())
        {
            std::size_t const pool_size = cfg.get_agas_promise_pool_size();

            // Unblock the local addressing_service by adding the initial pool
            // size to the promise pool semaphores. This ensures that no AGAS
            // requests are sent after first-stage AGAS bootstrap and before
            // second-stage bootstrap.
            agas_client.hosted->promise_pool_semaphore_.signal(pool_size);

            LBT_(info) << "(2nd stage) pre_main: addressing services enabled";
        }
        // }}}

        // Load components, so that we can use the barrier LCO.
        exit_requested = !components::stubs::runtime_support::load_components(find_here());
        LBT_(info) << "(2nd stage) pre_main: loaded components"
            << (exit_requested ? ", application exit has been requested" : "");

        lcos::barrier second_stage, third_stage;

        // {{{ Second and third stage barrier creation.
        if (agas_client.is_bootstrap())
        {
            naming::gid_type console_;

            if (HPX_UNLIKELY(!agas_client.get_console_locality(console_)))
            {
                HPX_THROW_EXCEPTION(network_error
                    , "pre_main"
                    , "no console locality registered");
            }

            std::size_t const num_localities = cfg.get_num_localities();
            second_stage = create_barrier(agas_client, num_localities, second_barrier);
            third_stage = create_barrier(agas_client, num_localities, third_barrier);

            LBT_(info) << "(2nd stage) pre_main: created 2nd and 3rd stage boot barriers";
        }

        else // Hosted.
        {
            // Initialize the barrier clients (find them in AGAS)
            second_stage = find_barrier(second_barrier);
            third_stage = find_barrier(third_barrier);

            LBT_(info) << "(2nd stage) pre_main: found 2nd and 3rd stage boot barriers";
        }
        // }}}

        // Second stage bootstrap synchronizes component loading across all
        // localities, ensuring that the component namespace tables are fully
        // populated before user code is executed.
        second_stage.wait();
        LBT_(info) << "(2nd stage) pre_main: passed 2nd stage boot barrier";

        register_counter_types();

        components::stubs::runtime_support::call_startup_functions(find_here());
        LBT_(info) << "(3rd stage) pre_main: ran startup functions";

        // Third stage bootstrap synchronizes startup functions across all
        // localities. This is done after component loading to guarantee that
        // all user code, including startup functions, are only run after the
        // component tables are populated.
        third_stage.wait();
        LBT_(info) << "(3rd stage) pre_main: passed 3rd stage boot barrier";
    }

    // Enable logging. Even if we terminate at this point we will see all
    // pending log messages so far.
    components::activate_logging();
    LBT_(info) << "(3rd stage) pre_main: activated logging";

    // Register pre-shutdown and shutdown functions to flush pending
    // reference counting operations.
    register_pre_shutdown_function(&garbage_collect_non_blocking);
    register_shutdown_function(&garbage_collect);

    // Any error in post-command line handling or any explicit --exit command
    // line option will cause the application to terminate at this point.
    if (exit_requested)
    {
        // If load_components returns false, shutdown the system. This
        // essentially only happens if the command line contained --exit.
        components::stubs::runtime_support::shutdown_all(
            naming::get_id_from_locality_id(HPX_AGAS_BOOTSTRAP_PREFIX), -1.0);
        return false;
    }

    return true;
}

}


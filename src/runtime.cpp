//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>

#include <iostream>
#include <vector>

#include <boost/config.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <hpx/exception.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/util/stringstream.hpp>
#include <hpx/runtime/components/console_error_sink.hpp>
#include <hpx/runtime/components/server/console_error_sink.hpp>
#include <hpx/runtime/components/runtime_support.hpp>
#include <hpx/runtime/parcelset/policies/global_parcelhandler_queue.hpp>
#include <hpx/include/performance_counters.hpp>

#if HPX_AGAS_VERSION > 0x10
    #include <hpx/runtime/agas/router/big_boot_barrier.hpp>
#endif
 
///////////////////////////////////////////////////////////////////////////////
// Make sure the system gets properly shut down while handling Ctrl-C and other
// system signals
#if defined(BOOST_WINDOWS)

namespace hpx
{
    void handle_termination(char const* reason)
    {
        std::cerr << "Received " << (reason ? reason : "unknown signal")
#if HPX_STACKTRACES != 0
                  << ", " << hpx::detail::backtrace() 
#else
                  << "."
#endif
                  << std::endl;
        std::abort();
    }

    HPX_EXPORT BOOL WINAPI termination_handler(DWORD ctrl_type)
    {
        switch (ctrl_type) {
        case CTRL_C_EVENT:
            handle_termination("Ctrl-C");
            return TRUE;

        case CTRL_BREAK_EVENT:
            handle_termination("Ctrl-Break");
            return TRUE;

        case CTRL_CLOSE_EVENT:
            handle_termination("Ctrl-Close");
            return TRUE;

        case CTRL_LOGOFF_EVENT:
            handle_termination("Logoff");
            return TRUE;

        case CTRL_SHUTDOWN_EVENT:
            handle_termination("Shutdown");
            return TRUE;

        default:
            break;
        }
        return FALSE;
    }
}

#else

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#if HPX_STACKTRACES != 0
    #include <boost/backtrace.hpp>
#endif

namespace hpx 
{
    HPX_EXPORT void termination_handler(int signum)
    {
        char* c = strsignal(signum); 
        std::cerr << "Received " << (c ? c : "unknown signal")
#if HPX_STACKTRACES != 0
                  << ", " << hpx::detail::backtrace() 
#else
                  << "."
#endif
                  << std::endl;
        std::abort();
    }
}

#endif

///////////////////////////////////////////////////////////////////////////////
namespace hpx 
{
    ///////////////////////////////////////////////////////////////////////////
    namespace strings
    {
        char const* const runtime_mode_names[] = 
        {
            "invalid",    // -1
            "console",    // 0
            "worker",     // 1
            "connect",    // 2
            "default",    // 3
        };
    }

    char const* get_runtime_mode_name(runtime_mode state)
    {
        if (state < runtime_mode_invalid || state > runtime_mode_last)
            return "invalid (value out of bounds)";
        return strings::runtime_mode_names[state+1];
    }

    ///////////////////////////////////////////////////////////////////////////
    boost::atomic<int> runtime::instance_number_counter_(-1);

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::runtime_impl(
            std::string const& address, boost::uint16_t port,
            std::string const& agas_address, boost::uint16_t agas_port, 
            runtime_mode locality_mode, init_scheduler_type const& init,
            std::string const& hpx_ini_file,
            std::vector<std::string> const& cmdline_ini_defs) 
      : runtime(agas_client_, hpx_ini_file, cmdline_ini_defs),
        mode_(locality_mode), result_(0), 
#if HPX_AGAS_VERSION <= 0x10
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "agas_client_pool"), 
#else
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "io_pool"), 
#endif
        parcel_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "parcel_pool"), 
        timer_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "timer_pool"),
        parcel_port_(parcel_pool_, naming::locality(address, port)),
#if HPX_AGAS_VERSION <= 0x10
        agas_client_(io_pool_, naming::locality(agas_address, agas_port),
                     ini_, mode_ == runtime_mode_console),
#else
        agas_client_(parcel_port_, ini_, mode_),
#endif
        parcel_handler_(agas_client_, parcel_port_, &thread_manager_
                       , new parcelset::policies::global_parcelhandler_queue),
#if HPX_AGAS_VERSION <= 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        scheduler_(init),
        notifier_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()),
            boost::bind(&runtime_impl::report_error, This(), _1, _2)),
        thread_manager_(timer_pool_, scheduler_, notifier_),
#if HPX_AGAS_VERSION > 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        applier_(parcel_handler_, thread_manager_, 
            boost::uint64_t(&runtime_support_), boost::uint64_t(&memory_)),
        action_manager_(applier_),
        runtime_support_(ini_, parcel_handler_.get_prefix(), agas_client_, applier_)
    {
        components::server::get_error_dispatcher().register_error_sink(
            &runtime_impl::default_errorsink, default_error_sink_);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::runtime_impl(
            naming::locality address, naming::locality agas_address, 
            runtime_mode locality_mode, init_scheduler_type const& init,
            std::string const& hpx_ini_file,
            std::vector<std::string> const& cmdline_ini_defs) 
      : runtime(agas_client_, hpx_ini_file, cmdline_ini_defs),
        mode_(locality_mode), result_(0), 
#if HPX_AGAS_VERSION <= 0x10
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "agas_client_pool"), 
#else
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "io_pool"), 
#endif
        parcel_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "parcel_pool"), 
        timer_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "timer_pool"),
        parcel_port_(parcel_pool_, address),
#if HPX_AGAS_VERSION <= 0x10
        agas_client_(io_pool_, agas_address, ini_, mode_ == runtime_mode_console),
#else
        agas_client_(parcel_port_, ini_, mode_),
#endif
        parcel_handler_(agas_client_, parcel_port_, &thread_manager_
                       , new parcelset::policies::global_parcelhandler_queue),
#if HPX_AGAS_VERSION <= 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        scheduler_(init),
        notifier_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()),
            boost::bind(&runtime_impl::report_error, This(), _1, _2)),
        thread_manager_(timer_pool_, scheduler_, notifier_),
#if HPX_AGAS_VERSION > 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        applier_(parcel_handler_, thread_manager_, 
            boost::uint64_t(&runtime_support_), boost::uint64_t(&memory_)),
        action_manager_(applier_),
        runtime_support_(ini_, parcel_handler_.get_prefix(), agas_client_, applier_)
    {
        components::server::get_error_dispatcher().register_error_sink(
            &runtime_impl::default_errorsink, default_error_sink_);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::runtime_impl(
            naming::locality address, runtime_mode locality_mode, 
            init_scheduler_type const& init,
            std::string const& hpx_ini_file,
            std::vector<std::string> const& cmdline_ini_defs) 
      : runtime(agas_client_, hpx_ini_file, cmdline_ini_defs),
        mode_(locality_mode), result_(0), 
#if HPX_AGAS_VERSION <= 0x10
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "agas_client_pool"), 
#else
        io_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "io_pool"), 
#endif
        parcel_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "parcel_pool"), 
        timer_pool_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()), "timer_pool"),
        parcel_port_(parcel_pool_, address),
#if HPX_AGAS_VERSION <= 0x10
        agas_client_(io_pool_, ini_, mode_ == runtime_mode_console),
#else
        agas_client_(parcel_port_, ini_, mode_),
#endif
        parcel_handler_(agas_client_, parcel_port_, &thread_manager_
                       , new parcelset::policies::global_parcelhandler_queue),
#if HPX_AGAS_VERSION <= 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        scheduler_(init),
        notifier_(boost::bind(&runtime_impl::init_tss, This()),
            boost::bind(&runtime_impl::deinit_tss, This()),
            boost::bind(&runtime_impl::report_error, This(), _1, _2)),
        thread_manager_(timer_pool_, scheduler_, notifier_),
#if HPX_AGAS_VERSION > 0x10
        init_logging_(ini_, mode_ == runtime_mode_console, agas_client_),
#endif
        applier_(parcel_handler_, thread_manager_, 
            boost::uint64_t(&runtime_support_), boost::uint64_t(&memory_)),
        action_manager_(applier_),
        runtime_support_(ini_, parcel_handler_.get_prefix(), agas_client_, applier_)
    {
        components::server::get_error_dispatcher().register_error_sink(
            &runtime_impl::default_errorsink, default_error_sink_);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::~runtime_impl()
    {
        LRT_(debug) << "~runtime_impl(entering)";

        // stop all services
        parcel_port_.stop();      // stops parcel_pool_ as well
        thread_manager_.stop();   // stops timer_pool_ as well
#if HPX_AGAS_VERSION <= 0x10
        io_pool_.stop();
#else
        io_pool_.stop();
#endif
        // unload libraries
        //runtime_support_.tidy();

        LRT_(debug) << "~runtime_impl(finished)";
    }

    ///////////////////////////////////////////////////////////////////////////
#if defined(_WIN64) && defined(_DEBUG) && !defined(BOOST_COROUTINE_USE_FIBERS)
#include <io.h>
#endif

    ///////////////////////////////////////////////////////////////////////////
#if HPX_AGAS_VERSION <= 0x10
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    threads::thread_state 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::run_helper(
        boost::function<runtime::hpx_main_function_type> func, int& result)
    {
        // if we're not the console, we'll pull the console configuration 
        // information and merge it with ours
//         if (mode_ == worker) {
//             error_code ec;
//             naming::id_type console_prefix;
//             if (agas_client_.get_console_prefix(console_prefix, ec))
//             {
//                 util::section ini;
//                 components::stubs::runtime_support::get_config(console_prefix, ini);
//                 ini_.add_section("application", ini);
//             }
//         }

        // now, execute the user supplied thread function
        if (!func.empty()) 
            result = func();
        return threads::thread_state(threads::terminated);
    }
#else
    void pre_main(hpx::runtime_mode);

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    threads::thread_state 
    runtime_impl<SchedulingPolicy, NotificationPolicy>::run_helper(
        boost::function<runtime::hpx_main_function_type> func, int& result)
    {
        // run global pre_main functionality
        hpx::pre_main(mode_);

        // now, execute the user supplied thread function
        if (!func.empty()) 
            result = func();

        return threads::thread_state(threads::terminated);
    }
#endif

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    int runtime_impl<SchedulingPolicy, NotificationPolicy>::start(
        boost::function<hpx_main_function_type> func, 
        std::size_t num_threads, std::size_t num_localities, bool blocking)
    {
#if defined(_WIN64) && defined(_DEBUG) && !defined(BOOST_COROUTINE_USE_FIBERS)
        // needs to be called to avoid problems at system startup
        // see: http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100319
        _isatty(0);
#endif
        // {{{ early startup code
#if HPX_AGAS_VERSION <= 0x10
        // init TSS for the main thread, this enables logging, time logging, etc.
        init_tss();
#else
        // in AGAS v2, the runtime pointer (accessible through get_runtime
        // and get_runtime_ptr) is already initialized at this point.
        applier_.init_tss();
#endif

        LRT_(info) << "cmd_line: " << get_config().get_cmd_line(); 

        LRT_(info) << "runtime_impl: beginning startup sequence";

        LRT_(info) << "runtime_impl: starting services";
        // start services (service threads)
        runtime_support_.run();
        LRT_(info) << "runtime_impl: started runtime_support component";

        // AGAS v2 starts the parcel port itself
#if HPX_AGAS_VERSION <= 0x10
        parcel_port_.run(false);            // starts parcel_pool_ as well
        LRT_(info) << "runtime_impl: started parcelport";
#endif

#if HPX_AGAS_VERSION > 0x10
        io_pool_.run(false); // start io pool
#endif

        thread_manager_.run(num_threads);   // start the thread manager, timer_pool_ as well
        LRT_(info) << "runtime_impl: started threadmanager";
        // }}}

        // AGAS v2 handles this in the client
#if HPX_AGAS_VERSION <= 0x10
        // {{{ exiting bootstrap mode 
        LRT_(info) << "runtime_impl: registering runtime_support and memory components";
        // register the runtime_support and memory instances with the AGAS 
        agas_client_.bind(applier_.get_runtime_support_raw_gid(), 
            naming::address(parcel_port_.here(), 
                components::get_component_type<components::server::runtime_support>(), 
                &runtime_support_));

        agas_client_.bind(applier_.get_memory_raw_gid(), 
            naming::address(parcel_port_.here(), 
                components::get_component_type<components::server::memory>(), 
                &memory_));
#endif
        // }}}

        // {{{ late startup - distributed
        // if there are more than one localities involved, wait for all
        // to get registered
#if HPX_AGAS_VERSION <= 0x10
        if (num_localities > 1) {
            bool foundall = false;
            for (int i = 0; i < HPX_MAX_NETWORK_RETRIES; ++i) {
                std::vector<naming::gid_type> prefixes;
                error_code ec;
                // NOTE: in AGAS v2, AGAS enforces a distributed, global barrier
                // before we get here, so this should always succeed 
                if (agas_client_.get_prefixes(prefixes, ec) &&
                    num_localities == prefixes.size()) 
                {
                    foundall = true;
                    break;
                }

                boost::this_thread::sleep(boost::get_system_time() + 
                    boost::posix_time::milliseconds(HPX_NETWORK_RETRIES_SLEEP));
            } 
            if (!foundall) {
                HPX_THROW_EXCEPTION(startup_timed_out, "runtime::run", 
                    "timed out while waiting for other localities");
            }
        }
#else
        // invoke the AGAS v2 notifications, waking up the other localities
        agas::get_big_boot_barrier().trigger();  
#endif
        // }}}

        // {{{ launch main 
        // register the given main function with the thread manager
        threads::thread_init_data data(
            boost::bind(&runtime_impl::run_helper, this, func, 
                boost::ref(result_)), 
            "run_helper");
        thread_manager_.register_thread(data);
        this->runtime::start();

        LRT_(info) << "runtime_impl: started using "  << num_threads << " OS threads";
        // }}}

        // block if required
        if (blocking) 
            return wait();     // wait for the shutdown_action to be executed

        return 0;   // return zero as we don't know the outcome of hpx_main yet
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    int runtime_impl<SchedulingPolicy, NotificationPolicy>::start(
        std::size_t num_threads, std::size_t num_localities, bool blocking)
    {
        boost::function<hpx_main_function_type> empty_main;
        return start(empty_main, num_threads, num_localities, blocking);
    }

    ///////////////////////////////////////////////////////////////////////////
    static void wait_helper(components::server::runtime_support& rts,
        boost::mutex& mtx, boost::condition& cond, bool& running)
    {
        // signal successful initialization
        {
            boost::mutex::scoped_lock lk(mtx);
            running = true;
            cond.notify_all();
        }

        // wait for termination
        rts.wait();
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    int runtime_impl<SchedulingPolicy, NotificationPolicy>::wait()
    {
        LRT_(info) << "runtime_impl: about to enter wait state";

        // start the wait_helper in a separate thread
        boost::mutex mtx;
        boost::condition cond;
        bool running = false;
        boost::thread t (boost::bind(
                    &wait_helper, boost::ref(runtime_support_), 
                    boost::ref(mtx), boost::ref(cond), boost::ref(running)
                )
            );

        // wait for the thread to run
        {
            boost::mutex::scoped_lock lk(mtx);
            if (!running)
                cond.wait(lk);
        }

        // block main thread
        t.join();

        LRT_(info) << "runtime_impl: exiting wait state";
        return result_;
    }

    ///////////////////////////////////////////////////////////////////////////
    // First half of termination process: stop thread manager,
    // schedule a task managed by timer_pool to initiate second part
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::stop(bool blocking)
    {
        LRT_(warning) << "runtime_impl: about to stop services";

        // execute all on_exit functions whenever the first thread calls this
        this->runtime::stop();

        // stop runtime_impl services (threads)
        thread_manager_.stop(false);    // just initiate shutdown

        // schedule task in timer_pool to execute stopped() below
        // this is necessary as this function (stop()) might have been called
        // from a PX thread, so it would deadlock by waiting for the thread 
        // manager
        boost::mutex mtx;
        boost::condition cond;
        boost::mutex::scoped_lock l(mtx);

#if HPX_AGAS_VERSION <= 0x10
        parcel_port_.get_io_service_pool().get_io_service().post
#else
        boost::thread t
#endif
            (boost::bind(&runtime_impl::stopped, this, blocking, 
                boost::ref(cond), boost::ref(mtx)));
        cond.wait(l);

#if HPX_AGAS_VERSION > 0x10
        t.join();
#endif

//        // stop the rest of the system
//        parcel_port_.stop(blocking);        // stops parcel_pool_ as well

        deinit_tss();
    }

    // Second step in termination: shut down all services.
    // This gets executed as a task in the timer_pool io_service and not as 
    // a PX thread!
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::stopped(
        bool blocking, boost::condition& cond, boost::mutex& mtx)
    {
        // wait for thread manager to exit
        runtime_support_.stopped();         // re-activate shutdown PX-thread 
        thread_manager_.stop(blocking);     // wait for thread manager

        // unregister the runtime_support and memory instances from the AGAS 
        // ignore errors, as AGAS might be down already
#if HPX_AGAS_VERSION <= 0x10
        error_code ec;
        agas_client_.unbind(applier_.get_runtime_support_raw_gid(), ec);
        agas_client_.unbind(applier_.get_memory_raw_gid(), ec);
#endif

        // this disables all logging from the main thread
        deinit_tss();

        LRT_(info) << "runtime_impl: stopped all services";

        boost::mutex::scoped_lock l(mtx);
        cond.notify_all();                  // we're done now
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::report_error(
        std::size_t num_thread, boost::exception_ptr const& e)
    {
        // The console error sink is only applied at the console, so default
        // error sink never gets called on the locality, meaning that the user
        // never sees errors that kill the system before the error parcel gets
        // sent out. So, before we try to send the error parcel (which might
        // cause a double fault), print local diagnostics.
        components::server::console_error_sink(e);

        // Report this error to the console.
        naming::gid_type console_prefix;
        if (agas_client_.get_console_prefix(console_prefix))
        {
            if (parcel_handler_.get_prefix() != console_prefix) {
                components::console_error_sink(
                    naming::id_type(console_prefix, naming::id_type::unmanaged), 
                    e);
            }
        }

        // Stop all services.
        //stop(false);
        components::server::runtime_support* p = 
            reinterpret_cast<components::server::runtime_support*>(
                  get_runtime_support_lva());

        p->terminate_all();     // this does not return
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::report_error(
        boost::exception_ptr const& e)
    {
        std::size_t num_thread = hpx::threads::threadmanager_base::get_thread_num();
        return report_error(num_thread, e); 
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    int runtime_impl<SchedulingPolicy, NotificationPolicy>::run(
        boost::function<hpx_main_function_type> func,
        std::size_t num_threads, std::size_t num_localities)
    {
        // start the main thread function
        start(func, num_threads, num_localities);

        // now wait for everything to finish
        int result = wait();
        stop();

        parcel_port_.stop();      // stops parcelport for sure
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    int runtime_impl<SchedulingPolicy, NotificationPolicy>::run(
        std::size_t num_threads, std::size_t num_localities)
    {
        // start the main thread function
        start(num_threads, num_localities);

        // now wait for everything to finish
        int result = wait();
        stop();

        parcel_port_.stop();      // stops parcelport for sure
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::default_errorsink(
        std::string const& msg)
    {
        std::cerr << msg << std::endl;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::init_tss()
    {
        // initialize our TSS
        this->runtime::init_tss();

        // initialize applier TSS
        applier_.init_tss();
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::deinit_tss()
    {
        // reset applier TSS
        applier_.deinit_tss();

        // reset our TSS
        this->runtime::deinit_tss();
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    naming::gid_type
    runtime_impl<SchedulingPolicy, NotificationPolicy>::get_next_id()
    {
        return id_pool.get_id(parcel_port_.here(), agas_client_);
    }

#if HPX_AGAS_VERSION > 0x10
    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::add_startup_function(
        boost::function<void()> const& f)
    {
        runtime_support_.add_startup_function(f);
    }

    template <typename SchedulingPolicy, typename NotificationPolicy> 
    void runtime_impl<SchedulingPolicy, NotificationPolicy>::add_shutdown_function(
        boost::function<void()> const& f)
    {
        runtime_support_.add_shutdown_function(f);
    }
#endif

    ///////////////////////////////////////////////////////////////////////////
    boost::thread_specific_ptr<runtime *> runtime::runtime_;

    void runtime::init_tss()
    {
        // initialize our TSS
        BOOST_ASSERT(NULL == runtime::runtime_.get());    // shouldn't be initialized yet
        runtime::runtime_.reset(new runtime* (this));
    }

    void runtime::deinit_tss()
    {
        // reset our TSS
        runtime::runtime_.reset();
    }

    /// \brief Install all performance counters related to this runtime 
    ///        instance
    void runtime::install_counters()
    {
        performance_counters::counter_type_data counter_types[] = 
        {
            { "/runtime/uptime", performance_counters::counter_elapsed_time }
        };
        performance_counters::install_counter_types(
            counter_types, sizeof(counter_types)/sizeof(counter_types[0]));

        boost::uint32_t const prefix = applier::get_applier().get_prefix_id();
        boost::format runtime_uptime("/runtime([locality#%d]/total)/uptime");
        performance_counters::counter_data counters[] = 
        {
            { boost::str(runtime_uptime % prefix) }
        };
        performance_counters::install_counters(
            counters, sizeof(counters)/sizeof(counters[0]));
    }

    ///////////////////////////////////////////////////////////////////////////
    runtime& get_runtime()
    {
        BOOST_ASSERT(NULL != runtime::runtime_.get());   // should have been initialized
        return **runtime::runtime_;
    }

    runtime* get_runtime_ptr()
    {
        runtime** rt = runtime::runtime_.get();
        return rt ? *rt : NULL;
    }

    naming::locality const& get_locality()
    { 
        return get_runtime().here(); 
    }

    void report_error(std::size_t num_thread, boost::exception_ptr const& e) 
    {
        hpx::applier::get_applier().get_thread_manager().report_error(num_thread, e);
    }

    void report_error(boost::exception_ptr const& e) 
    {
        std::size_t num_thread = hpx::threads::threadmanager_base::get_thread_num();
        hpx::applier::get_applier().get_thread_manager().report_error(num_thread, e);
    }

    bool register_on_exit(boost::function<void()> f)
    {
        runtime* rt = get_runtime_ptr();
        if (NULL == rt)
            return false;
        rt->on_exit(f);
        return true;
    }

    std::size_t get_runtime_instance_number()
    {
//         runtime* rt = get_runtime_ptr();
//         return (NULL == rt) ? 0 : rt->get_instance_number();
        return get_runtime().get_instance_number();
    }

    std::string get_config_entry(std::string const& key, std::string const& dflt)
    {
        return get_runtime().get_config().get_entry(key, dflt);
    }

    std::string get_config_entry(std::string const& key, std::size_t dflt)
    {
        return get_runtime().get_config().get_entry(key, dflt);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Helpers
    naming::id_type find_here()
    {
        return naming::id_type(hpx::applier::get_applier().get_prefix(), 
            naming::id_type::unmanaged);
    }

    std::vector<naming::id_type> 
    find_all_localities(components::component_type type)
    {
        std::vector<naming::id_type> prefixes;
        hpx::applier::get_applier().get_prefixes(prefixes, type);
        return prefixes;
    }

    std::vector<naming::id_type> find_all_localities()
    {
        std::vector<naming::id_type> prefixes;
        hpx::applier::get_applier().get_prefixes(prefixes);
        return prefixes;
    }

    ///////////////////////////////////////////////////////////////////////////
    naming::gid_type get_next_id()
    {
        return get_runtime().get_next_id();
    }

    std::size_t get_num_os_threads()
    {
        return get_runtime().get_config().get_num_os_threads();
    }

#if HPX_AGAS_VERSION > 0x10
    ///////////////////////////////////////////////////////////////////////////
    void register_startup_function(boost::function<void()> const& f)
    {
        get_runtime().add_startup_function(f);
    }

    void register_shutdown_function(boost::function<void()> const& f)
    {
        get_runtime().add_shutdown_function(f);
    }
#endif
}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace naming
{
    // shortcut for get_runtime().get_agas_client()
    resolver_client& get_agas_client()
    {
        return get_runtime().get_agas_client();
    }
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace threads
{
    // shortcut for get_applier().get_thread_manager()
    threadmanager_base& get_thread_manager()
    {
        return hpx::applier::get_applier().get_thread_manager();
    }
}}

///////////////////////////////////////////////////////////////////////////////
/// explicit template instantiation for the thread manager of our choice
template HPX_EXPORT class hpx::runtime_impl<
    hpx::threads::policies::global_queue_scheduler, 
    hpx::threads::policies::callback_notifier>;

template HPX_EXPORT class hpx::runtime_impl<
    hpx::threads::policies::local_queue_scheduler, 
    hpx::threads::policies::callback_notifier>;

template HPX_EXPORT class hpx::runtime_impl<
    hpx::threads::policies::local_priority_queue_scheduler, 
    hpx::threads::policies::callback_notifier>;

template HPX_EXPORT class hpx::runtime_impl<
    hpx::threads::policies::abp_queue_scheduler, 
    hpx::threads::policies::callback_notifier>;


//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2010-2011 Phillip LeBlanc, Dylan Stark
//  Copyright (c)      2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/config.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/util/asio_util.hpp>

#if HPX_AGAS_VERSION > 0x10
    #include <vector>
    #include <boost/assign/std/vector.hpp>
    #include <boost/foreach.hpp>
    #include <hpx/lcos/eager_future.hpp>
    #include <hpx/runtime/components/runtime_support.hpp>
    #include <hpx/runtime/actions/function.hpp>
    #include <hpx/runtime/actions/plain_action.hpp>
    #include <hpx/runtime/components/plain_component_factory.hpp>
    #include <hpx/runtime/applier/applier.hpp>
    #include <hpx/include/performance_counters.hpp>
#endif

#if !defined(BOOST_WINDOWS)
    #include <signal.h>
#endif

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

namespace hpx
{
    typedef int (*hpx_main_func)(boost::program_options::variables_map& vm);
}

#if HPX_AGAS_VERSION > 0x10
    namespace hpx
    {
        void print_counter(std::string const& name)
        {
            std::cout << "  " << name << std::endl;
        }
    }

    typedef hpx::actions::plain_action1<
        std::string const&,
        hpx::print_counter
    > print_counter_action;

    HPX_REGISTER_PLAIN_ACTION(print_counter_action);

    namespace hpx
    {
        void list_counter(std::string const& name, naming::gid_type const& gid)
        {
            typedef lcos::eager_future<print_counter_action> future_type;
 
            const naming::id_type console
                (naming::get_gid_from_prefix(1), naming::id_type::unmanaged);

            if ((4 <= name.size()) && (name.substr(0, 4) == "/pcs"))
                future_type(console, name).get();
        }
    }

    typedef hpx::actions::plain_action2<
        std::string const&,
        hpx::naming::gid_type const&,
        hpx::list_counter
    > list_counter_action;

    namespace hpx
    {
        int list_counters(boost::program_options::variables_map& vm, hpx_main_func f)
        {
            {
                std::cout << "registered performance counters" << std::endl; 
                actions::function<void(std::string const&, naming::gid_type const&)>
                    cb(new list_counter_action);
                applier::get_applier().get_agas_client().iterateids(cb);
            }

            if (0 != f)
                return boost::bind(f, vm)();

            else
            {
                finalize();

                return 0;
            }
        }

        inline int list_counters(boost::program_options::variables_map& vm)
        {
            return list_counters(vm, 0);
        }
    }

    HPX_REGISTER_PLAIN_ACTION(list_counter_action);
#endif

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    // Print stack trace and exit.
#if defined(BOOST_WINDOWS)
    BOOL termination_handler(DWORD ctrl_type);
#else
    void termination_handler(int signum);
#endif

    ///////////////////////////////////////////////////////////////////////////
    typedef boost::function<void()> startup_func;
    typedef boost::function<void()> shutdown_func;

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        enum command_line_result
        {
            help,       ///< command line handling printed help text
            success,    ///< sucess parsing command line
            error       ///< error handling command line
        }; 

        ///////////////////////////////////////////////////////////////////////
        command_line_result print_version()
        {
            boost::format hpx_version("%d.%d.%d%s");
            boost::format boost_version("%d.%d.%d");
            boost::format logo(
                "HPX - High Performance ParalleX\n"
                "\n"
                "An experimental runtime system for conventional machines implementing\n"
                "(parts of) the ParalleX execution model.\n" 
                "\n"
                "Copyright (C) 1998-2011 Hartmut Kaiser, Bryce Lelbach and others\n"
                "\n"
                "Distributed under the Boost Software License, Version 1.0. (See accompanying\n" 
                "file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)\n"
                "\n"
                "Versions:\n"
                "  HPX %s (AGAS %x), SVN %s\n"
                "  Boost %s\n"
                "\n"
                "Build:\n"
                "  Date: %s\n" 
                "  Platform: %s\n"
                "  Compiler: %s\n"
                "  Standard Library: %s\n");

            std::cout << (logo
                          % boost::str( hpx_version
                                      % HPX_VERSION_MAJOR
                                      % HPX_VERSION_MINOR
                                      % HPX_VERSION_SUBMINOR
                                      % HPX_VERSION_TAG)
                          % HPX_AGAS_VERSION 
                          % HPX_SVN_REVISION
                          % boost::str( boost_version
                                      % (BOOST_VERSION / 100000)
                                      % (BOOST_VERSION / 100 % 1000)
                                      % (BOOST_VERSION % 100))
                          % __DATE__
                          % BOOST_PLATFORM
                          % BOOST_COMPILER
                          % BOOST_STDLIB);
            return help;
        }

        ///////////////////////////////////////////////////////////////////////
        command_line_result print_help(
            boost::program_options::options_description const& app_options, 
            boost::program_options::options_description const& hpx_options)
        {
            boost::program_options::options_description visible;

            visible.add(app_options).add(hpx_options);
            std::cout << visible;
            return help;
        }

        ///////////////////////////////////////////////////////////////////////
        // parse the command line
        command_line_result parse_commandline(
            boost::program_options::options_description& app_options, 
            int argc, char *argv[], boost::program_options::variables_map& vm,
            hpx::runtime_mode mode)
        {
            using boost::program_options::options_description;
            using boost::program_options::value;
            using boost::program_options::store;
            using boost::program_options::command_line_parser;

            try {
                options_description hpx_options("HPX Options");
                options_description hidden_options("Hidden Options");

                hpx_options.add_options()
                    ("help,h", "print out program usage (this message)")
                    ("version,v", "print out HPX version and copyright information")
                    ("run-agas-server,r",
                     "run AGAS server as part of this runtime instance")
                    ("run-hpx-main",
                     "run the hpx_main function, regardless of locality mode")
                ;

                switch (mode) {
                case runtime_mode_default:
                    hpx_options.add_options()
                        ("worker,w", "run this instance in worker mode")
                        ("console,c", "run this instance in console mode")
                        ("connect", "run this instance in worker mode, but connecting late")
                    ;
                    break;

                case runtime_mode_worker:
                case runtime_mode_console:
                case runtime_mode_connect:
                    // If the runtime for this application is always run in
                    // worker mode, silently ignore the worker option for
                    // hpx_pbs compatibility.
                    hidden_options.add_options()
                        ("worker,w", "run this instance in worker mode")
                        ("console,c", "run this instance in console mode")
                        ("connect", "run this instance in worker mode, but connecting late")
                    ;
                    break;

                case runtime_mode_invalid:
                default:
                    throw std::logic_error("invalid runtime mode specified");
                }

                hpx_options.add_options()
#if HPX_AGAS_VERSION <= 0x10
                    ("run-agas-server-only", "run only the AGAS server")
#else
                    ("list-counters", "list registered performance counters")
#endif
                ;

                hpx_options.add_options()
                    ("app-config,p", value<std::string>(), 
                     "load the specified application configuration file")
                    ("hpx-config", value<std::string>()->default_value(""), 
                     "load the specified hpx configuration file")
                    ("agas,a", value<std::string>(), 
                     "the IP address the AGAS server is running on, "
                     "expected format: `address:port' (default: "
                     "taken from hpx.ini)")
                    ("hpx,x", value<std::string>(), 
                     "the IP address the HPX parcelport is listening on, "
                     "expected format: `address:port' (default: "
                     "127.0.0.1:7910)")
                    ("localities,l", value<std::size_t>(), 
                     "the number of localities to wait for at application "
                     "startup (default: 1)")
                    ("threads,t", value<std::size_t>(), 
                     "the number of operating system threads to spawn for this "
                     "HPX locality (default: 1)")
                    ("high-priority-threads", value<std::size_t>(), 
                     "the number of operating system threads maintaining a high "
                     "priority queue (default: number of OS threads), valid for "
                     "--queueing=priority_local only")
                    ("ini,I", value<std::vector<std::string> >()->composing(),
                     "add an ini definition to the default runtime "
                     "configuration")
                    ("print-counter,P", value<std::vector<std::string> >()->composing(),
                     "print the specified performance counter before shutting "
                     "down the system")
                    ("dump-config", "print the runtime configuration")
                    ("exit", "exit after configuring the runtime")
                    ("queueing,q", value<std::string>(),
                     "the queue scheduling policy to use, options are `global/g', "
                     "`local/l', `priority_local/p' and `abp/a' (default: priority_local/p)")
                ;

                options_description desc_cmdline;
                desc_cmdline.add(app_options).add(hpx_options).add(hidden_options);

                store(command_line_parser(argc, argv).
                    options(desc_cmdline).run(), vm);
                notify(vm);

                // print version/copyright information 
                if (vm.count("version")) 
                    return print_version();

                // print help screen
                if (vm.count("help")) 
                    return print_help(app_options, hpx_options);
            }
            catch (std::exception const& e) {
                std::cerr << "hpx::init: exception caught: "
                          << e.what() << std::endl;
                return error;
            }

            return success;
        }

        ///////////////////////////////////////////////////////////////////////
        // Addresses are supposed to have the format <hostname>[:port]
        inline void 
        split_ip_address(std::string const& v, std::string& addr, 
            boost::uint16_t& port)
        {
            std::string::size_type p = v.find_first_of(":");

            try {
                if (p != std::string::npos) {
                    addr = v.substr(0, p);
                    port = boost::lexical_cast<boost::uint16_t>(v.substr(p+1));
                }
                else {
                    addr = v;
                }

                // map localhost to loopback ip address (that's a quick hack 
                // which will be removed as soon as we figure out why name 
                // resolution does not handle this anymore)
                if (addr == "localhost") 
                    addr = "127.0.0.1";
            }
            catch (boost::bad_lexical_cast const& /*e*/) {
                std::cerr << "hpx::init: illegal port number given: "
                          << v.substr(p+1) 
                          << "           using default value instead: "
                          << port 
                          << std::endl;
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // helper class for AGAS server initialization
#if HPX_AGAS_VERSION <= 0x10
        class agas_server_helper
        {
        public:
            agas_server_helper(std::string host, boost::uint16_t port,
                    bool blocking = false)
              : agas_pool_(), agas_(agas_pool_, host, port)
            {
                agas_.run(blocking); 
            }

            ~agas_server_helper()
            {
                agas_.stop(); 
            }

        private:
            hpx::util::io_service_pool agas_pool_;
            hpx::naming::resolver_server agas_;
        };
#endif

#if HPX_AGAS_VERSION > 0x10
        void print_shutdown_counters(std::vector<std::string> const& names)
        {
            std::cout << "shutdown performance counter queries\n";

            BOOST_FOREACH(std::string const& name, names)
            {
                naming::gid_type gid;
                applier::get_applier().get_agas_client().queryid(name, gid);

                if (HPX_UNLIKELY(!gid))
                {
                    HPX_THROW_EXCEPTION(bad_parameter,
                        "print_shutdown_counters",
                        boost::str(boost::format(
                            "invalid performance counter '%s'")
                            % name))
                }

                using hpx::performance_counters::stubs::performance_counter;
                using hpx::performance_counters::status_valid_data;

                // Query the performance counter.
                performance_counters::counter_value value
                    = performance_counter::get_value(gid);

                if (HPX_LIKELY(status_valid_data == value.status_))
                    std::cout << "  " << name << "," << value.value_ << "\n"; 
                else
                    std::cout << "  " << name << ",invalid\n"; 
            }
        }
#endif

        ///////////////////////////////////////////////////////////////////////
        template <typename Runtime>
        int run(Runtime& rt, hpx_main_func f, 
            boost::program_options::variables_map& vm, runtime_mode mode, 
            startup_func const& startup_function, 
            shutdown_func const& shutdown_function, 
            std::size_t num_threads, std::size_t num_localities)
        {
            if (vm.count("app-config"))
            {
                std::string config(vm["app-config"].as<std::string>());
                rt.get_config().load_application_configuration(config.c_str());
            }

            // Dump the configuration.
            if (vm.count("dump-config"))
                rt.get_config().dump();

#if HPX_AGAS_VERSION > 0x10

            if (vm.count("print-counter"))
            {
                std::vector<std::string> counters
                    = vm["print-counter"].as<std::vector<std::string> >();
                rt.add_shutdown_function
                    (boost::bind(print_shutdown_counters, counters));
            }

            if (!startup_function.empty())
                rt.add_startup_function(startup_function);

            if (!shutdown_function.empty())
                rt.add_shutdown_function(shutdown_function);

            if (vm.count("exit"))
            { 
                if (vm.count("list-counters"))
                    // Call list_counters, which will print out all available
                    // performance counters and then return 0.
                    return rt.run(boost::bind(&list_counters, vm),
                        num_threads, num_localities);
                else
                    return 0;
            }

            else if (vm.count("list-counters"))
                // Call list_counters, which will print out all available
                // performance counters and then call f.
                return rt.run(boost::bind(&list_counters, vm, f),
                    num_threads, num_localities);

            else
            {
                if (vm.count("exit"))
                    return 0;
                else if (0 != f)
                    // Run this runtime instance using the given function f.
                    return rt.run(boost::bind(f, vm), num_threads, num_localities);
            }
#else
            if (vm.count("exit"))
                return 0;
            else if (0 != f)
                // Run this runtime instance using the given function f.
                return rt.run(boost::bind(f, vm), num_threads, num_localities);
#endif

            // Run this runtime instance without an hpx_main
            return rt.run(num_threads, num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // global scheduler (one queue for all OS threads)
        int run_global(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup_function, 
            shutdown_func const& shutdown_function, 
            std::size_t num_threads, std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("bad parameter --high-priority-threads, "
                    "valid for --queueing=priority_local only");
            }

            // scheduling policy
            typedef hpx::threads::policies::global_queue_scheduler
                global_queue_policy;

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<global_queue_policy> runtime_type;
            runtime_type rt(hpx_host, hpx_port, agas_host, agas_port, mode,
                global_queue_policy::init_parameter_type(), 
                vm["hpx-config"].as<std::string>(), ini_config);

            return run(rt, f, vm, mode, startup_function, 
                shutdown_function, num_threads, num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // local scheduler (one queue for each OS threads)
        int run_local(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup_function, 
            shutdown_func const& shutdown_function, 
            std::size_t num_threads, std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("bad parameter --high-priority-threads, "
                    "valid for --queueing=priority_local only");
            }

            // scheduling policy
            typedef hpx::threads::policies::local_queue_scheduler
                local_queue_policy;
            local_queue_policy::init_parameter_type init(num_threads, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<local_queue_policy> runtime_type;
            runtime_type rt(hpx_host, hpx_port, agas_host, agas_port, mode,
                init, vm["hpx-config"].as<std::string>(), ini_config);

            return run(rt, f, vm, mode, startup_function, 
                shutdown_function, num_threads, num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // local scheduler with priority queue (one queue for each OS threads
        // plus one separate queue for high priority PX-threads)
        int run_priority_local(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup_function, 
            shutdown_func const& shutdown_function, 
            std::size_t num_threads, std::size_t num_localities)
        {
            std::size_t num_high_priority_queues = num_threads;
            if (vm.count("high-priority-threads"))
                num_high_priority_queues
                    = vm["high-priority-threads"].as<std::size_t>();

            // scheduling policy
            typedef hpx::threads::policies::local_priority_queue_scheduler 
                local_queue_policy;
            local_queue_policy::init_parameter_type init(
                num_threads, num_high_priority_queues, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<local_queue_policy> runtime_type;
            runtime_type rt(hpx_host, hpx_port, agas_host, agas_port, mode,
                init, vm["hpx-config"].as<std::string>(), ini_config);

            return run(rt, f, vm, mode, startup_function, 
                shutdown_function, num_threads, num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // abp scheduler: local deques for each OS thread, with work
        // stealing from the "bottom" of each.
        int run_abp(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup_function, 
            shutdown_func const& shutdown_function, 
            std::size_t num_threads, std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("bad parameter --high-priority-threads, "
                    "valid for --queueing=priority_local only");
            }

            // scheduling policy
            typedef hpx::threads::policies::abp_queue_scheduler 
                abp_queue_policy;
            abp_queue_policy::init_parameter_type init(num_threads, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<abp_queue_policy> runtime_type;
            runtime_type rt(hpx_host, hpx_port, agas_host, agas_port, mode,
                init, vm["hpx-config"].as<std::string>(), ini_config);

            return run(rt, f, vm, mode, startup_function, 
                shutdown_function, num_threads, num_localities);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    int init(hpx_main_func f,
        boost::program_options::options_description& desc_cmdline, 
        int argc, char* argv[], startup_func startup_function, 
        shutdown_func shutdown_function, hpx::runtime_mode mode)
    {
        int result = 0;

#if defined(BOOST_WINDOWS)
        // Set console control handler to allow server to be stopped.
        SetConsoleCtrlHandler(hpx::termination_handler, TRUE);
#else
        struct sigaction new_action;
        new_action.sa_handler = hpx::termination_handler;
        sigemptyset(&new_action.sa_mask);
        new_action.sa_flags = 0;

        sigaction(SIGBUS, &new_action, NULL);  // Bus error
        sigaction(SIGFPE, &new_action, NULL);  // Floating point exception
        sigaction(SIGILL, &new_action, NULL);  // Illegal instruction 
        sigaction(SIGPIPE, &new_action, NULL); // Bad pipe 
        sigaction(SIGSEGV, &new_action, NULL); // Segmentation fault 
        sigaction(SIGSYS, &new_action, NULL);  // Bad syscall 
#endif

        try {
            using boost::program_options::variables_map; 

            // Analyze the command line.
            variables_map vm;
            detail::command_line_result r = 
                detail::parse_commandline(desc_cmdline, argc, argv, vm, mode);

            switch (r) {
            case detail::error:
                return 1;
            case detail::help:
                return 0;
            default:
                break;
            }

            // Check command line arguments.
            std::string hpx_host(HPX_INITIAL_IP_ADDRESS), agas_host;
            boost::uint16_t hpx_port = HPX_INITIAL_IP_PORT, agas_port = 0;
            std::size_t num_threads = 1;
            std::size_t num_localities = 1;
            std::string queueing = "priority_local";
            std::vector<std::string> ini_config;

            if (vm.count("ini"))
                ini_config = vm["ini"].as<std::vector<std::string> >();

            if (vm.count("agas")) {
                detail::split_ip_address(
                    vm["agas"].as<std::string>(), agas_host, agas_port);

#if HPX_AGAS_VERSION > 0x10
                // map this command line option to the proper ini-file entries
                using namespace boost::assign;
                ini_config += "hpx.agas.address=" + agas_host;
                ini_config += "hpx.agas.port=" + 
                    boost::lexical_cast<std::string>(agas_port);
#endif
            }

            if (vm.count("hpx")) {
                detail::split_ip_address(
                    vm["hpx"].as<std::string>(), hpx_host, hpx_port);
            }

            if (vm.count("localities"))
                num_localities = vm["localities"].as<std::size_t>();

            if (vm.count("threads"))
                num_threads = vm["threads"].as<std::size_t>();

            if (vm.count("queueing"))
                queueing = vm["queueing"].as<std::string>();

            // If the user has not specified an explicit runtime mode we 
            // retrieve it from the command line.
            if (hpx::runtime_mode_default == mode)
            {
                // The default mode is console, i.e. all workers need to be 
                // started with --worker/-w.
                mode = hpx::runtime_mode_console;
                if (vm.count("console") + vm.count("worker") + vm.count("connect") > 1) {
                    throw std::logic_error("Ambiguous command line options. "
                        "Do not specify more than one of --console/-c, "
                        "--worker/-w, or --connect\n");
                }

                // In these cases we default to executing with an empty 
                // hpx_main, except if specified otherwise.
                if (vm.count("worker")) {
                    mode = hpx::runtime_mode_worker;

                    // do not execute any explicit hpx_main except if asked 
                    // otherwise
                    if (!vm.count("run-hpx-main"))
                        f = 0;
                }
                else if (vm.count("connect")) {
                    mode = hpx::runtime_mode_connect;

                    // do not execute any explicit hpx_main except if asked 
                    // otherwise
                    if (!vm.count("run-hpx-main"))
                        f = 0;
                }
            }

#if HPX_AGAS_VERSION <= 0x10
            // Initialize and run the AGAS service, if appropriate.
            boost::shared_ptr<detail::agas_server_helper> agas_server;

            if (vm.count("run-agas-server") || (num_localities == 1 && !vm.count("agas"))) {
                agas_server.reset(
                    new detail::agas_server_helper(agas_host, agas_port));
            }
            else if (vm.count("run-agas-server-only")) {
                agas_server.reset(
                    new detail::agas_server_helper(agas_host, agas_port, true));
                return 0;
            }
#else
            if (vm.count("run-agas-server") || (num_localities == 1 && !vm.count("agas")))  
            {
                using namespace boost::assign;
                ini_config += "hpx.agas.router_mode=bootstrap"; 
            }
#endif

#if HPX_AGAS_VERSION > 0x10
            {
                using namespace boost::assign;
                ini_config += "hpx.num_localities=" + 
                    boost::lexical_cast<std::string>(num_localities);
            }

            // if we connect only temporarily disable loading/registering any 
            // components
            if (mode == hpx::runtime_mode_connect)
            {
                using namespace boost::assign;
                ini_config += "hpx.components.load_external=0";
            }

            // FIXME: AGAS V2: if a locality is supposed to run the AGAS 
            //        service only and requests to use 'priority_local' as the
            //        scheduler, switch to the 'local' scheduler instead.
#endif

            // Initialize and start the HPX runtime.
            int result = -1;
            if (0 == std::string("global").find(queueing)) {
                result = detail::run_global(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup_function, shutdown_function, num_threads, 
                    num_localities);
            }
            else if (0 == std::string("local").find(queueing)) {
                result = detail::run_local(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup_function, shutdown_function, num_threads, 
                    num_localities);
            }
            else if (0 == std::string("priority_local").find(queueing)) {
                // local scheduler with priority queue (one queue for each OS threads
                // plus one separate queue for high priority PX-threads)
                result = detail::run_priority_local(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup_function, shutdown_function, num_threads, 
                    num_localities);
            }
            else if (0 == std::string("abp").find(queueing)) {
                // abp scheduler: local deques for each OS thread, with work
                // stealing from the "bottom" of each.
                result = detail::run_abp(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup_function, shutdown_function, num_threads, 
                    num_localities);
            }
            else {
                throw std::logic_error("bad value for parameter --queueing/-q");
            }
        }
        catch (std::exception& e) {
            std::cerr << "hpx::init: std::exception caught: " << e.what()
                      << "\n";
            return -1;
        }
        catch (...) {
            std::cerr << "hpx::init: unexpected exception caught\n";
            return -1;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////
    void finalize(double shutdown_timeout, double localwait)
    {
        if (localwait == -1.0)
            get_option(localwait, "hpx.finalize_wait_time");

        if (localwait != -1.0) {
            hpx::util::high_resolution_timer t;
            double start_time = t.elapsed();
            double current = 0.0;
            do {
                current = t.elapsed();
            } while (current - start_time < localwait * 1e-6);
        }

        if (shutdown_timeout == -1.0)
            get_option(shutdown_timeout, "hpx.shutdown_timeout");

        components::server::runtime_support* p = 
            reinterpret_cast<components::server::runtime_support*>(
                  get_runtime().get_runtime_support_lva());

        p->shutdown_all(shutdown_timeout); 
    }

    ///////////////////////////////////////////////////////////////////////////
    void disconnect(double shutdown_timeout, double localwait)
    {
        if (localwait == -1.0)
            get_option(localwait, "hpx.finalize_wait_time");

        if (localwait != -1.0) {
            hpx::util::high_resolution_timer t;
            double start_time = t.elapsed();
            double current = 0.0;
            do {
                current = t.elapsed();
            } while (current - start_time < localwait * 1e-6);
        }

        if (shutdown_timeout == -1.0)
            get_option(shutdown_timeout, "hpx.shutdown_timeout");

        components::server::runtime_support* p = 
            reinterpret_cast<components::server::runtime_support*>(
                  get_runtime().get_runtime_support_lva());

#if HPX_AGAS_VERSION > 0x10
        p->call_shutdown_functions();
#endif

        p->shutdown(shutdown_timeout); 
    }
}

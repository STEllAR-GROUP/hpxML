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
#include <hpx/util/pbs_environment.hpp>
#include <hpx/util/map_hostnames.hpp>
#include <hpx/util/sed_transform.hpp>
#include <hpx/util/parse_command_line.hpp>

#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/components/runtime_support.hpp>
#include <hpx/runtime/actions/function.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/util/query_counters.hpp>
#include <hpx/util/stringstream.hpp>

#if !defined(BOOST_WINDOWS)
#  include <signal.h>
#endif

#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    typedef int (*hpx_main_func)(boost::program_options::variables_map& vm);
}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace detail
{
    // forward declarations only
    void console_print(std::string const& name);
    void list_counter(std::string const& name, naming::gid_type const& gid);
    void list_counter_info(std::string const& name, naming::gid_type const& gid);
    void list_symbolic_name(std::string const& name, naming::gid_type const& gid);
    void list_component_type(std::string const& name, components::component_type);
}}

typedef hpx::actions::plain_action1<
    std::string const&, hpx::detail::console_print
> console_print_action;
HPX_REGISTER_PLAIN_ACTION_EX2(console_print_action, console_print_action, true);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::naming::gid_type const&,
    hpx::detail::list_counter
> list_counter_action;
HPX_REGISTER_PLAIN_ACTION_EX2(list_counter_action, list_counter_action, true);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::naming::gid_type const&,
    hpx::detail::list_counter_info
> list_counter_info_action;
HPX_REGISTER_PLAIN_ACTION_EX2(list_counter_info_action, list_counter_info_action, true);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::naming::gid_type const&,
    hpx::detail::list_symbolic_name
> list_symbolic_name_action;
HPX_REGISTER_PLAIN_ACTION_EX2(list_symbolic_name_action, list_symbolic_name_action, true);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::components::component_type,
    hpx::detail::list_component_type
> list_component_type_action;
HPX_REGISTER_PLAIN_ACTION_EX2(list_component_type_action, list_component_type_action, true);

namespace hpx { namespace detail
{
    // print string on the console
    void console_print(std::string const& name)
    {
        std::cout << name << std::endl;
    }

    // redirect the printing of the given counter name to the console
    void list_counter(std::string const& name, naming::gid_type const& gid)
    {
        if (sizeof(hpx::performance_counters::counter_prefix)-1 <= name.size() &&
            0 == name.find(hpx::performance_counters::counter_prefix))
        {
            typedef lcos::eager_future<console_print_action> future_type;

            naming::gid_type console;
            naming::get_agas_client().get_console_prefix(console);
            future_type(console, name).get();
        }
    }

    // redirect the printing of the full counter info to the console
    void list_counter_info(std::string const& name, naming::gid_type const& gid)
    {
        if (sizeof(hpx::performance_counters::counter_prefix)-1 <= name.size() &&
            0 == name.find(hpx::performance_counters::counter_prefix))
        {
            using hpx::performance_counters::stubs::performance_counter;

            performance_counters::counter_info info =
                performance_counter::get_info(gid);

            // compose the information to be printed for each of the counters
            util::osstream strm;
            strm << std::string(78, '-') << '\n';
            strm << "fullname: " << info.fullname_ << '\n';
            strm << "helptext: " << info.helptext_ << '\n';
            strm << "type:     "
                 << performance_counters::get_counter_type_name(info.type_)
                 << '\n';

            boost::format fmt("%d.%d.%d\n");
            strm << "version:  "        // 0xMMmmrrrr
                 << boost::str(fmt % (info.version_ / 0x1000000) %
                        (info.version_ / 0x10000 % 0x100) %
                        (info.version_ % 0x10000));
            strm << std::string(78, '-') << '\n';

            typedef lcos::eager_future<console_print_action> future_type;
            naming::gid_type console;
            naming::get_agas_client().get_console_prefix(console);
            future_type(console, strm.str()).get();
        }
    }

    void list_symbolic_name(std::string const& name,
        naming::gid_type const& gid)
    {
        util::osstream strm;

        strm << name << ", "
             << gid << ", "
             << ( naming::get_credit_from_gid(gid)
                ? "managed"
                : "unmanaged");

        typedef lcos::eager_future<console_print_action> future_type;

        naming::gid_type console;
        naming::get_agas_client().get_console_prefix(console);
        future_type(console, strm.str()).get();
    }

    template <typename Action>
    int list_symbolic_names(boost::program_options::variables_map& vm,
        hpx_main_func f, std::string const& text)
    {
        {
            if (!text.empty())
                std::cout << text << std::endl;

            typedef void iter_func(std::string const&, naming::gid_type const&);

            hpx::actions::function<iter_func> cb(new Action);
            naming::get_agas_client().iterateids(cb);
        }

        if (0 != f)
            return f(vm);

        // we assume that we need to exit execution if no hpx_main is given
        finalize();
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    void list_component_type(std::string const& name,
        components::component_type ctype)
    {
        char const* fmt = "%1%, %|40t|%2%";

        std::string const s = boost::str(boost::format(fmt)
            % name % components::get_component_type_name(ctype));

        typedef lcos::eager_future<console_print_action> future_type;

        naming::gid_type console;
        naming::get_agas_client().get_console_prefix(console);
        future_type(console, s).get();
    }

    template <typename Action>
    int list_component_types(boost::program_options::variables_map& vm,
        hpx_main_func f, std::string const& text)
    {
        {
            if (!text.empty())
                std::cout << text << std::endl;

            typedef void iter_func(std::string const&,
                components::component_type);

            hpx::actions::function<iter_func> cb(new Action);
            naming::get_agas_client().iterate_types(cb);
        }

        if (0 != f)
            return f(vm);

        // we assume that we need to exit execution if no hpx_main is given
        finalize();
        return 0;
    }

    int print_counters(boost::program_options::variables_map& vm,
        hpx_main_func f, boost::shared_ptr<util::query_counters> const& qc)
    {
        {
            BOOST_ASSERT(qc);
            qc->start();
        }

        if (0 != f)
            return f(vm);

        // we assume that we need to exit execution if no hpx_main is given
        finalize();
        return 0;
    }
}}

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
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        int print_version(std::ostream& out)
        {
            out << std::endl << hpx::copyright() << std::endl;
            out << hpx::complete_version() << std::endl;
            return 0;
        }


        ///////////////////////////////////////////////////////////////////////
        template <typename Runtime>
        struct dump_config
        {
            dump_config(Runtime const& rt) : rt_(boost::cref(rt)) {}

            void operator()() const
            {
                std::cout << "Configuration after runtime start:\n";
                std::cout << "----------------------------------\n";
                rt_.get().get_config().dump(0, std::cout);
                std::cout << "----------------------------------\n";
            }

            boost::reference_wrapper<Runtime const> rt_;
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Runtime>
        int run_special(Runtime& rt, hpx::hpx_main_func f,
            boost::program_options::variables_map& vm, std::size_t num_threads,
            std::size_t num_localities, int& result)
        {
            // sanity checking
            std::size_t const list_count = vm.count("list-counters") +
                vm.count("list-counter-infos") +
                vm.count("list-symbolic-names") +
                vm.count("list-component-types");
            std::size_t const print_count = vm.count("print-counter") +
                vm.count("print-counter-interval");

            if (list_count && print_count) {
                throw std::logic_error("The --list-* options cannot be used "
                    "in conjunction with any of the --print-* options.");
            }

            if (list_count > 1) {
                throw std::logic_error("Only one --list-* option may be "
                    "specified");
            }

            if (vm.count("list-counters")) {
                // Print the names of all registered performance counters and
                // then call f (if f is NULL, hpx::finalize() is called instead
                // and 0 is returned).
                result = rt.run(
                    boost::bind(&list_symbolic_names<list_counter_action>,
                        vm, f, "registered performance counters"),
                    num_threads, num_localities);
                return true;
            }
            else if (vm.count("list-counter-infos")) {
                // Print info about all registered performance counters and
                // then call f (if f is NULL, hpx::finalize() is called instead
                // and 0 is returned).
                result = rt.run(
                    boost::bind(&list_symbolic_names<list_counter_info_action>,
                        vm, f, "registered performance counters"),
                    num_threads, num_localities);
                return true;
            }
            else if (vm.count("list-symbolic-names")) {
                // Print all registered symbolic names and then call f (if f is
                // NULL, hpx::finalize() is called instead and 0 is returned).
                result = rt.run(
                    boost::bind(&list_symbolic_names<list_symbolic_name_action>,
                        vm, f, "registered symbolic names"),
                    num_threads, num_localities);
                return true;
            }
            else if (vm.count("list-component-types")) {
                // Print all registered component types and then call f (if f is
                // NULL, hpx::finalize() is called instead and 0 is returned).
                result = rt.run(
                    boost::bind(&list_component_types<list_component_type_action>,
                        vm, f, "registered dynamic component types"),
                    num_threads, num_localities);
                return true;
            }

            if (vm.count("print-counter")) {
                std::size_t interval = 0;
                if (vm.count("print-counter-interval"))
                    interval = vm["print-counter-interval"].as<std::size_t>();

                std::vector<std::string> counters =
                    vm["print-counter"].as<std::vector<std::string> >();

                // schedule the query function at startup, which will schedule
                // itself to run after the given interval
                boost::shared_ptr<util::query_counters> qc =
                    boost::make_shared<util::query_counters>(
                        boost::ref(counters), interval, boost::ref(std::cout));

                // schedule to run at shutdown
                rt.add_pre_shutdown_function(
                    boost::bind(&util::query_counters::evaluate, qc));

                if (0 != interval) {
                    result = rt.run(boost::bind(&print_counters, vm, f, qc),
                        num_threads, num_localities);
                    return true;
                }
            }
            else if (vm.count("print-counter-interval")) {
                throw std::logic_error("Invalid command line option "
                    "--print-counter-interval, valid in conjunction with "
                    "--print-counter only");
            }

            return false;
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename Runtime>
        int run(Runtime& rt, hpx_main_func f,
            boost::program_options::variables_map& vm, runtime_mode mode,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            if (vm.count("app-config"))
            {
                std::string config(vm["app-config"].as<std::string>());
                rt.get_config().load_application_configuration(config.c_str());
            }

            if (!!startup)
                rt.add_startup_function(startup);

            if (!!shutdown)
                rt.add_shutdown_function(shutdown);

            // Dump the configuration before all components have been loaded.
            if (vm.count("dump-config-initial")) {
                std::cout << "Configuration after runtime construction:\n";
                std::cout << "-----------------------------------------\n";
                rt.get_config().dump(0, std::cout);
                std::cout << "-----------------------------------------\n";
            }

            // Dump the configuration after all components have been loaded.
            if (vm.count("dump-config"))
            {
                if (vm.count("exit")) {
                    throw std::logic_error("The command line option --exit "
                        "cannot be used in conjunction with --dump-config, try "
                        "--dump-config-init --exit instead.");
                }
                rt.add_startup_function(dump_config<Runtime>(rt));
            }

            int result = 0;
            if (vm.count("exit")) {
                run_special(rt, hpx::hpx_main_func(0), vm, num_threads,
                    num_localities, result);
                return result;
            }

            // Run this runtime instance with a special hpx_main, returns false
            // otherwise
            if (run_special(rt, f, vm, num_threads, num_localities, result))
                return result;

            // Run this runtime instance using the given function f.
            if (0 != f)
                return rt.run(boost::bind(f, vm), num_threads, num_localities);

            // Run this runtime instance without an hpx_main
            return rt.run(num_threads, num_localities);
        }

#if defined(HPX_ENABLE_GLOBAL_SCHEDULER)
        ///////////////////////////////////////////////////////////////////////
        // global scheduler (one queue for all OS threads)
        int run_global(hpx_main_func f, boost::program_options::variables_map& vm,
            runtime_mode mode, std::vector<std::string> const& ini_config,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("Invalid command line option "
                    "--high-priority-threads, valid for "
                    "--queueing=priority_local only");
            }
#if defined(BOOST_WINDOWS)
            if (vm.count("numa-sensitive")) {
                throw std::logic_error("Invalid command line option "
                    "--numa-sensitive, valid for "
                    "--queueing=priority_local only");
            }
#endif
            if (vm.count("hierarchy-arity")) {
                throw std::logic_error("Invalid command line option "
                    "--hierarchy-arity, valid for --queueing=hierarchy only.");
            }

            // scheduling policy
            typedef hpx::threads::policies::global_queue_scheduler
                global_queue_policy;

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<global_queue_policy> runtime_type;
            runtime_type rt(mode, global_queue_policy::init_parameter_type(),
                vm["hpx-config"].as<std::string>(), ini_config);

            return run(rt, f, vm, mode, startup, shutdown, num_threads,
                num_localities);
        }
#endif

#if defined(HPX_ENABLE_LOCAL_SCHEDULER)
        ///////////////////////////////////////////////////////////////////////
        // local scheduler (one queue for each OS threads)
        int run_local(hpx_main_func f, boost::program_options::variables_map& vm,
            runtime_mode mode, std::vector<std::string> const& ini_config,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("Invalid command line option "
                    "--high-priority-threads, valid for "
                    "--queueing=priority_local only.");
            }
#if defined(BOOST_WINDOWS)
            if (vm.count("numa-sensitive")) {
                throw std::logic_error("Invalid command line option "
                    "--numa-sensitive, valid for "
                    "--queueing=priority_local only");
            }
#endif
            if (vm.count("hierarchy-arity")) {
                throw std::logic_error("Invalid command line option "
                    "--hierarchy-arity, valid for --queueing=hierarchy only.");
            }

            // scheduling policy
            typedef hpx::threads::policies::local_queue_scheduler
                local_queue_policy;
            local_queue_policy::init_parameter_type init(num_threads, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<local_queue_policy> runtime_type;
            runtime_type rt(mode, init, vm["hpx-config"].as<std::string>(),
                ini_config);

            return run(rt, f, vm, mode, startup, shutdown, num_threads,
                num_localities);
        }
#endif

        ///////////////////////////////////////////////////////////////////////
        // local scheduler with priority queue (one queue for each OS threads
        // plus one separate queue for high priority PX-threads)
        int run_priority_local(hpx_main_func f, boost::program_options::variables_map& vm,
            runtime_mode mode, std::vector<std::string> const& ini_config,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            std::size_t num_high_priority_queues = num_threads;
            if (vm.count("high-priority-threads")) {
                num_high_priority_queues =
                    vm["high-priority-threads"].as<std::size_t>();
            }
            bool numa_sensitive = false;
#if defined(BOOST_WINDOWS)
            if (vm.count("numa-sensitive"))
                numa_sensitive = true;
#endif
            if (vm.count("hierarchy-arity")) {
                throw std::logic_error("Invalid command line option "
                    "--hierarchy-arity, valid for --queueing=hierarchy only.");
            }

            // scheduling policy
            typedef hpx::threads::policies::local_priority_queue_scheduler
                local_queue_policy;
            local_queue_policy::init_parameter_type init(
                num_threads, num_high_priority_queues, 1000, numa_sensitive);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<local_queue_policy> runtime_type;
            runtime_type rt(mode, init, vm["hpx-config"].as<std::string>(),
                ini_config);

            return run(rt, f, vm, mode, startup, shutdown, num_threads,
                num_localities);
        }

#if defined(HPX_ENABLE_ABP_SCHEDULER)
        ///////////////////////////////////////////////////////////////////////
        // abp scheduler: local deques for each OS thread, with work
        // stealing from the "bottom" of each.
        int run_abp(hpx_main_func f, boost::program_options::variables_map& vm,
            runtime_mode mode, std::vector<std::string> const& ini_config,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("Invalid command line option "
                    "--high-priority-threads, valid for "
                    "--queueing=priority_local only.");
            }
#if defined(BOOST_WINDOWS)
            if (vm.count("numa-sensitive")) {
                throw std::logic_error("Invalid command line option "
                    "--numa-sensitive, valid for "
                    "--queueing=priority_local only");
            }
#endif
            if (vm.count("hierarchy-arity")) {
                throw std::logic_error("Invalid command line option "
                    "--hierarchy-arity, valid for --queueing=hierarchy only.");
            }

            // scheduling policy
            typedef hpx::threads::policies::abp_queue_scheduler
                abp_queue_policy;
            abp_queue_policy::init_parameter_type init(num_threads, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<abp_queue_policy> runtime_type;
            runtime_type rt(mode, init, vm["hpx-config"].as<std::string>(),
                ini_config);

            return run(rt, f, vm, mode, startup, shutdown, num_threads,
                num_localities);
        }
#endif

        ///////////////////////////////////////////////////////////////////////
        // hierarchical scheduler: The thread queues are built up hierarchically
        // this avoids contention during work stealing
        int run_hierarchy(hpx_main_func f, boost::program_options::variables_map& vm,
            runtime_mode mode, std::vector<std::string> const& ini_config,
            startup_function_type const& startup,
            shutdown_function_type const& shutdown, std::size_t num_threads,
            std::size_t num_localities)
        {
            if (vm.count("high-priority-threads")) {
                throw std::logic_error("Invalid command line option "
                    "--high-priority-threads, valid for "
                    "--queueing=priority_local only.");
            }
#if defined(BOOST_WINDOWS)
            if (vm.count("numa-sensitive")) {
                throw std::logic_error("Invalid command line option "
                    "--numa-sensitive, valid for "
                    "--queueing=priority_local only");
            }
#endif
            std::size_t arity = 2;
            if (vm.count("hierarchy-arity")) {
                arity = vm["hierarchy-arity"].as<std::size_t>();
            }
            // scheduling policy
            typedef hpx::threads::policies::hierarchy_scheduler
                queue_policy;
            queue_policy::init_parameter_type
                init(num_threads, arity, 1000);

            // Build and configure this runtime instance.
            typedef hpx::runtime_impl<queue_policy> runtime_type;
            runtime_type rt(mode, init, vm["hpx-config"].as<std::string>(),
                ini_config);

            return run(rt, f, vm, mode, startup, shutdown, num_threads,
                num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        void set_signal_handlers()
        {
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
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    int init(hpx_main_func f,
        boost::program_options::options_description& desc_cmdline,
        int argc, char* argv[], std::vector<std::string> ini_config,
        startup_function_type startup, shutdown_function_type shutdown,
        hpx::runtime_mode mode)
    {
        int result = 0;
        detail::set_signal_handlers();

        try {
            using boost::program_options::variables_map;
            using namespace boost::assign;

            // Analyze the command line.
            variables_map vm;
            boost::program_options::options_description help;
            if (!util::parse_commandline(desc_cmdline, argc, argv, vm, mode, &help))
                return -1;

            // print version/copyright information
            if (vm.count("version"))
                return detail::print_version(std::cout);

            if (vm.count("help")) {
                std::cout << help << std::endl;
                return 0;
            }

            bool debug_clp = vm.count("debug-clp") ? true : false;

            // create host name mapping
            util::map_hostnames mapnames(debug_clp);
            if (vm.count("ifsuffix"))
                mapnames.use_suffix(vm["ifsuffix"].as<std::string>());
            if (vm.count("ifprefix"))
                mapnames.use_prefix(vm["ifprefix"].as<std::string>());

            // The AGAS host name and port number are pre-initialized from
            //the command line
            std::string agas_host;
            boost::uint16_t agas_port = HPX_INITIAL_IP_PORT;
            if (vm.count("agas"))
                util::split_ip_address(vm["agas"].as<std::string>(), agas_host, agas_port);

            // Check command line arguments.
            util::pbs_environment env(debug_clp);

            if (vm.count("iftransform")) {
                util::sed_transform iftransform(vm["iftransform"].as<std::string>());

                // Check for parsing failures
                if (!iftransform) {
                    throw std::logic_error(boost::str(boost::format(
                        "Could not parse --iftransform argument '%1%'") %
                        vm["iftransform"].as<std::string>()));
                }

                typedef util::pbs_environment::transform_function_type
                    transform_function_type;
                env.use_transform(transform_function_type(iftransform));
            }

            if (vm.count("nodefile")) {
                if (vm.count("nodes")) {
                    throw std::logic_error("Ambiguous command line options. "
                        "Do not specify more than one of the --nodefile and "
                        "--nodes options at the same time.");
                }
                ini_config += "hpx.nodefile=" +
                    env.init_from_file(vm["nodefile"].as<std::string>(), agas_host);
            }
            else if (vm.count("nodes")) {
                ini_config += "hpx.nodes=" + env.init_from_nodelist(
                    vm["nodes"].as<std::vector<std::string> >(), agas_host);
            }

            // let the PBS environment decide about the AGAS host
            agas_host = env.agas_host_name(
                agas_host.empty() ? HPX_INITIAL_IP_ADDRESS : agas_host);

            std::string hpx_host(env.host_name(HPX_INITIAL_IP_ADDRESS));
            boost::uint16_t hpx_port = HPX_INITIAL_IP_PORT;
            std::size_t num_threads = env.retrieve_number_of_threads();
            bool run_agas_server = vm.count("run-agas-server") ? true : false;

            std::size_t num_localities = env.retrieve_number_of_localities();
            if (vm.count("localities"))
                num_localities = vm["localities"].as<std::size_t>();

            std::size_t node = env.retrieve_node_number();

            // we initialize certain settings if --node is specified (or data
            // has been retrieved from the environment)
            if (node != std::size_t(-1) || vm.count("node")) {
                // command line overwrites the environment
                if (vm.count("node")) {
                    if (vm.count("agas")) {
                        throw std::logic_error("Command line option --node "
                            "is not compatible with --agas/-a");
                    }
                    node = vm["node"].as<std::size_t>();
                    if (1 == num_localities && !vm.count("localities")) {
                        throw std::logic_error("Command line option --node "
                            "requires to specify the number of localities as "
                            "well (for instance by using --localities/-l)");
                    }
                }
                if (env.agas_node() == node) {
                    // console node, by default runs AGAS
                    run_agas_server = true;
                    mode = hpx::runtime_mode_console;
                }
                else {
                    hpx_port += node;         // each node gets an unique port
                    mode = hpx::runtime_mode_worker;

                    // do not execute any explicit hpx_main except if asked
                    // otherwise
                    if (!vm.count("run-hpx-main"))
                        f = 0;
                }
                // store node number in configuration
                ini_config += "hpx.locality=" +
                    boost::lexical_cast<std::string>(node + 1);
            }

            if (vm.count("ini")) {
                std::vector<std::string> cfg =
                    vm["ini"].as<std::vector<std::string> >();
                std::copy(cfg.begin(), cfg.end(), std::back_inserter(ini_config));
            }

            if (vm.count("hpx"))
                util::split_ip_address(vm["hpx"].as<std::string>(), hpx_host, hpx_port);

            if (vm.count("threads"))
                num_threads = vm["threads"].as<std::size_t>();

            std::string queueing("priority_local");
            if (vm.count("queueing"))
                queueing = vm["queueing"].as<std::string>();

            // If the user has not specified an explicit runtime mode we
            // retrieve it from the command line.
            if (hpx::runtime_mode_default == mode) {
                // The default mode is console, i.e. all workers need to be
                // started with --worker/-w.
                mode = hpx::runtime_mode_console;
                if (vm.count("console") + vm.count("worker") + vm.count("connect") > 1) {
                    throw std::logic_error("Ambiguous command line options. "
                        "Do not specify more than one of --console/-c, "
                        "--worker/-w, or --connect");
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

            // map host names to ip addresses, if requested
            hpx_host = mapnames.map(hpx_host, hpx_port);
            agas_host = mapnames.map(agas_host, agas_port);

            // sanity checks
            if (num_localities == 1 && !vm.count("agas") && !vm.count("node")) {
                // We assume we have to run the AGAS server if the number of
                // localities to run on is not specified (or is '1')
                // and no additional option (--agas or --node) has been
                // specified. That simplifies running small standalone
                // applications on one locality.
                run_agas_server = true;
            }

            if (hpx_host == agas_host && hpx_port == agas_port) {
                // we assume that we need to run the agas server if the user
                // asked for the same network addresses for HPX and AGAS
                run_agas_server = true;
            }
            else if (run_agas_server) {
                // otherwise, if the user instructed us to run the AGAS server,
                // we set the AGAS network address to the same value as the HPX
                // network address
                agas_host = hpx_host;
                agas_port = hpx_port;
            }
            else if (env.run_with_pbs()) {
                // in PBS mode, if the network addresses are different and we
                // should not run the AGAS server we assume to be in worker mode
                mode = hpx::runtime_mode_worker;

                // do not execute any explicit hpx_main except if asked
                // otherwise
                if (!vm.count("run-hpx-main"))
                    f = 0;
            }

            // write HPX and AGAS network parameters to the proper ini-file entries
            ini_config += "hpx.address=" + hpx_host;
            ini_config += "hpx.port=" + boost::lexical_cast<std::string>(hpx_port);
            ini_config += "hpx.agas.address=" + agas_host;
            ini_config += "hpx.agas.port=" + boost::lexical_cast<std::string>(agas_port);

            if (run_agas_server) {
                ini_config += "hpx.agas.service_mode=bootstrap";
                if (vm.count("run-agas-server-only"))
                    ini_config += "hpx.components.load_external=0";
            }
            else if (vm.count("run-agas-server-only") && !env.run_with_pbs()) {
                throw std::logic_error("Command line option --run-agas-server-only "
                    "can be specified only for the node running the AGAS server.");
            }
            if (1 == num_localities && vm.count("run-agas-server-only")) {
                std::cerr  << "hpx::init: command line warning: --run-agas-server-only "
                    "used for single locality execution, application might "
                    "not run properly." << std::endl;
            }

            // Set whether the AGAS server is running as a dedicated runtime.
            // This decides whether the AGAS actions are executed with normal
            // priority (if dedicated) or with high priority (non-dedicated)
            if (vm.count("run-agas-server-only"))
                ini_config += "hpx.agas.dedicated_server=1";

            if (vm.count("debug-hpx-log")) {
                ini_config += "hpx.logging.console.destination=" +
                    vm["debug-hpx-log"].as<std::string>();
                ini_config += "hpx.logging.destination=" +
                    vm["debug-hpx-log"].as<std::string>();
                ini_config += "hpx.logging.console.level=5";
                ini_config += "hpx.logging.level=5";
            }

            if (vm.count("debug-agas-log")) {
                ini_config += "hpx.logging.console.agas.destination=" +
                    vm["debug-agas-log"].as<std::string>();
                ini_config += "hpx.logging.agas.destination=" +
                    vm["debug-agas-log"].as<std::string>();
                ini_config += "hpx.logging.console.agas.level=5";
                ini_config += "hpx.logging.agas.level=5";
            }

            // Collect the command line for diagnostic purposes.
            std::string cmd_line;
            for (int i = 0; i < argc; ++i)
            {
                // quote only if it contains whitespace
                std::string arg(argv[i]);
                if (arg.find_first_of(" \t") != std::string::npos)
                    cmd_line += std::string("\"") + arg + "\"";
                else
                    cmd_line += arg;

                if ((i + 1) != argc)
                    cmd_line += " ";
            }

            // Store the program name and the command line.
            ini_config += "hpx.program_name=" + std::string(argv[0]);
            ini_config += "hpx.cmd_line=" + cmd_line;

            // Set number of OS threads in configuration.
            ini_config += "hpx.os_threads=" +
                boost::lexical_cast<std::string>(num_threads);

            // Set number of localities in configuration (do it everywhere,
            // even if this information is only used by the AGAS server).
            ini_config += "hpx.localities=" +
                boost::lexical_cast<std::string>(num_localities);

            // FIXME: AGAS V2: if a locality is supposed to run the AGAS
            //        service only and requests to use 'priority_local' as the
            //        scheduler, switch to the 'local' scheduler instead.
            ini_config += std::string("hpx.runtime_mode=") +
                get_runtime_mode_name(mode);

            if (debug_clp) {
                std::cerr << "Configuration before runtime start:\n";
                std::cerr << "-----------------------------------\n";
                BOOST_FOREACH(std::string const& s, ini_config) {
                    std::cerr << s << std::endl;
                }
                std::cerr << "-----------------------------------\n";
            }

            // Initialize and start the HPX runtime.
            if (0 == std::string("global").find(queueing)) {
#if defined(HPX_ENABLE_GLOBAL_SCHEDULER)
                result = detail::run_global(f, vm, mode, ini_config,
                    startup, shutdown, num_threads, num_localities);
#else
                throw std::logic_error("Command line option --queueing=global "
                    "is not configured in this build. Please rebuild with "
                    "'cmake -DHPX_ENABLE_GLOBAL_SCHEDULER'.");
#endif
            }
            else if (0 == std::string("local").find(queueing)) {
#if defined(HPX_ENABLE_LOCAL_SCHEDULER)
                result = detail::run_local(f, vm, mode, ini_config,
                    startup, shutdown, num_threads, num_localities);
#else
                throw std::logic_error("Command line option --queueing=local "
                    "is not configured in this build. Please rebuild with "
                    "'cmake -DHPX_ENABLE_LOCAL_SCHEDULER'.");
#endif
            }
            else if (0 == std::string("priority_local").find(queueing)) {
                // local scheduler with priority queue (one queue for each OS threads
                // plus one separate queue for high priority PX-threads)
                result = detail::run_priority_local(f, vm, mode, ini_config,
                    startup, shutdown, num_threads, num_localities);
            }
            else if (0 == std::string("abp").find(queueing)) {
                // abp scheduler: local dequeues for each OS thread, with work
                // stealing from the "bottom" of each.
#if defined(HPX_ENABLE_ABP_SCHEDULER)
                result = detail::run_abp(f, vm, mode, ini_config,
                    startup, shutdown, num_threads, num_localities);
#else
                throw std::logic_error("Command line option --queueing=abp "
                    "is not configured in this build. Please rebuild with "
                    "'cmake -DHPX_ENABLE_ABP_SCHEDULER'.");
#endif
            }
            else if (0 == std::string("hierarchy").find(queueing)) {
                // hierarchy scheduler: tree of dequeues, with work
                // stealing from the parent queue in that tree.
                result = detail::run_hierarchy(f, vm, mode, ini_config,
                    startup, shutdown, num_threads, num_localities);
            }
            else {
                throw std::logic_error("Bad value for command line option "
                    "--queueing/-q");
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
    namespace detail
    {
        template <typename T>
        inline T
        get_option(std::string const& config, T default_ = T())
        {
            if (!config.empty()) {
                try {
                    return boost::lexical_cast<T>(
                        get_runtime().get_config().get_entry(config, default_));
                }
                catch (boost::bad_lexical_cast const&) {
                    ;   // do nothing
                }
            }
            return default_;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    void finalize(double shutdown_timeout, double localwait)
    {
        if (localwait == -1.0)
            localwait = detail::get_option("hpx.finalize_wait_time", -1.0);

        if (localwait != -1.0) {
            hpx::util::high_resolution_timer t;
            double start_time = t.elapsed();
            double current = 0.0;
            do {
                current = t.elapsed();
            } while (current - start_time < localwait * 1e-6);
        }

        if (shutdown_timeout == -1.0)
            shutdown_timeout = detail::get_option("hpx.shutdown_timeout", -1.0);

        components::stubs::runtime_support::shutdown_all(
            naming::get_id_from_prefix(HPX_AGAS_BOOTSTRAP_PREFIX)
          , shutdown_timeout);
    }

    ///////////////////////////////////////////////////////////////////////////
    void disconnect(double shutdown_timeout, double localwait)
    {
        if (localwait == -1.0)
            localwait = detail::get_option("hpx.finalize_wait_time", -1.0);

        if (localwait != -1.0) {
            hpx::util::high_resolution_timer t;
            double start_time = t.elapsed();
            double current = 0.0;
            do {
                current = t.elapsed();
            } while (current - start_time < localwait * 1e-6);
        }

        if (shutdown_timeout == -1.0)
            shutdown_timeout = detail::get_option("hpx.shutdown_timeout", -1.0);

        components::server::runtime_support* p =
            reinterpret_cast<components::server::runtime_support*>(
                  get_runtime().get_runtime_support_lva());

        p->call_shutdown_functions(true);
        p->call_shutdown_functions(false);
        p->shutdown(shutdown_timeout);
    }

    ///////////////////////////////////////////////////////////////////////////
    void terminate()
    {
        components::stubs::runtime_support::terminate_all(
            naming::get_id_from_prefix(HPX_AGAS_BOOTSTRAP_PREFIX));
    }
}


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

#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/components/runtime_support.hpp>
#include <hpx/runtime/actions/function.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/include/performance_counters.hpp>
#include <hpx/util/stringstream.hpp>

#if !defined(BOOST_WINDOWS)
    #include <signal.h>
#endif

#include <iostream>
#include <fstream>
#include <cctype>
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
    void print_counter(std::string const& name);
    void list_counter(std::string const& name, naming::gid_type const& gid);
    void list_counter_info(std::string const& name, naming::gid_type const& gid);
}}

typedef hpx::actions::plain_action1<
    std::string const&, hpx::detail::print_counter
> print_counter_action;
HPX_REGISTER_PLAIN_ACTION(print_counter_action);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::naming::gid_type const&, 
    hpx::detail::list_counter
> list_counter_action;
HPX_REGISTER_PLAIN_ACTION(list_counter_action);

typedef hpx::actions::plain_action2<
    std::string const&, hpx::naming::gid_type const&, 
    hpx::detail::list_counter_info
> list_counter_info_action;
HPX_REGISTER_PLAIN_ACTION(list_counter_info_action);

namespace hpx { namespace detail
{
    // print counter value on the console
    void print_counter(std::string const& name)
    {
        std::cout << name << std::endl;
    }

    // redirect the printing of the given counter name to the console
    void list_counter(std::string const& name, naming::gid_type const& gid)
    {
        char const prefix[] = "/counters";
        if (sizeof(prefix)-1 <= name.size() && 0 == name.find(prefix))
        {
            typedef lcos::eager_future<print_counter_action> future_type;

            naming::gid_type console;
            naming::get_agas_client().get_console_prefix(console);
            future_type(console, name).get();
        }
    }

    // redirect the printing of the full counter info to the console
    void list_counter_info(std::string const& name, naming::gid_type const& gid)
    {
        char const prefix[] = "/counters";
        if (sizeof(prefix)-1 <= name.size() && 0 == name.find(prefix))
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

            typedef lcos::eager_future<print_counter_action> future_type;
            naming::gid_type console;
            naming::get_agas_client().get_console_prefix(console);
            future_type(console, strm.str()).get();
        }
    }

    // iterate all registered performance counters and invoke printing their
    // names
    template <typename Action>
    int list_counters(boost::program_options::variables_map& vm, 
        hpx_main_func f)
    {
        {
            std::cout << "registered performance counters" << std::endl; 
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
        // Additional command line parser which interprets '@something' as an 
        // option "options-file" with the value "something". Additionally we 
        // map any option -N (where N is a integer) to --node=N.
        inline std::pair<std::string, std::string> 
        option_parser(std::string const& s)
        {
            if ('@' == s[0]) 
                return std::make_pair(std::string("options-file"), s.substr(1));

            if ('-' == s[0] && s.size() > 1 && std::isdigit(s[1])) {
                try {
                    // test, whether next argument is an integer
                    boost::lexical_cast<std::size_t>(s.substr(1));
                    return std::make_pair(std::string("node"), s.substr(1));
                }
                catch (boost::bad_lexical_cast const&) {
                    ;   // ignore
                }
            }
            return std::pair<std::string, std::string>();
        }

        ///////////////////////////////////////////////////////////////////////
        // Read all options from a given config file, parse and add them to the
        // given variables_map
        bool read_config_file_options(std::string const &filename, 
            boost::program_options::options_description const &desc, 
            boost::program_options::variables_map &vm, bool may_fail = false)
        {
            std::ifstream ifs(filename.c_str());
            if (!ifs.is_open()) {
                if (!may_fail) {
                    std::cerr << filename 
                        << ": command line warning: command line options file not found"
                        << std::endl;
                }
                return false;
            }

            std::vector<std::string> options;
            std::string line;
            while (std::getline(ifs, line)) {
                // skip empty lines
                std::string::size_type pos = line.find_first_not_of(" \t");
                if (pos == std::string::npos) 
                    continue;

                // skip comment lines
                if ('#' != line[pos]) {
                    // strip leading and trailing whitespace
                    std::string::size_type endpos = line.find_last_not_of(" \t");
                    BOOST_ASSERT(endpos != std::string::npos);
                    options.push_back(line.substr(pos, endpos-pos+1));
                }
            }

            // add options to parsed settings
            if (options.size() > 0) {
                using boost::program_options::value;
                using boost::program_options::store;
                using boost::program_options::command_line_parser;
                using namespace boost::program_options::command_line_style;

                store(command_line_parser(options)
                    .options(desc).style(unix_style).run(), vm);
                notify(vm);
            }
            return true;
        }

        // try to find a config file somewhere up the filesystem hierarchy 
        // starting with the input file path. This allows to use a general wave.cfg 
        // file for all files in a certain project.
        void handle_generic_config_options(std::string appname,
            boost::program_options::variables_map& vm,
            boost::program_options::options_description const& desc_cfgfile)
        {
            if (appname.empty())
                return;

            boost::filesystem::path dir (boost::filesystem::initial_path());
            boost::filesystem::path app (appname);
            appname = boost::filesystem::basename(app.filename());

            // walk up the hierarchy, trying to find a file appname.cfg 
            while (!dir.empty()) {
                boost::filesystem::path filename = dir / (appname + ".cfg");
                if (read_config_file_options(filename.string(), desc_cfgfile, vm, true))
                    break;    // break on the first options file found

                dir = dir.parent_path();    // chop off last directory part
            }
        }

        // handle all --options-config found on the command line
        void handle_config_options(boost::program_options::variables_map& vm,
            boost::program_options::options_description const& desc_cfgfile)
        {
            using boost::program_options::options_description;
            if (vm.count("options-file")) {
                std::vector<std::string> const &cfg_files = 
                    vm["options-file"].as<std::vector<std::string> >();
                BOOST_FOREACH(std::string const& cfg_file, cfg_files)
                {
                    // parse a single config file and store the results
                    read_config_file_options(cfg_file, desc_cfgfile, vm);
                }
            }
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
            using boost::program_options::parsed_options;
            using namespace boost::program_options::command_line_style;

            try {
                options_description cmdline_options(
                    "HPX options (allowed on command line only)");
                cmdline_options.add_options()
                    ("help,h", "print out program usage (this message)")
                    ("version,v", "print out HPX version and copyright information")
                    ("options-file", value<std::vector<std::string> >()->composing(), 
                        "specify a file containing command line options "
                        "(alternatively: @filepath)")
                ;

                options_description hpx_options(
                    "HPX options (additionally allowed in an options file)");
                options_description hidden_options("Hidden options");

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

                // general options definitions
                hpx_options.add_options()
                    ("run-agas-server,r",
                     "run AGAS server as part of this runtime instance")
                    ("run-hpx-main",
                     "run the hpx_main function, regardless of locality mode")
                    ("agas,a", value<std::string>(), 
                     "the IP address the AGAS server is running on, "
                     "expected format: `address:port' (default: "
                     "127.0.0.1:7910)")
                    ("hpx,x", value<std::string>(), 
                     "the IP address the HPX parcelport is listening on, "
                     "expected format: `address:port' (default: "
                     "127.0.0.1:7910)")
                    ("nodefile", value<std::string>(), 
                      "the file name of a node file to use (list of nodes, one "
                      "node name per line and core)")
                    ("nodes", value<std::vector<std::string> >()->multitoken(), 
                      "the (space separated) list of the nodes to use (usually "
                      "this is extracted from a node file)")
                    ("ifsuffix", value<std::string>(), 
                      "suffix to append to host names in order to resolve them "
                      "to the proper network interconnect")
                    ("localities,l", value<std::size_t>(), 
                     "the number of localities to wait for at application "
                     "startup (default: 1)")
                    ("node", value<std::size_t>(), 
                     "number of the node this locality is run on "
                     "(must be unique, alternatively: -1, -2, etc.)")
                    ("threads,t", value<std::size_t>(), 
                     "the number of operating system threads to dedicate as "
                     "shepherd threads for this HPX locality (default: 1)")
                    ("queueing,q", value<std::string>(),
                     "the queue scheduling policy to use, options are `global/g', "
                     "`local/l', `priority_local/p' and `abp/a' (default: priority_local/p)")
                    ("high-priority-threads", value<std::size_t>(), 
                     "the number of operating system threads maintaining a high "
                     "priority queue (default: number of OS threads), valid for "
                     "--queueing=priority_local only")
                ;

                options_description config_options("HPX configuration options");
                config_options.add_options()
                    ("app-config,p", value<std::string>(), 
                     "load the specified application configuration (ini) file")
                    ("hpx-config", value<std::string>()->default_value(""), 
                     "load the specified hpx configuration (ini) file")
                    ("ini,I", value<std::vector<std::string> >()->composing(),
                     "add a configuration definition to the default runtime "
                     "configuration")
                    ("dump-config-initial", "print the initial runtime configuration")
                    ("dump-config", "print the final runtime configuration")
                    // enable debug output from command line handling
                    ("debug-clp", "debug command line processing")
                    ("exit", "exit after configuring the runtime")
                ;
                
                options_description counter_options(
                    "HPX options related to performance counters");
                counter_options.add_options()
                    ("print-counter", value<std::vector<std::string> >()->composing(),
                     "print the specified performance counter before shutting "
                     "down the system")
                    ("list-counters", "list the names of all registered performance "
                     "counters")
                    ("list-counter-infos", "list the description of all registered "
                     "performance counters")
                ;

                // construct the overall options description and parse the 
                // command line
                options_description desc_cmdline;
                desc_cmdline
                    .add(app_options).add(cmdline_options)
                    .add(hpx_options).add(counter_options)
                    .add(config_options).add(hidden_options)
                ;
                parsed_options opts(parse_command_line(argc, argv, 
                    desc_cmdline, unix_style, option_parser));
                store(opts, vm);
                notify(vm);

                options_description desc_cfgfile;
                desc_cfgfile
                    .add(app_options).add(hpx_options)
                    .add(counter_options).add(config_options)
                    .add(hidden_options);

                handle_generic_config_options(argv[0], vm, desc_cfgfile);
                handle_config_options(vm, desc_cfgfile);

                // print version/copyright information 
                if (vm.count("version")) 
                    return print_version();

                // print help screen
                if (vm.count("help")) {
                    boost::program_options::options_description visible;
                    visible
                        .add(app_options).add(cmdline_options)
                        .add(hpx_options).add(counter_options)
                        .add(config_options)
                    ;
                    std::cout << visible;
                    return help;
                }
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
        void print_shutdown_counters(std::vector<std::string> const& names)
        {
            std::cout << "performance counter values (at shutdown):\n";

            BOOST_FOREACH(std::string const& name, names)
            {
                error_code ec;
                naming::gid_type gid;
                naming::get_agas_client().queryid(name, gid, ec);

                if (HPX_UNLIKELY(ec || !gid))
                {
                    HPX_THROW_EXCEPTION(bad_parameter,
                        "print_shutdown_counters",
                        boost::str(boost::format(
                            "unknown performance counter: '%s'") % name))
                }

                using hpx::performance_counters::stubs::performance_counter;
                using hpx::performance_counters::status_valid_data;

                // Query the performance counter.
                double value = performance_counter::get_typed_value<double>(gid, ec);
                if (!ec)
                    std::cout << name << "," << value << "\n"; 
                else
                    std::cout << name << ",invalid\n"; 
            }
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename Runtime>
        struct dump_config
        {
            dump_config(Runtime const& rt) : rt_(rt) {}

            void operator()() const
            {
                std::cout << "Configuration after runtime start:\n";
                std::cout << "----------------------------------\n";
                rt_.get_config().dump(0, std::cout);
                std::cout << "----------------------------------\n";
            }

            Runtime const& rt_;
        };

        template <typename Runtime>
        int run(Runtime& rt, hpx_main_func f, 
            boost::program_options::variables_map& vm, runtime_mode mode, 
            startup_func const& startup, shutdown_func const& shutdown, 
            std::size_t num_threads, std::size_t num_localities)
        {
            if (vm.count("app-config"))
            {
                std::string config(vm["app-config"].as<std::string>());
                rt.get_config().load_application_configuration(config.c_str());
            }

            if (vm.count("print-counter")) {
                std::vector<std::string> counters = 
                    vm["print-counter"].as<std::vector<std::string> >();
                rt.add_shutdown_function(
                    boost::bind(print_shutdown_counters, counters));
            }

            if (!startup.empty())
                rt.add_startup_function(startup);

            if (!shutdown.empty())
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
                rt.add_startup_function(dump_config<Runtime>(rt));

            if (vm.count("exit")) { 
                if (vm.count("list-counters")) {
                    // Print all available performance counter names and then 
                    // call hpx::finalize() and return 0.
                    return rt.run(
                        boost::bind(&list_counters<list_counter_action>, 
                            vm, hpx::hpx_main_func(0)),
                        num_threads, num_localities);
                }
                else if (vm.count("list-counter-infos")) {
                    // Print all available performance counter infos and then 
                    // call hpx::finalize() and return 0.
                    return rt.run(
                        boost::bind(&list_counters<list_counter_info_action>, 
                            vm, hpx::hpx_main_func(0)),
                        num_threads, num_localities);
                }
                return 0;
            }

            if (vm.count("list-counters")) {
                // Print out all available performance counter names and then 
                // call f.
                return rt.run(
                    boost::bind(&list_counters<list_counter_action>, vm, f),
                    num_threads, num_localities);
            }
            else if (vm.count("list-counter-infos")) {
                // Print out all available performance counter infos and then 
                // call f.
                return rt.run(
                    boost::bind(&list_counters<list_counter_info_action>, vm, f),
                    num_threads, num_localities);
            }

            if (0 != f) {
                // Run this runtime instance using the given function f.
                return rt.run(boost::bind(f, vm), num_threads, num_localities);
            }

            // Run this runtime instance without an hpx_main
            return rt.run(num_threads, num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // global scheduler (one queue for all OS threads)
        int run_global(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup, shutdown_func const& shutdown, 
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

            return run(rt, f, vm, mode, startup, shutdown, num_threads, 
                num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // local scheduler (one queue for each OS threads)
        int run_local(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup, shutdown_func const& shutdown, 
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

            return run(rt, f, vm, mode, startup, shutdown, num_threads, 
                num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // local scheduler with priority queue (one queue for each OS threads
        // plus one separate queue for high priority PX-threads)
        int run_priority_local(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup, shutdown_func const& shutdown, 
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

            return run(rt, f, vm, mode, startup, shutdown, num_threads, 
                num_localities);
        }

        ///////////////////////////////////////////////////////////////////////
        // abp scheduler: local deques for each OS thread, with work
        // stealing from the "bottom" of each.
        int run_abp(std::string const& hpx_host, boost::uint16_t hpx_port, 
            std::string const& agas_host, boost::uint16_t agas_port, 
            hpx_main_func f, boost::program_options::variables_map& vm, 
            runtime_mode mode, std::vector<std::string> const& ini_config, 
            startup_func const& startup, shutdown_func const& shutdown, 
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
        startup_func startup, shutdown_func shutdown, hpx::runtime_mode mode)
    {
        int result = 0;
        detail::set_signal_handlers();

        try {
            using boost::program_options::variables_map; 
            using namespace boost::assign;

            // Analyze the command line.
            variables_map vm;
            detail::command_line_result r = detail::parse_commandline(
                desc_cmdline, argc, argv, vm, mode);

            if (detail::error == r)
                return 1;
            if (detail::help == r)
                return 0;

            bool debug_clp = vm.count("debug-clp") ? true : false;

            // create host name mapping
            util::map_hostnames mapnames(debug_clp);
            if (vm.count("ifsuffix")) 
                mapnames.use_suffix(vm["ifsuffix"].as<std::string>());

            // The AGAS host name and port number are pre-initialized from
            //the command line
            std::string agas_host;
            boost::uint16_t agas_port = HPX_INITIAL_IP_PORT;
            if (vm.count("agas")) {
                std::string host;
                boost::uint16_t port = HPX_INITIAL_IP_PORT;
                detail::split_ip_address(vm["agas"].as<std::string>(), host, port);
                if (!host.empty()) agas_host = host;
                if (!port) agas_port = port;
            }

            // Check command line arguments.
            util::pbs_environment env(debug_clp);
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
            agas_host = env.agas_host_name(HPX_INITIAL_IP_ADDRESS);

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
                    if (1 == num_localities) {
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
                    boost::lexical_cast<std::string>(node);
            }

            if (vm.count("ini")) {
                std::vector<std::string> cfg =
                    vm["ini"].as<std::vector<std::string> >();
                std::copy(cfg.begin(), cfg.end(), std::back_inserter(ini_config));
            }

            if (vm.count("hpx")) {
                std::string host;
                boost::uint16_t port = HPX_INITIAL_IP_PORT;
                detail::split_ip_address(vm["hpx"].as<std::string>(), host, port);
                if (!host.empty()) hpx_host = host;
                if (!port) hpx_port = port;
            }

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

            // write HPX and AGAS network parameters to the proper ini-file entries
            ini_config += "hpx.address=" + hpx_host;
            ini_config += "hpx.port=" + boost::lexical_cast<std::string>(hpx_port);
            ini_config += "hpx.agas.address=" + agas_host;
            ini_config += "hpx.agas.port=" + boost::lexical_cast<std::string>(agas_port);

            // We assume we have to run the AGAS server if
            //  - it's explicitly specified
            //  - the number of localities to run on is not specified (or is '1')
            //    and no additional option (--agas or --node) has been specified.
            if (run_agas_server || 
                (num_localities == 1 && !vm.count("agas") && !vm.count("node")))  
            {
                ini_config += "hpx.agas.router_mode=bootstrap"; 
            }

            // Collect the command line for diagnostic purposes.
            std::string cmd_line;
            for (int i = 0; i < argc; ++i)
            {
                cmd_line += std::string("'") + argv[i] + "'";
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
                result = detail::run_global(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup, shutdown, num_threads, num_localities);
            }
            else if (0 == std::string("local").find(queueing)) {
                result = detail::run_local(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup, shutdown, num_threads, num_localities);
            }
            else if (0 == std::string("priority_local").find(queueing)) {
                // local scheduler with priority queue (one queue for each OS threads
                // plus one separate queue for high priority PX-threads)
                result = detail::run_priority_local(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup, shutdown, num_threads, num_localities);
            }
            else if (0 == std::string("abp").find(queueing)) {
                // abp scheduler: local deques for each OS thread, with work
                // stealing from the "bottom" of each.
                result = detail::run_abp(hpx_host, hpx_port, 
                    agas_host, agas_port, f, vm, mode, ini_config, 
                    startup, shutdown, num_threads, num_localities);
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

        components::server::runtime_support* p = 
            reinterpret_cast<components::server::runtime_support*>(
                  get_runtime().get_runtime_support_lva());

        p->shutdown_all(shutdown_timeout); 
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

        p->call_shutdown_functions();
        p->shutdown(shutdown_timeout); 
    }
}


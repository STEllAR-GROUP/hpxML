//  Copyright (c) 2005-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/version.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/util/runtime_configuration.hpp>
#include <hpx/util/init_ini_data.hpp>
#include <hpx/util/itt_notify.hpp>

#include <boost/assign/std/vector.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/qi_alternative.hpp>
#include <boost/spirit/include/qi_sequence.hpp>

namespace hpx { namespace threads
{
    ///////////////////////////////////////////////////////////////////////////
    // global variable defining the stack size to use for all HPX-threads
    extern std::size_t default_stacksize;
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace util
{
    // pre-initialize entries with compile time based values
    void pre_initialize_ini(section& ini)
    {
        using namespace boost::assign;
        std::vector<std::string> lines;
        lines +=
            // create an empty application section
            "[application]",

            // create system and application instance specific entries
            "[system]",
            "pid = " + boost::lexical_cast<std::string>(getpid()),
            "prefix = " HPX_PREFIX,

            // create default installation location and logging settings
            "[hpx]",
            "location = ${HPX_LOCATION:$[system.prefix]}",
            "component_path = $[hpx.location]/lib/hpx",
            "ini_path = $[hpx.location]/share/hpx/ini",
#if HPX_USE_ITT == 1
            "use_itt_notify = ${HPX_USE_ITTNOTIFY:0}",
#endif
            "finalize_wait_time = ${HPX_FINALIZE_WAIT_TIME:-1.0}",
            "shutdown_timeout = ${HPX_SHUTDOWN_TIMEOUT:-1.0}",
            "default_stack_size = ${HPX_DEFAULT_STACK_SIZE:"
                BOOST_PP_STRINGIZE(HPX_DEFAULT_STACK_SIZE) "}",

            "[hpx.agas]",
            "address = ${HPX_AGAS_SERVER_ADDRESS:" HPX_INITIAL_IP_ADDRESS "}",
            "port = ${HPX_AGAS_SERVER_PORT:"
                BOOST_PP_STRINGIZE(HPX_INITIAL_IP_PORT) "}",
            "max_resolve_requests = ${HPX_AGAS_MAX_RESOLVE_REQUESTS:"
                BOOST_PP_STRINGIZE(HPX_INITIAL_AGAS_MAX_RESOLVE_REQUESTS) "}",
            "max_pending_refcnt_requests = "
                "${HPX_AGAS_MAX_PENDING_REFCNT_REQUESTS:1"
                BOOST_PP_STRINGIZE(HPX_INITIAL_AGAS_MAX_PENDING_REFCNT_REQUESTS)
                "}",
            "service_mode = hosted",
            "dedicated_server = 0",
            "gva_cache_size = ${HPX_AGAS_GVA_CACHE_SIZE:"
                BOOST_PP_STRINGIZE(HPX_INITIAL_AGAS_GVA_CACHE_SIZE) "}",
            "use_range_caching = ${HPX_AGAS_USE_RANGE_CACHING:1}",
            "use_caching = ${HPX_AGAS_USE_CACHING:1}",

            "[hpx.components]",
            "load_external = ${HPX_LOAD_EXTERNAL_COMPONENTS:1}",

            "[hpx.components.barrier]",
            "name = hpx",
            "path = $[hpx.location]/lib/hpx/" HPX_LIBRARY,
            "enabled = 1",

            "[hpx.components.raw_counter]",
            "name = hpx",
            "path = $[hpx.location]/lib/hpx/" HPX_LIBRARY,
            "enabled = 1",

            "[hpx.components.average_count_counter]",
            "name = hpx",
            "path = $[hpx.location]/lib/hpx/" HPX_LIBRARY,
            "enabled = 1",

            "[hpx.components.elapsed_time_counter]",
            "name = hpx",
            "path = $[hpx.location]/lib/hpx/" HPX_LIBRARY,
            "enabled = 1"
        ;
        // don't overload user overrides
        ini.parse("static defaults", lines);
    }

    void post_initialize_ini(section& ini, std::string const& hpx_ini_file = "",
        std::vector<std::string> const& cmdline_ini_defs = std::vector<std::string>())
    {
        // add explicit configuration information if its provided
        util::init_ini_data_base(ini, hpx_ini_file);

        // let the command line override the config file.
        if (!cmdline_ini_defs.empty())
            ini.parse("command line definitions", cmdline_ini_defs);
    }

    void runtime_configuration::load_components()
    {
        // try to build default ini structure from shared libraries in default
        // installation location, this allows to install simple components
        // without the need to install an ini file
        std::string component_path(
            get_entry("hpx.component_path", HPX_DEFAULT_COMPONENT_PATH));
        util::init_ini_data_default(component_path, *this);

        // merge all found ini files of all components
        util::merge_component_inis(*this);

        // read system and user ini files _again_, to allow the user to
        // overwrite the settings from the default component ini's.
        util::init_ini_data_base(*this, hpx_ini_file);

        // let the command line override the config file.
        if (!cmdline_ini_defs.empty())
            parse("command line definitions", cmdline_ini_defs);
    }

    ///////////////////////////////////////////////////////////////////////////
    runtime_configuration::runtime_configuration()
    {
        pre_initialize_ini(*this);
        post_initialize_ini(*this);

        // set global config options
#if HPX_USE_ITT == 1
        use_ittnotify_api = get_itt_notify_mode();
#endif
        threads::default_stacksize = get_default_stack_size();
    }

    ///////////////////////////////////////////////////////////////////////////
    runtime_configuration::runtime_configuration(
        std::vector<std::string> const& prefill,
        std::string const& hpx_ini_file_,
        std::vector<std::string> const& cmdline_ini_defs_)
        : hpx_ini_file(hpx_ini_file_)
        , cmdline_ini_defs(cmdline_ini_defs_)
    {
        pre_initialize_ini(*this);

        if (!prefill.empty())
            this->parse("static prefill defaults", prefill);

        post_initialize_ini(*this, hpx_ini_file_, cmdline_ini_defs_);

        // set global config options
#if HPX_USE_ITT == 1
        use_ittnotify_api = get_itt_notify_mode();
#endif
        threads::default_stacksize = get_default_stack_size();
    }

    // AGAS configuration information has to be stored in the global hpx.agas
    // configuration section:
    //
    //    [hpx.agas]
    //    address=<ip address>   # this defaults to HPX_INITIAL_IP_PORT
    //    port=<ip port>         # this defaults to HPX_INITIAL_IP_ADDRESS
    //
    // TODO: implement for AGAS v2
    naming::locality runtime_configuration::get_agas_locality() const
    {
        // load all components as described in the configuration information
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                std::string cfg_port(
                    sec->get_entry("port", HPX_INITIAL_IP_PORT));

                return naming::locality(
                    sec->get_entry("address", HPX_INITIAL_IP_ADDRESS),
                    boost::lexical_cast<boost::uint16_t>(cfg_port));
            }
        }
        return naming::locality(HPX_INITIAL_IP_ADDRESS, HPX_INITIAL_IP_PORT);
    }

    // HPX network address configuration information has to be stored in the
    // global hpx configuration section:
    //
    //    [hpx]
    //    address=<ip address>   # this defaults to HPX_INITIAL_IP_PORT
    //    port=<ip port>         # this defaults to HPX_INITIAL_IP_ADDRESS
    //
    naming::locality runtime_configuration::get_parcelport_address() const
    {
        // load all components as described in the configuration information
        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                std::string cfg_port(
                    sec->get_entry("port", HPX_INITIAL_IP_PORT));

                return naming::locality(
                    sec->get_entry("address", HPX_INITIAL_IP_ADDRESS),
                    boost::lexical_cast<boost::uint16_t>(cfg_port));
            }
        }
        return naming::locality(HPX_INITIAL_IP_ADDRESS, HPX_INITIAL_IP_PORT);
    }

    agas::service_mode runtime_configuration::get_agas_service_mode() const
    {
        // load all components as described in the configuration information
        if (has_section("hpx.agas"))
        {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec)
            {
                std::string const m = sec->get_entry("service_mode", "hosted");

                if (m == "hosted")
                    return agas::service_mode_hosted;
                else if (m == "bootstrap")
                    return agas::service_mode_bootstrap;
                else {
                    // REVIEW: exception type is overused
                    HPX_THROW_EXCEPTION(bad_parameter,
                        "runtime_configuration::get_agas_service_mode",
                        std::string("invalid AGAS router mode \"") + m + "\"");
                }
            }
        }
        return agas::service_mode_hosted;
    }

    std::size_t runtime_configuration::get_num_localities() const
    {
        // this function should only be called on the AGAS server
        BOOST_ASSERT(agas::service_mode_bootstrap == get_agas_service_mode());

        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("localities", 1));
            }
        }
        return 1;
    }

    std::size_t
    runtime_configuration::get_agas_promise_pool_size() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("promise_pool_size"
                                 , 4 * get_os_thread_count()));
            }
        }
        return 16;
    }

    std::size_t runtime_configuration::get_agas_gva_cache_size() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("gva_cache_size",
                        HPX_INITIAL_AGAS_GVA_CACHE_SIZE));
            }
        }
        return HPX_INITIAL_AGAS_GVA_CACHE_SIZE;
    }

    bool runtime_configuration::get_agas_caching_mode() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<int>(
                    sec->get_entry("use_caching", "1")) ? true : false;
            }
        }
        return false;
    }

    bool runtime_configuration::get_agas_range_caching_mode() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<int>(
                    sec->get_entry("use_range_caching", "1")) ? true : false;
            }
        }
        return false;
    }

    std::size_t runtime_configuration::get_agas_max_resolve_requests() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("max_resolve_requests",
                        HPX_INITIAL_AGAS_MAX_RESOLVE_REQUESTS));
            }
        }
        return HPX_INITIAL_AGAS_MAX_RESOLVE_REQUESTS;
    }

    std::size_t
    runtime_configuration::get_agas_max_pending_refcnt_requests() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("max_pending_refcnt_requests",
                        HPX_INITIAL_AGAS_MAX_PENDING_REFCNT_REQUESTS));
            }
        }
        return HPX_INITIAL_AGAS_MAX_PENDING_REFCNT_REQUESTS;
    }

    // Get whether the AGAS server is running as a dedicated runtime.
    // This decides whether the AGAS actions are executed with normal
    // priority (if dedicated) or with high priority (non-dedicated)
    bool runtime_configuration::get_agas_dedicated_server() const
    {
        if (has_section("hpx.agas")) {
            util::section const* sec = get_section("hpx.agas");
            if (NULL != sec) {
                return boost::lexical_cast<int>(
                    sec->get_entry("dedicated_server", 0)) ? true : false;
            }
        }
        return false;
    }

    bool runtime_configuration::get_itt_notify_mode() const
    {
#if HPX_USE_ITT == 1
        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                return boost::lexical_cast<int>(
                    sec->get_entry("use_itt_notify", "0")) ? true : false;
            }
        }
#endif
        return false;
    }

    std::size_t runtime_configuration::get_os_thread_count() const
    {
        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                return boost::lexical_cast<std::size_t>(
                    sec->get_entry("os_threads", 1));
            }
        }
        return 1;
    }

    std::string runtime_configuration::get_cmd_line() const
    {
        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                return sec->get_entry("cmd_line", "");
            }
        }
        return "";
    }

    // Will return the stack size to use for all HPX-threads.
    std::size_t runtime_configuration::get_default_stack_size() const
    {
        if (has_section("hpx")) {
            util::section const* sec = get_section("hpx");
            if (NULL != sec) {
                std::string entry = sec->get_entry("default_stack_size",
                    BOOST_PP_STRINGIZE(HPX_DEFAULT_STACK_SIZE));
                std::size_t val = HPX_DEFAULT_STACK_SIZE;

                namespace qi = boost::spirit::qi;
                qi::parse(entry.begin(), entry.end(),
                    "0x" >> qi::hex | "0" >> qi::oct | qi::int_, val);
                return val;
            }
        }
        return 1;
    }

    ///////////////////////////////////////////////////////////////////////////
    bool runtime_configuration::load_application_configuration(
        char const* filename, error_code& ec)
    {
        try {
            section appcfg(filename);
            section applroot;
            applroot.add_section("application", appcfg);
            this->section::merge(applroot);
        }
        catch (hpx::exception const& e) {
            // file doesn't exist or is ill-formed
            if (&ec == &throws)
                throw;
            ec = make_error_code(e.get_error(), e.what(), hpx::rethrow);
            return false;
        }
        return true;
    }
}}


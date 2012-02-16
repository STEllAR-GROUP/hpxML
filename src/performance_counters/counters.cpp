//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/include/performance_counters.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/runtime/agas/interface.hpp>
#include <hpx/runtime/components/stubs/runtime_support.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/format.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/lexical_cast.hpp>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_string.hpp>
#include <boost/spirit/include/qi_auxiliary.hpp>
#include <boost/spirit/include/qi_directive.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

///////////////////////////////////////////////////////////////////////////////
// Initialization support for the performance counter actions
HPX_REGISTER_ACTION_EX(
    hpx::performance_counters::server::base_performance_counter::get_counter_info_action,
    performance_counter_get_counter_info_action);
HPX_REGISTER_ACTION_EX(
    hpx::performance_counters::server::base_performance_counter::get_counter_value_action,
    performance_counter_get_counter_value_action);

HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::performance_counters::counter_info>::set_result_action,
    set_result_action_counter_info);
HPX_REGISTER_ACTION_EX(
    hpx::lcos::base_lco_with_value<hpx::performance_counters::counter_value>::set_result_action,
    set_result_action_counter_value);

HPX_DEFINE_GET_COMPONENT_TYPE(
    hpx::performance_counters::server::base_performance_counter);

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace performance_counters
{
    /// \brief Create a full name of a counter from the contents of the given
    ///        \a counter_path_elements instance.
    counter_status get_counter_name(counter_path_elements const& path,
        std::string& result, error_code& ec)
    {
        if (path.objectname_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_name",
                    "empty object name");
            return status_invalid_data;
        }

        result = "/";
        if (!path.objectname_.empty())
            result += path.objectname_;

        if (!path.parentinstancename_.empty() || !path.instancename_.empty())
        {
            result += "{";
            if (!path.parentinstancename_.empty())
            {
                result += path.parentinstancename_;
                if (-1 != path.parentinstanceindex_)
                {
                    result += "#";
                    result += boost::lexical_cast<std::string>(path.parentinstanceindex_);
                }
                if (!path.instancename_.empty())
                    result += "/";
            }
            if (!path.instancename_.empty()) {
                result += path.instancename_;
                if (-1 != path.instanceindex_)
                {
                    result += "#";
                    result += boost::lexical_cast<std::string>(path.instanceindex_);
                }
            }
            result += "}";
        }
        if (path.countername_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_name",
                    "empty counter name");
            return status_invalid_data;
        }

        result += "/";
        result += path.countername_;

        if (!path.parameters_.empty()) {
            result += "#";
            result += path.parameters_;
        }

        if (&ec != &throws)
            ec = make_success_code();
        return status_valid_data;
    }

    /// \brief Create a full name of a counter from the contents of the given
    ///        \a counter_path_elements instance.
    counter_status get_counter_type_name(counter_type_path_elements const& path,
        std::string& result, error_code& ec)
    {
        if (path.objectname_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_type_name",
                    "empty object name");
            return status_invalid_data;
        }

        result = "/";
        if (!path.objectname_.empty())
            result += path.objectname_;

        if (path.countername_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_type_name",
                    "empty counter name");
            return status_invalid_data;
        }

        result += "/";
        result += path.countername_;

        if (&ec != &throws)
            ec = make_success_code();
        return status_valid_data;
    }

    /// \brief Create a full name of a counter from the contents of the given
    ///        \a counter_path_elements instance.
    counter_status get_full_counter_type_name(
        counter_type_path_elements const& path, std::string& result,
        error_code& ec)
    {
        if (path.objectname_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_full_counter_type_name",
                    "empty object name");
            return status_invalid_data;
        }

        result = "/";
        if (!path.objectname_.empty())
            result += path.objectname_;

        if (path.countername_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_full_counter_type_name",
                    "empty counter name");
            return status_invalid_data;
        }

        result += "/";
        result += path.countername_;

        if (!path.parameters_.empty()) {
            result += "#";
            result += path.parameters_;
        }

        if (&ec != &throws)
            ec = make_success_code();
        return status_valid_data;
    }

    /// \brief Fill the given \a counter_type_path_elements instance from the
    ///        given full name of a counter
    ///
    ///    /objectname{...}/countername
    ///
    counter_status get_counter_path_elements(std::string const& name,
        counter_type_path_elements& path, error_code& ec)
    {
        if (name.empty() || name[0] != '/') {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                    "empty name parameter");
            return status_invalid_data;
        }

        std::string::size_type pstart = 1;
        if (name.find(counter_prefix) == 0)
            pstart = sizeof(counter_prefix);

        std::string::size_type p = name.find_first_of("{/", pstart + 1);
        if (p == std::string::npos) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                    "expected delimiter: '{' or '/'");
            return status_invalid_data;
        }

        // object name is the first part of the full name
        path.objectname_ = name.substr(pstart, p-pstart);
        if (path.objectname_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                    "empty object name");
            return status_invalid_data;
        }

        if (name[p] == '{') {
            std::string::size_type p1 = name.find_last_of("}");
            if (p1 == std::string::npos || p1 >= name.size()) {
                HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                        "mismatched parenthesis, expected: '}'");
                return status_invalid_data;
            }
            p = p1+1;
        }

        // counter name is always the last part of the full name
        std::string::size_type p1 = name.find_last_of("#");
        if (p1 != std::string::npos) {
            path.parameters_ = name.substr(p1+1);
            p1 = p1 - p - 1;
        }

        path.countername_ = name.substr(p+1, p1);
        if (path.countername_.empty()) {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                    "empty counter name");
            return status_invalid_data;
        }

        if (&ec != &throws)
            ec = make_success_code();
        return status_valid_data;
    }

    ///////////////////////////////////////////////////////////////////////////
    struct instance_name
    {
        instance_name() : index_(-1), basename_(false) {}

        std::string name_;
        boost::uint32_t index_;
        bool basename_;
    };

    struct instance_elements
    {
        instance_name parent_;
        instance_name child_;
    };

    struct path_elements
    {
        std::string object_;
        instance_elements instance_;
        std::string counter_;
        std::string parameters_;
    };
}}

BOOST_FUSION_ADAPT_STRUCT(
    hpx::performance_counters::instance_name,
    (std::string, name_)
    (boost::uint32_t, index_)
    (bool, basename_)
);

BOOST_FUSION_ADAPT_STRUCT(
    hpx::performance_counters::instance_elements,
    (hpx::performance_counters::instance_name, parent_)
    (hpx::performance_counters::instance_name, child_)
);

BOOST_FUSION_ADAPT_STRUCT(
    hpx::performance_counters::path_elements,
    (std::string, object_)
    (hpx::performance_counters::instance_elements, instance_)
    (std::string, counter_)
    (std::string, parameters_)
);

namespace hpx { namespace performance_counters
{
    ///
    ///    /objectname{parentinstancename#parentindex/instancename#instanceindex}/countername#parameters
    ///    /objectname{/basecounter}/countername,parameters
    ///
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct path_parser : qi::grammar<Iterator, path_elements()>
    {
        path_parser()
          : path_parser::base_type(start)
        {
          start = -qi::lit(counter_prefix)
                >> '/' >> +~qi::char_("{/") >> -instance
                >> '/' >>  +~qi::char_("#}") >> -('#' >> +qi::char_);
            instance = '{' >> parent >> -('/' >> child) >> '}';
            parent =
                    &qi::lit('/') >> qi::raw[start] >> qi::attr(-1) >> qi::attr(true)  // base counter
                |  +~qi::char_("#/}") >> -('#' >> qi::uint_) >> qi::attr(false) // counter instance name
                ;
            child = +~qi::char_("#}") >> -('#' >> qi::uint_) >> qi::attr(true);
        }

        qi::rule<Iterator, path_elements()> start;
        qi::rule<Iterator, instance_elements()> instance;
        qi::rule<Iterator, instance_name()> parent;
        qi::rule<Iterator, instance_name()> child;
    };

    /// \brief Fill the given \a counter_path_elements instance from the given
    ///        full name of a counter
    ///
    ///    /objectname{parentinstancename#parentindex/instancename#instanceindex}/countername
    ///
    counter_status get_counter_path_elements(std::string const& name,
        counter_path_elements& path, error_code& ec)
    {
        path_elements elements;
        path_parser<std::string::const_iterator> p;

        std::string::const_iterator begin = name.begin();
        if (!qi::parse(begin, name.end(), p, elements) || begin != name.end())
        {
            HPX_THROWS_IF(ec, bad_parameter, "get_counter_path_elements",
                    "invalid counter name format");
            return status_invalid_data;
        }

        path.objectname_ = elements.object_;
        path.countername_ = elements.counter_;
        path.parentinstancename_ = elements.instance_.parent_.name_;
        path.parentinstanceindex_ = elements.instance_.parent_.index_;
        path.instancename_ = elements.instance_.child_.name_;
        path.instanceindex_ = elements.instance_.child_.index_;
        path.parameters_ = elements.parameters_;
        path.parentinstance_is_basename_ = elements.instance_.parent_.basename_;

        if (&ec != &throws)
            ec = make_success_code();

        return status_valid_data;
    }

    /// \brief Return the counter type name from a given full instance name
    counter_status get_counter_type_name(std::string const& name,
        std::string& type_name, error_code& ec)
    {
        counter_type_path_elements p;

        counter_status status = get_counter_path_elements(name, p, ec);
        if (!status_is_valid(status)) return status;

        return get_counter_type_name(p, type_name, ec);
    }

    /// \brief Return the counter type name from a given full instance name
    counter_status get_counter_name(std::string const& name,
        std::string& countername, error_code& ec)
    {
        counter_path_elements p;

        counter_status status = get_counter_path_elements(name, p, ec);
        if (!status_is_valid(status)) return status;

        return get_counter_name(p, countername, ec);
    }

    /// \brief Complement the counter info if parent instance name is missing
    counter_status complement_counter_info(counter_info& info,
        counter_info const& type_info, error_code& ec)
    {
        info.type_ = type_info.type_;
        if (info.helptext_.empty())
            info.helptext_ = type_info.helptext_;
        return complement_counter_info(info, ec);
    }

    counter_status complement_counter_info(counter_info& info,
        error_code& ec)
    {
        counter_path_elements p;

        counter_status status = get_counter_path_elements(info.fullname_, p, ec);
        if (!status_is_valid(status)) return status;

        if (p.parentinstancename_.empty()) {
            p.parentinstancename_ =
                boost::str(boost::format("locality#%d") % get_locality_id());
        }

        return get_counter_name(p, info.fullname_, ec);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the name for a given counter type
    namespace strings
    {
        char const* const counter_type_names[] =
        {
            "counter_text",
            "counter_raw",
            "counter_average_base",
            "counter_average_count",
            "counter_statistics_max",
            "counter_statistics_min",
            "counter_average_timer",
            "counter_elapsed_time"
        };
    }

    char const* get_counter_type_name(counter_type type)
    {
        if (type < counter_text || type > counter_elapsed_time)
            return "unknown";
        return strings::counter_type_names[type];
    }

    ///////////////////////////////////////////////////////////////////////////
    counter_status add_counter_type(counter_info const& info,
        HPX_STD_FUNCTION<create_counter_func> const& create_counter,
        HPX_STD_FUNCTION<discover_counters_func> const& discover_counters,
        error_code& ec)
    {
        return get_runtime().get_counter_registry().add_counter_type(
            info, create_counter, discover_counters, ec);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Call the supplied function for each registered counter type
    counter_status discover_counter_types(
        HPX_STD_FUNCTION<discover_counter_func> const& discover_counter,
        error_code& ec)
    {
        return get_runtime().get_counter_registry().discover_counter_types(
            discover_counter, ec);
    }

    counter_status remove_counter_type(counter_info const& info, error_code& ec)
    {
        // the runtime might not be available any more
        runtime* rt = get_runtime_ptr();
        return rt ? rt->get_counter_registry().remove_counter_type(info, ec) :
            status_generic_error;
    }

    /// \brief Retrieve the counter type for the given counter name from the
    ///        (local) registry
    counter_status get_counter_type(std::string const& name,
        counter_info& info, error_code& ec)
    {
        // the runtime might not be available any more
        runtime* rt = get_runtime_ptr();
        return rt ?
            rt->get_counter_registry().get_counter_type(name, info, ec) :
            status_generic_error;
    }

    namespace detail
    {
        naming::gid_type create_raw_counter_value(
            counter_info const& info, boost::int64_t* countervalue,
            error_code& ec)
        {
            naming::gid_type gid;
            get_runtime().get_counter_registry().create_raw_counter_value(
                info, countervalue, gid, ec);
            return gid;
        }

        naming::gid_type create_raw_counter(counter_info const& info,
            HPX_STD_FUNCTION<boost::int64_t()> const& f, error_code& ec)
        {
            naming::gid_type gid;
            get_runtime().get_counter_registry().create_raw_counter(
                info, f, gid, ec);
            return gid;
        }

        // \brief Create a new performance counter instance based on given
        //        counter info
        naming::gid_type create_counter(counter_info const& info, error_code& ec)
        {
            naming::gid_type gid;
            get_runtime().get_counter_registry().create_counter(info, gid, ec);
            return gid;
        }

        // \brief Create a new statistics performance counter instance based on
        //        given base counter name and given base time interval
        //        (milliseconds).
        naming::gid_type create_statistics_counter(
            counter_info const& info, std::string const& base_counter_name,
            std::size_t base_time_interval, error_code& ec)
        {
            naming::gid_type gid;
            get_runtime().get_counter_registry().
                create_statistics_counter(info, base_counter_name,
                    base_time_interval, gid, ec);
            return gid;
        }
    }

    namespace detail
    {
        counter_status add_counter(naming::id_type const& id,
            counter_info const& info, error_code& ec)
        {
            return get_runtime().get_counter_registry().add_counter(id, info, ec);
        }

        counter_status remove_counter(counter_info const& info,
            naming::id_type const& id, error_code& ec)
        {
            return get_runtime().get_counter_registry().remove_counter(
                info, id, ec);
        }

        // create an arbitrary counter on this locality
        naming::gid_type create_counter_local(counter_info const& info)
        {
            // find create function for given counter
            error_code ec;

            HPX_STD_FUNCTION<create_counter_func> f;
            get_runtime().get_counter_registry().get_counter_create_function(
                info, f, ec);
            if (ec) {
                HPX_THROW_EXCEPTION(bad_parameter, "create_counter_local",
                    "no create function for performance counter found: " +
                        info.fullname_);
                return naming::invalid_gid;
            }

            // attempt to create the new counter instance
            naming::gid_type gid = f(info, ec);
            if (ec) {
                HPX_THROW_EXCEPTION(bad_parameter, "create_counter_local",
                    "couldn't create performance counter: " +
                        info.fullname_);
                return naming::invalid_gid;
            }

            return gid;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    naming::id_type get_counter(counter_info const& info, error_code& ec)
    {
        // complement counter info data
        counter_info complemented_info = info;
        complement_counter_info(complemented_info, ec);
        if (ec) return naming::invalid_id;

        ensure_counter_prefix(complemented_info.fullname_);      // pre-pend prefix, if necessary

        // ask AGAS for the id of the given counter
        naming::id_type id;
        bool result = agas::resolve_name(complemented_info.fullname_, id, ec);
        if (!result) {
            try {
                // figure out target locality
                counter_path_elements p;
                get_counter_path_elements(complemented_info.fullname_, p, ec);
                if (ec) return naming::invalid_id;

                // Take target locality from base counter if if this is an
                // aggregating counter (the instance name is a base counter).
                if (p.parentinstance_is_basename_)
                {
                    get_counter_path_elements(p.parentinstancename_, p, ec);
                    if (ec) return naming::invalid_id;
                }

                if (p.parentinstancename_ != "locality" ||
                    p.parentinstanceindex_ < 0 ||
                    p.parentinstanceindex_ >= static_cast<boost::int32_t>(get_num_localities()))
                {
                    HPX_THROWS_IF(ec, bad_parameter, "get_counter",
                        "attempt to create counter on non-existing locality");
                    return naming::invalid_id;
                }

                // use the runtime_support component of the target locality to
                // create the new performance counter
                using namespace components::stubs;
                naming::gid_type gid = runtime_support::create_performance_counter(
                    naming::get_id_from_locality_id(p.parentinstanceindex_),
                    complemented_info);

                id = naming::id_type(gid, naming::id_type::managed);
            }
            catch (hpx::exception const& e) {
                if (&ec == &throws)
                    throw;
                ec = make_error_code(e.get_error(), e.what());
                LPCS_(warning) << (boost::format("failed to create counter %s (%s)")
                    % complemented_info.fullname_ % e.what());
                return naming::invalid_id;
            }

            // register the canonical name with AGAS
            agas::register_name(complemented_info.fullname_, id, ec);
        }
        if (ec)
            return naming::invalid_id;

        return id;
    }

    naming::id_type get_counter(std::string name, error_code& ec)
    {
        ensure_counter_prefix(name);      // pre-pend prefix, if necessary

        // ask AGAS for the id of the given counter
        counter_info info;
        get_counter_type(name, info, ec);
        if (ec) return naming::invalid_id;

        info.fullname_ = name;            // set full counter name
        return get_counter(info, ec);
    }
}}


//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/config.hpp>
#include <hpx/exception.hpp>
#include <hpx/state.hpp>
#include <hpx/runtime.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/threads/threadmanager.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/util/stringstream.hpp>
#if HPX_STACKTRACES != 0
  #include <boost/backtrace.hpp>
#endif
#include <boost/format.hpp>

#include <stdexcept>

namespace hpx { namespace detail
{
    std::string backtrace()
    {
#if HPX_STACKTRACES != 0
        return boost::trace();
#else
        return "";
#endif
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Exception>
    HPX_EXPORT void rethrow_exception(Exception const& e, std::string const& func,
        std::string const& file, int line, std::string const& back_trace,
        boost::uint32_t node, boost::int64_t shepherd, std::size_t thread_id,
        std::string const& thread_name)
    {
        try {
            // create a boost::exception object encapsulating the Exception to 
            // be thrown and annotate it with all the local information we have
            throw boost::enable_current_exception(
                boost::enable_error_info(e) 
                    << throw_stacktrace(back_trace)
                    << throw_locality(node)
                    << throw_shepherd(shepherd)
                    << throw_thread_id(thread_id)
                    << throw_thread_name(thread_name)
                    << throw_function(func) 
                    << throw_file(file)
                    << throw_line(line));
        }
        catch (boost::exception const& e) {
            // log the exception information in any case
            LERR_(always) << "rethrow_exception: throwing exception: " 
                << diagnostic_information(e);
            throw;      // rethrow whatever has been caught
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    template HPX_EXPORT void rethrow_exception(hpx::exception const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);

    template HPX_EXPORT void rethrow_exception(boost::system::system_error const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);

    template HPX_EXPORT void rethrow_exception(std::exception const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::bad_exception const&,
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
#ifndef BOOST_NO_TYPEID
    template HPX_EXPORT void rethrow_exception(std::bad_typeid const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::bad_cast const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
#endif
    template HPX_EXPORT void rethrow_exception(std::bad_alloc const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::logic_error const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::runtime_error const&,
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::out_of_range const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);
    template HPX_EXPORT void rethrow_exception(std::invalid_argument const&, 
        std::string const&, std::string const&, int, std::string const&,
        boost::uint32_t, boost::int64_t, std::size_t, std::string const&);

    ///////////////////////////////////////////////////////////////////////////
    template <typename Exception>
    HPX_EXPORT void throw_exception(Exception const& e, std::string const& func, 
        std::string const& file, int line)
    {
        boost::uint32_t node = 0;
        boost::int64_t shepherd = -1;
        std::size_t thread_id = 0;
        std::string thread_name("");
        std::string back_trace(backtrace());

        // if this is not a HPX thread we do not need to query neither for 
        // the shepherd thread nor for the thread id
        threads::thread_self* self = threads::get_self_ptr();
        if (NULL != self)
        {
            if (threads::threadmanager_is(running))
            {
                node = applier::get_applier().get_prefix_id();
                shepherd = threads::threadmanager_base::get_thread_num();
            }

            thread_id = reinterpret_cast<std::size_t>(self->get_thread_id());
            thread_name = threads::get_thread_description(self->get_thread_id());
        } 

        rethrow_exception(e, func, file, line, back_trace, node, shepherd,
            thread_id, thread_name);
    }

    ///////////////////////////////////////////////////////////////////////////
    template HPX_EXPORT void throw_exception(hpx::exception const&, 
        std::string const&, std::string const&, int);

    template HPX_EXPORT void throw_exception(boost::system::system_error const&, 
        std::string const&, std::string const&, int);

    template HPX_EXPORT void throw_exception(std::exception const&, 
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::bad_exception const&,
        std::string const&, std::string const&, int);
#ifndef BOOST_NO_TYPEID
    template HPX_EXPORT void throw_exception(std::bad_typeid const&, 
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::bad_cast const&, 
        std::string const&, std::string const&, int);
#endif
    template HPX_EXPORT void throw_exception(std::bad_alloc const&, 
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::logic_error const&, 
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::runtime_error const&,
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::out_of_range const&, 
        std::string const&, std::string const&, int);
    template HPX_EXPORT void throw_exception(std::invalid_argument const&, 
        std::string const&, std::string const&, int);

    ///////////////////////////////////////////////////////////////////////////
    void assertion_failed(char const* expr, char const* function,
        char const* file, long line)
    {
        assertion_failed_msg(expr, expr, function, file, line);
    }

    void assertion_failed_msg(char const* msg, char const* expr,
        char const* function, char const* file, long line)
    {
        bool threw = false;
    
        std::string str("assertion '" + std::string(msg) + "' failed");
        if (expr != msg)
            str += " (" + std::string(expr) + ")";

        try {
            boost::filesystem::path p(hpx::util::create_path(file));
            hpx::detail::throw_exception(
                hpx::exception(hpx::assertion_failure, str), 
                function, p.string(), line);
        }
        catch (...) {
            threw = true;

            // If the runtime pointer is available, we can safely get the prefix
            // of this locality. If it's not available, then just terminate.
            runtime* rt = get_runtime_ptr();
            if (NULL != rt)  {
                rt->report_error(boost::current_exception());
            }
            else {
                std::cerr << "Runtime is not available, reporting error locally. "
                    << diagnostic_information(boost::current_exception())
                    << std::flush; 
            }
        }

        // If the exception wasn't thrown, then print out the assertion message,
        // so that the program doesn't abort without any diagnostics.
        // 
        // FIXME: why should the exception be not thrown above?
        if (!threw) {
            std::cerr << "Runtime is not available, reporting error locally\n"
                         "[what]: " << str << std::endl; 
        }
        std::abort();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Extract the diagnostic information embedded in the given exception and
    // return a string holding a formatted message.
    std::string diagnostic_information(boost::exception const& e)
    {
        util::osstream strm;
        strm << "\n";

        std::string const* back_trace = 
            boost::get_error_info<hpx::throw_stacktrace>(e);
        if (back_trace && !back_trace->empty()) {
            // FIXME: add indentation to stack frame information
            strm << "[stack_trace]: " << *back_trace << "\n";
        }

        // Try a cast to std::exception - this should handle boost.system
        // error codes in addition to the standard library exceptions.
        std::exception const* se = dynamic_cast<std::exception const*>(&e);
        if (se) 
            strm << "[what]: " << se->what() << "\n";

        boost::uint32_t const* locality = 
            boost::get_error_info<hpx::throw_locality>(e);
        if (locality && 0 != *locality) 
            strm << "[locality]: " << *locality << "\n";

        char const* const* func =
            boost::get_error_info<boost::throw_function>(e);
        if (func) {
            strm << "[function]: " << *func << "\n";
        }
        else {
            std::string const* s = 
                boost::get_error_info<hpx::throw_function>(e);
            if (s) 
                strm << "[function]: " << *s << "\n";
        }

        char const* const* file =
            boost::get_error_info<boost::throw_file>(e);
        if (file) {
            strm << "[file]: " << *file << "\n";
        }
        else {
            std::string const* s = 
                boost::get_error_info<hpx::throw_file>(e);
            if (s) 
                strm << "[file]: " << *s << "\n"; 
        }

        int const* line = 
            boost::get_error_info<boost::throw_line>(e);
        if (line) 
            strm << "[line]: " << *line << "\n";

        boost::int64_t const* shepherd = 
            boost::get_error_info<hpx::throw_shepherd>(e);
        if (shepherd && -1 != *shepherd) 
            strm << "[os-thread]: " << *shepherd << "\n";

        std::size_t const* thread_id = 
            boost::get_error_info<hpx::throw_thread_id>(e);
        if (thread_id && *thread_id) 
            strm << (boost::format("[thread_id]: %016x\n") % *thread_id);

        std::string const* thread_name = 
            boost::get_error_info<hpx::throw_thread_name>(e);
        if (thread_name && !thread_name->empty()) 
            strm << "[thread_name]: " << *thread_name << "\n";

        // add system information
        strm << "[version]: " << boost::str(
                boost::format("%d.%d.%d%s (AGAS: %x, build-type: %s), SVN: %s\n") % 
                    HPX_VERSION_MAJOR % HPX_VERSION_MINOR % 
                    HPX_VERSION_SUBMINOR % HPX_VERSION_TAG % 
                    HPX_AGAS_VERSION % HPX_BUILD_TYPE % HPX_SVN_REVISION); 
        strm << "[boost]: " << boost::str(boost::format("%d.%d.%d\n") % 
                (BOOST_VERSION / 100000) % (BOOST_VERSION / 100 % 1000) % 
                (BOOST_VERSION % 100));
        strm << "[platform]: " << BOOST_PLATFORM << "\n"; 
        strm << "[compiler]: " << BOOST_COMPILER << "\n"; 
        strm << "[stdlib]: " << BOOST_STDLIB << "\n"; 

        return util::osstream_get_string(strm);
    }
}}


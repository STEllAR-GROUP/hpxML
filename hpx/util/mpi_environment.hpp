//  Copyright (c) 2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_UTIL_MPI_ENV_HPP
#define HPX_UTIL_MPI_ENV_HPP

#include <hpx/config/defines.hpp>

#if defined(HPX_HAVE_PARCELPORT_MPI)
#include <hpx/hpx_fwd.hpp>
#include <cstdlib>

namespace hpx { namespace util
{
    struct command_line_handling;

    struct HPX_EXPORT mpi_environment
    {
        static std::size_t init(int *argc, char ***argv, command_line_handling& cfg,
            std::size_t node);
        static void finalize();

        static bool enabled();
        static bool multi_threaded();
        static bool has_called_init();

        static int rank();
        static int size();

        static std::string get_processor_name();

    private:
        static bool enabled_;
        static bool has_called_init_;
        static int provided_threading_flag_;
    };
}}

#else

namespace hpx { namespace util
{
    struct command_line_handling;

    struct HPX_EXPORT mpi_environment
    {
        static std::size_t init(int *argc, char ***argv, command_line_handling& cfg,
            std::size_t node);
    };
}}

#endif
#endif

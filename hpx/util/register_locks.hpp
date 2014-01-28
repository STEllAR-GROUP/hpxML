//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2014 Thomas Haller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_UTIL_REGISTER_LOCKS_JUN_26_2012_1029AM)
#define HPX_UTIL_REGISTER_LOCKS_JUN_26_2012_1029AM

#include <hpx/hpx_fwd.hpp>

namespace hpx { namespace util
{
    struct register_lock_data
    {
        register_lock_data() : ignore_(false) {}

        bool ignore_;       // will be ignored while checking for held locks
    };

    // Always provide function exports, which guarantees ABI compatibility of
    // Debug and Release builds.

#if HPX_HAVE_VERIFY_LOCKS || defined(HPX_EXPORTS)
    HPX_API_EXPORT bool register_lock(void const* lock,
        register_lock_data* data = 0);
    HPX_API_EXPORT bool unregister_lock(void const* lock);
    HPX_API_EXPORT void verify_no_locks();
    HPX_API_EXPORT void force_error_on_lock();
    HPX_API_EXPORT void enable_lock_detection();
    HPX_API_EXPORT void ignore_while_checking(void const* lock);
#else
    inline bool register_lock(void const*, util::register_lock_data* = 0)
    {
        return true;
    }
    inline bool unregister_lock(void const*)
    {
        return true;
    }
    inline void verify_no_locks()
    {
    }
    inline void force_error_on_lock()
    {
    }
    inline void enable_lock_detection()
    {
    }
    inline void ignore_while_checking(void const* /*lock*/)
    {
    }
#endif
}}

#endif


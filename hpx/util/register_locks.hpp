//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2014 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_UTIL_REGISTER_LOCKS_JUN_26_2012_1029AM)
#define HPX_UTIL_REGISTER_LOCKS_JUN_26_2012_1029AM

#include <hpx/hpx_fwd.hpp>

namespace hpx { namespace util
{
    struct register_lock_data {};

    // Always provide function exports, which guarantees ABI compatibility of
    // Debug and Release builds.

#if HPX_HAVE_VERIFY_LOCKS || defined(HPX_EXPORTS)
    HPX_API_EXPORT bool register_lock(void const* lock,
        register_lock_data* data = 0);
    HPX_API_EXPORT bool unregister_lock(void const* lock);
    HPX_API_EXPORT void verify_no_locks();
    HPX_API_EXPORT void force_error_on_lock();
    HPX_API_EXPORT void enable_lock_detection();
    HPX_API_EXPORT void ignore_lock(void const* lock);
    HPX_API_EXPORT void reset_ignored(void const* lock);
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
    inline void ignore_lock(void const* lock)
    {
    }
    inline void reset_ignored(void const* lock)
    {
    }
#endif

    struct ignore_while_checking
    {
        ignore_while_checking(void const* lock)
          : lock_(lock)
        {
            ignore_lock(lock);
        }

        ~ignore_while_checking()
        {
            reset_ignored(lock_);
        }

        void const* lock_;
    };
}}

#endif


//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2014 Thomas Haller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/util/register_locks.hpp>
#include <hpx/util/static.hpp>
#include <hpx/lcos/local/spinlock.hpp>

#include <boost/ptr_container/ptr_map.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace detail
{
    std::string backtrace();
    std::string backtrace_direct();
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace util
{
#if HPX_HAVE_VERIFY_LOCKS
    namespace detail
    {
        struct lock_data
        {
            lock_data()
              : thread_num_(get_worker_thread_num())
              , ignore_(false)
              , user_data_(0)
            {}

            lock_data(register_lock_data* data)
              : thread_num_(get_worker_thread_num())
              , ignore_(false)
              , user_data_(data)
            {}

            ~lock_data()
            {
                delete user_data_;
            }

            std::size_t thread_num_;
            bool ignore_;
            register_lock_data* user_data_;
        };

        struct register_locks
        {
            typedef lcos::local::spinlock mutex_type;
            typedef boost::ptr_map<void const*, lock_data> held_locks_map;

            struct registered_locks
            {
                mutable mutex_type mtx_;
                held_locks_map stored_locks_;
            };

            struct tls_tag {};

            static bool lock_detection_enabled_;

            static registered_locks& get_registered_locks()
            {
                util::static_<registered_locks, tls_tag> held_locks;
                return held_locks.get();
            }

            static mutex_type& get_mtx()
            {
                return get_registered_locks().mtx_;
            }

            static held_locks_map& get_lock_map()
            {
                return get_registered_locks().stored_locks_;
            }
        };

        bool register_locks::lock_detection_enabled_ = false;
    }

    ///////////////////////////////////////////////////////////////////////////
    void enable_lock_detection()
    {
        detail::register_locks::lock_detection_enabled_ = true;
    }

    ///////////////////////////////////////////////////////////////////////////
    bool register_lock(void const* lock, util::register_lock_data* data)
    {
        using detail::register_locks;

        if (register_locks::lock_detection_enabled_ && 0 != threads::get_self_ptr())
        {
            register_locks::mutex_type::scoped_lock l(register_locks::get_mtx());

            register_locks::held_locks_map& held_locks =
                register_locks::get_lock_map();

            register_locks::held_locks_map::iterator it = held_locks.find(lock);
            if (it != held_locks.end())
                return false;     // this lock is already registered

            std::pair<register_locks::held_locks_map::iterator, bool> p;
            if (!data) {
                p = held_locks.insert(lock, new detail::lock_data);
            }
            else {
                p = held_locks.insert(lock, new detail::lock_data(data));
            }
            return p.second;
        }
        return true;
    }

    // unregister the given lock from this HPX-thread
    bool unregister_lock(void const* lock)
    {
        using detail::register_locks;

        if (register_locks::lock_detection_enabled_ && 0 != threads::get_self_ptr())
        {
            register_locks::mutex_type::scoped_lock l(register_locks::get_mtx());

            register_locks::held_locks_map& held_locks =
                register_locks::get_lock_map();

            register_locks::held_locks_map::iterator it = held_locks.find(lock);
            if (it == held_locks.end())
                return false;     // this lock is not registered

            held_locks.erase(lock);
        }
        return true;
    }

    // verify that no locks are held by this HPX-thread
    namespace detail
    {
        inline bool some_locks_are_not_ignored(
            register_locks::held_locks_map const& held_locks)
        {
            typedef register_locks::held_locks_map::const_iterator iterator;

            std::size_t thread_num = get_worker_thread_num();

            iterator end = held_locks.end();
            for (iterator it = held_locks.begin(); it != end; ++it)
            {
                lock_data const& data = *(*it).second;
                if (data.thread_num_ == thread_num && !data.ignore_)
                    return true;
            }

            return false;
        }
    }

    void verify_no_locks()
    {
        using detail::register_locks;

        if (register_locks::lock_detection_enabled_ && 0 != threads::get_self_ptr())
        {
            register_locks::mutex_type::scoped_lock l(register_locks::get_mtx());

            register_locks::held_locks_map& held_locks =
                register_locks::get_lock_map();

            // we create a log message if there are still registered locks for
            // this OS-thread
            if (!held_locks.empty())
            {
                if (detail::some_locks_are_not_ignored(held_locks))
                {
                    std::string back_trace(hpx::detail::backtrace_direct());
                    if (back_trace.empty()) {
                        LERR_(debug)
                            << "suspending thread while at least one lock is "
                               "being held (stack backtrace was disabled at "
                               "compile time)";
                    }
                    else {
                        LERR_(debug)
                            << "suspending thread while at least one lock is "
                            << "being held, stack backtrace: "
                            << back_trace;
                    }
                }
            }
        }
    }

    void force_error_on_lock()
    {
        // For now just do the same as during suspension. We can't reliably
        // tell whether there are still locks held as those could have been
        // acquired in a different OS thread.
        verify_no_locks();

//        {
//            register_locks::held_locks_map const& held_locks =
//               register_locks::get_lock_map();
//
//            // we throw an error if there are still registered locks for
//            // this OS-thread
//            if (!held_locks.empty()) {
//                HPX_THROW_EXCEPTION(invalid_status, "force_error_on_lock",
//                    "At least one lock is held while thread is being terminated "
//                    "or interrupted.");
//            }
//        }
    }

    namespace detail
    {
        void set_ignore_status(void const* lock, bool status)
        {
            if (register_locks::lock_detection_enabled_ && 0 != threads::get_self_ptr())
            {
                register_locks::mutex_type::scoped_lock l(register_locks::get_mtx());

                register_locks::held_locks_map& held_locks =
                    register_locks::get_lock_map();

                register_locks::held_locks_map::iterator it = held_locks.find(lock);
                if (it == held_locks.end())
                {
                    HPX_THROW_EXCEPTION(invalid_status, "set_ignore_status",
                        "The given lock has not been registered.");
                    return;
                }

                it->second->ignore_ = status;
            }
        }
    }

    void ignore_lock(void const* lock)
    {
        detail::set_ignore_status(lock, true);
    }

    void reset_ignored(void const* lock)
    {
        detail::set_ignore_status(lock, false);
    }

#else

    bool register_lock(void const*, util::register_lock_data*)
    {
        return true;
    }

    bool unregister_lock(void const*)
    {
        return true;
    }

    void verify_no_locks()
    {
    }

    void force_error_on_lock()
    {
    }

    void ignore_lock(void const* lock)
    {
    }

    void reset_ignored(void const* lock)
    {
    }

#endif
}}



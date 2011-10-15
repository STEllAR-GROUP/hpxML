//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Part of this code has been adopted from code published under the BSL by:
//
//  (C) Copyright 2006-7 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_RECURSIVE_MUTEX_AUG_03_2009_0459PM)
#define HPX_LCOS_RECURSIVE_MUTEX_AUG_03_2009_0459PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/local_mutex.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos
{
    /// An exclusive-ownership recursive mutex which implements Boost.Thread's
    /// TimedLockable concept.
    struct HPX_EXPORT local_recursive_mutex : boost::noncopyable
    {
      private:
        boost::uint64_t recursion_count;
        boost::atomic<threads::thread_id_type> locking_thread_id;
        local_mutex mutex;

      public:
        local_recursive_mutex(char const* const description = "")
          : recursion_count(0), locking_thread_id(0), mutex(description)
        {}

        /// Attempts to acquire ownership of the \a local_recursive_mutex.
        /// Never blocks.
        ///
        /// \returns \a true if ownership was acquired; otherwise, \a false.
        ///
        /// \throws Never throws.
        bool try_lock();

        /// Acquires ownership of the \a local_recursive_mutex. Suspends the
        /// current pxthread if ownership cannot be obtained immediately.
        ///
        /// \throws Throws \a hpx#bad_parameter if an error occurs while
        ///         suspending. Throws \a hpx#yield_aborted if the mutex is
        ///         destroyed while suspended. Throws \a hpx#null_thread_id if
        ///         called outside of a pxthread.
        void lock();

        /// Attempts to acquire ownership of the \a local_recursive_mutex.
        /// Suspends the current pxthread until \a wait_until if ownership
        /// cannot be obtained immediately.
        ///
        /// \returns \a true if ownership was acquired; otherwise, \a false.
        ///
        /// \throws Throws \a hpx#bad_parameter if an error occurs while
        ///         suspending. Throws \a hpx#yield_aborted if the mutex is
        ///         destroyed while suspended. Throws \a hpx#null_thread_id if
        ///         called outside of a pxthread.
        bool timed_lock(::boost::system_time const& wait_until);

        /// Attempts to acquire ownership of the \a local_recursive_mutex.
        /// Suspends the current pxthread until \a timeout if ownership cannot
        /// be obtained immediately.
        ///
        /// \returns \a true if ownership was acquired; otherwise, \a false.
        ///
        /// \throws Throws \a hpx#bad_parameter if an error occurs while
        ///         suspending. Throws \a hpx#yield_aborted if the mutex is
        ///         destroyed while suspended. Throws \a hpx#null_thread_id if
        ///         called outside of a pxthread.
        template<typename Duration>
        bool timed_lock(Duration const& timeout)
        {
            return timed_lock(boost::get_system_time() + timeout);
        }

        bool timed_lock(boost::xtime const& timeout)
        {
            return timed_lock(boost::posix_time::ptime(timeout));
        }

        /// Release ownership of the \a local_recursive_mutex.
        ///
        /// \throws Throws \a hpx#bad_parameter if an error occurs while
        ///         releasing the mutex. Throws \a hpx#null_thread_id if called
        ///         outside of a pxthread.
        void unlock()
        {
            if (!--recursion_count)
            {
                locking_thread_id.exchange((threads::thread_id_type)0);
                mutex.unlock();
            }
        }

    private:
        bool try_recursive_lock(threads::thread_id_type current_thread_id)
        {
            if(locking_thread_id.load(boost::memory_order_acquire) ==
                current_thread_id)
            {
                ++recursion_count;
                return true;
            }
            return false;
        }

        bool try_basic_lock(threads::thread_id_type current_thread_id)
        {
            if (mutex.try_lock())
            {
                locking_thread_id.exchange(current_thread_id);
                recursion_count = 1;
                return true;
            }
            return false;
        }

        bool try_timed_lock(threads::thread_id_type current_thread_id,
            ::boost::system_time const& target)
        {
            if (mutex.timed_lock(target))
            {
                locking_thread_id.exchange(current_thread_id);
                recursion_count = 1;
                return true;
            }
            return false;
        }
    };
}}

#endif


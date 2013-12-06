//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_EVENT_SEP_29_2012_1918AM)
#define HPX_LCOS_EVENT_SEP_29_2012_1918AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/local/condition_variable.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/util/assert.hpp>

#include <boost/atomic.hpp>
#include <boost/cstdint.hpp>

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

////////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos { namespace local
{
    /// Event semaphores can be used for synchronizing multiple threads that
    /// need to wait for an event to occur. When the event occurs, all threads
    /// waiting for the event are woken up.
    namespace detail
    {
        template <typename Mutex = lcos::local::spinlock>
        class event
        {
        private:
            typedef Mutex mutex_type;

        public:
            /// \brief Construct a new event semaphore
            event()
              : event_(false)
            {}

            /// \brief Check if the event has occurred.
            bool occurred()
            {
                return event_.load(boost::memory_order_acquire);
            }

            /// \brief Wait for the event to occur.
            void wait()
            {
                if (event_.load(boost::memory_order_acquire))
                    return;

                typename mutex_type::scoped_lock l(mtx_);
                wait_locked(l);
            }

            /// \brief Release all threads waiting on this semaphore.
            void set()
            {
                event_.store(true, boost::memory_order_release);

                typename mutex_type::scoped_lock l(mtx_);
                set_locked(l);
            }

            /// \brief Reset the event
            void reset()
            {
                event_.store(false, boost::memory_order_release);
            }

        private:
            void wait_locked(typename mutex_type::scoped_lock& l)
            {
                HPX_ASSERT(l.owns_lock());

                while (!event_.load(boost::memory_order_acquire))
                {
                    cond_.wait(l, "event::wait_locked");
                }
            }

            void set_locked(typename mutex_type::scoped_lock& l)
            {
                HPX_ASSERT(l.owns_lock());

                // release the threads
                cond_.notify_all(l);
            }

            mutex_type mtx_;      ///< This mutex protects the queue.
            local::detail::condition_variable cond_;

            boost::atomic<bool> event_;
        };
    }

    typedef detail::event<> event;
}}}

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif


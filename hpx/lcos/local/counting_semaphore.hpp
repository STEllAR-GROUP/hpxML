//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_COUNTING_SEMAPHORE_OCT_16_2008_1007AM)
#define HPX_LCOS_COUNTING_SEMAPHORE_OCT_16_2008_1007AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/local/condition_variable.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/util/assert.hpp>

#include <boost/cstdint.hpp>

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

////////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos { namespace local
{
    /// A semaphore is a protected variable (an entity storing a value) or
    /// abstract data type (an entity grouping several variables that may or
    /// may not be numerical) which constitutes the classic method for
    /// restricting access to shared resources, such as shared memory, in a
    /// multiprogramming environment. Semaphores exist in many variants, though
    /// usually the term refers to a counting semaphore, since a binary
    /// semaphore is better known as a mutex. A counting semaphore is a counter
    /// for a set of available resources, rather than a locked/unlocked flag of
    /// a single resource. It was invented by Edsger Dijkstra. Semaphores are
    /// the classic solution to preventing race conditions in the dining
    /// philosophers problem, although they do not prevent resource deadlocks.
    ///
    /// Counting semaphores can be used for synchronizing multiple threads as
    /// well: one thread waiting for several other threads to touch (signal)
    /// the semaphore, or several threads waiting for one other thread to touch
    /// this semaphore.
    namespace detail
    {
        template <typename Mutex = lcos::local::spinlock>
        class HPX_EXPORT counting_semaphore
        {
        private:
            typedef Mutex mutex_type;

        public:
            /// \brief Construct a new counting semaphore
            ///
            /// \param value    [in] The initial value of the internal semaphore
            ///                 lock count. Normally this value should be zero
            ///                 (which is the default), values greater than zero
            ///                 are equivalent to the same number of signals pre-
            ///                 set, and negative values are equivalent to the
            ///                 same number of waits pre-set.
            counting_semaphore(boost::int64_t value = 0)
              : value_(value) {}

            /// \brief Wait for the semaphore to be signaled
            ///
            /// \param count    [in] The value by which the internal lock count will
            ///                 be decremented. At the same time this is the minimum
            ///                 value of the lock count at which the thread is not
            ///                 yielded.
            void wait(boost::int64_t count = 1)
            {
                typename mutex_type::scoped_lock l(mtx_);
                wait_locked(count, l);
            }

            /// \brief Try to wait for the semaphore to be signaled
            ///
            /// \param count    [in] The value by which the internal lock count will
            ///                 be decremented. At the same time this is the minimum
            ///                 value of the lock count at which the thread is not
            ///                 yielded.
            ///
            /// \returns        The function returns true if the calling thread was
            ///                 able to acquire the requested amount of credits.
            ///                 The function returns false if not sufficient credits
            ///                 are available at this point in time.
            bool try_wait(boost::int64_t count = 1)
            {
                typename mutex_type::scoped_lock l(mtx_);
                if (!(value_ < count)) {
                    // enter wait_locked only if there are sufficient credits
                    // available
                    wait_locked(count, l);
                    return true;
                }
                return false;
            }

            /// \brief Signal the semaphore
            ///
            ///
            void signal(boost::int64_t count = 1)
            {
                typename mutex_type::scoped_lock l(mtx_);
                signal_locked(count, l);
            }

            boost::int64_t signal_all()
            {
                typename mutex_type::scoped_lock l(mtx_);
                boost::int64_t count = static_cast<boost::int64_t>(cond_.size(l));
                signal_locked(count, l);
                return count;
            }

            template <typename Lock>
            void wait_locked(boost::int64_t count, Lock& l)
            {
                while (value_ < count)
                {
                    cond_.wait(l, "counting_semaphore::wait_locked");
                }
                value_ -= count;
            }

        private:
            template <typename Lock>
            void signal_locked(boost::int64_t count, Lock& l)
            {
                value_ += count;
                if (value_ >= 0)
                {
                    // release all threads, they will figure out between themselves
                    // which one gets released from wait above
                    cond_.notify_all(l);
                }
            }

        private:
            mutex_type mtx_;
            boost::int64_t value_;
            local::detail::condition_variable cond_;
        };
    }

    typedef detail::counting_semaphore<> counting_semaphore;
}}}

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif


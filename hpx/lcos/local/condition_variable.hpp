//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2013 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_LCOS_LOCAL_CONDITION_VARIABLE_HPP
#define HPX_LCOS_LOCAL_CONDITION_VARIABLE_HPP

#include <hpx/config.hpp>
#include <hpx/error_code.hpp>
#include <hpx/lcos/local/detail/condition_variable.hpp>
#include <hpx/lcos/local/mutex.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/runtime/threads/thread_enums.hpp>
#include <hpx/util/assert_owns_lock.hpp>
#include <hpx/util/date_time_chrono.hpp>
#include <hpx/util/register_locks.hpp>
#include <hpx/util/unlock_guard.hpp>

#include <mutex>
#include <utility>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos { namespace local
{
    enum class cv_status
    {
        no_timeout, timeout, error
    };

    class condition_variable
    {
    private:
        typedef lcos::local::spinlock mutex_type;

    public:
        void notify_one(error_code& ec = throws)
        {
            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            cond_.notify_one(std::move(l), ec);
        }

        void notify_all(error_code& ec = throws)
        {
            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            cond_.notify_all(std::move(l), ec);
        }

        void wait(std::unique_lock<mutex>& lock, error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            util::unlock_guard<std::unique_lock<mutex> > unlock(lock);

            cond_.wait(std::move(l), ec);
        }

        template <class Predicate>
        void wait(std::unique_lock<mutex>& lock, Predicate pred,
            error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            while (!pred())
            {
                wait(lock);
            }
        }

        cv_status wait_until(std::unique_lock<mutex>& lock,
            util::steady_time_point const& abs_time,
            error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            util::unlock_guard<std::unique_lock<mutex> > unlock(lock);

            threads::thread_state_ex_enum const reason =
                cond_.wait_until(std::move(l), abs_time, ec);

            if (ec) return cv_status::error;

            // if the timer has hit, the waiting period timed out
            return (reason == threads::wait_timeout) ? //-V110
                cv_status::timeout : cv_status::no_timeout;
        }

        template <typename Predicate>
        bool wait_until(std::unique_lock<mutex>& lock,
            util::steady_time_point const& abs_time, Predicate pred,
            error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            while (!pred())
            {
                if (wait_until(lock, abs_time, ec) == cv_status::timeout)
                    return pred();
            }
            return true;
        }

        cv_status wait_for(std::unique_lock<mutex>& lock,
            util::steady_duration const& rel_time,
            error_code& ec = throws)
        {
            return wait_until(lock, rel_time.from_now(), ec);
        }

        template <typename Predicate>
        bool wait_for(std::unique_lock<mutex>& lock,
            util::steady_duration const& rel_time, Predicate pred,
            error_code& ec = throws)
        {
            return wait_until(lock, rel_time.from_now(), std::move(pred), ec);
        }

    private:
        mutable mutex_type mtx_;
        detail::condition_variable cond_;
    };

    class condition_variable_any
    {
    private:
        typedef lcos::local::spinlock mutex_type;

    public:
        void notify_one(error_code& ec = throws)
        {
            std::unique_lock<mutex_type> l(mtx_);
            cond_.notify_one(std::move(l), ec);
        }

        void notify_all(error_code& ec = throws)
        {
            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            cond_.notify_all(std::move(l), ec);
        }

        template <class Lock>
        void wait(Lock& lock, error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            util::unlock_guard<Lock> unlock(lock);

            cond_.wait(std::move(l), ec);
        }

        template <class Lock, class Predicate>
        void wait(Lock& lock, Predicate pred, error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            while (!pred())
            {
                wait(lock);
            }
        }

        template <typename Lock>
        cv_status
        wait_until(Lock& lock, util::steady_time_point const& abs_time,
            error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            util::ignore_all_while_checking ignore_lock;
            std::unique_lock<mutex_type> l(mtx_);
            util::unlock_guard<Lock> unlock(lock);

            threads::thread_state_ex_enum const reason =
                cond_.wait_until(std::move(l), abs_time, ec);

            if (ec) return cv_status::error;

            // if the timer has hit, the waiting period timed out
            return (reason == threads::wait_timeout) ? //-V110
                cv_status::timeout : cv_status::no_timeout;
        }

        template <typename Lock, typename Predicate>
        bool wait_until(Lock& lock, util::steady_time_point const& abs_time,
            Predicate pred, error_code& ec = throws)
        {
            HPX_ASSERT_OWNS_LOCK(lock);

            while (!pred())
            {
                if (wait_until(lock, abs_time, ec) == cv_status::timeout)
                    return pred();
            }
            return true;
        }

        template <typename Lock>
        cv_status
        wait_for(Lock& lock, util::steady_duration const& rel_time,
            error_code& ec = throws)
        {
            return wait_until(lock, rel_time.from_now(), ec);
        }

        template <typename Lock, typename Predicate>
        bool wait_for(Lock& lock, util::steady_duration const& rel_time,
            Predicate pred, error_code& ec = throws)
        {
            return wait_until(lock, rel_time.from_now(), std::move(pred), ec);
        }

    private:
        mutable mutex_type mtx_;
        detail::condition_variable cond_;
    };
}}}

#endif /*HPX_LCOS_LOCAL_CONDITION_VARIABLE_HPP*/

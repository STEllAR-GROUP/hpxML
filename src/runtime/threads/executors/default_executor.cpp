//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/threads/executors/default_executor.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>

namespace hpx { namespace threads { namespace executors { namespace detail
{
    // Schedule the specified function for execution in this executor.
    // Depending on the subclass implementation, this may block in some
    // situations.
    void default_executor::add(HPX_STD_FUNCTION<void()> f,
        char const* description)
    {
        register_thread_nullary(boost::move(f), description);
    }

    // Like add(), except that if the attempt to add the function would
    // cause the caller to block in add, try_add would instead do
    // nothing and return false.
    bool default_executor::try_add(HPX_STD_FUNCTION<void()> f,
        char const* description)
    {
        register_thread_nullary(boost::move(f), description);
        return true;      // this function will never block
    }

    // Schedule given function for execution in this executor no sooner
    // than time abs_time. This call never blocks, and may violate
    // bounds on the executor's queue size.
    void default_executor::add_at(
        boost::posix_time::ptime const& abs_time,
        HPX_STD_FUNCTION<void()> f, char const* description)
    {
        // create new thread
        thread_id_type id = register_thread_nullary(
            boost::move(f), description, suspended);
        BOOST_ASSERT(invalid_thread_id != id);    // would throw otherwise

        // now schedule new thread for execution
        set_thread_state(id, abs_time);
    }

    // Schedule given function for execution in this executor no sooner
    // than time rel_time from now. This call never blocks, and may
    // violate bounds on the executor's queue size.
    void default_executor::add_after(
        boost::posix_time::time_duration const& rel_time,
        HPX_STD_FUNCTION<void()> f, char const* description)
    {
        // create new thread
        thread_id_type id = register_thread_nullary(
            boost::move(f), description, suspended);
        BOOST_ASSERT(invalid_thread_id != id);    // would throw otherwise

        // now schedule new thread for execution
        set_thread_state(id, rel_time);
    }

    // Return an estimate of the number of waiting tasks.
    std::size_t default_executor::num_pending_tasks() const
    {
        return get_thread_count() - get_thread_count(terminated);
    }
}}}}

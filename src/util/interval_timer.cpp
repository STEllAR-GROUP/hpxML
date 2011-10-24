//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/util/interval_timer.hpp>
#include <hpx/util/unlock_lock.hpp>

#include <boost/bind.hpp>

namespace hpx { namespace util
{
    ///////////////////////////////////////////////////////////////////////////
    interval_timer::interval_timer()
      : microsecs_(0), id_(0)
    {}

    interval_timer::interval_timer(HPX_STD_FUNCTION<void()> const& f,
            std::size_t microsecs, std::string const& description,
            bool pre_shutdown)
      : f_(f), microsecs_(microsecs), id_(0), description_(description),
        pre_shutdown_(pre_shutdown)
    {}

    void interval_timer::start()
    {
        if (pre_shutdown_)
            register_pre_shutdown_function(boost::bind(&interval_timer::stop, this));
        else
            register_shutdown_function(boost::bind(&interval_timer::stop, this));

        evaluate(threads::wait_signaled);
    }

    void interval_timer::stop()
    {
        mutex_type::scoped_lock l(mtx_);
        if (id_) {
            error_code ec;       // avoid throwing on error
            threads::set_thread_state(id_, threads::pending,
                threads::wait_abort, threads::thread_priority_critical, ec);
            id_ = 0;
        }
    }

    interval_timer::~interval_timer()
    {
        stop();
    }

    threads::thread_state_enum interval_timer::evaluate(
        threads::thread_state_ex_enum statex)
    {
        if (statex == threads::wait_abort || 0 == microsecs_)
            return threads::terminated;        // object has been finalized, exit

        mutex_type::scoped_lock l(mtx_);
        id_ = 0;

        {
            util::unlock_the_lock<mutex_type::scoped_lock> ul(l);
            f_();                     // invoke the supplied function
        }

        schedule_thread();            // wait and repeat
        return threads::terminated;   // do not re-schedule this thread
    }

    // schedule a high priority task after a given time interval
    void interval_timer::schedule_thread()
    {
        using namespace hpx::threads;

        // create a new suspended thread
        id_ = hpx::applier::register_thread_plain(
            boost::bind(&interval_timer::evaluate, this, _1),
            description_.c_str(), threads::suspended);

        // schedule this thread to be run after the given amount of seconds
        threads::set_thread_state(id_,
            boost::posix_time::microseconds(microsecs_),
            threads::pending, threads::wait_signaled,
            threads::thread_priority_critical);
    }
}}


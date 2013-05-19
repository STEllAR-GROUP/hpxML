//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_THREADS_EXECUTORS_DEFAULT_EXECUTOR_JAN_11_2013_0700PM)
#define HPX_RUNTIME_THREADS_EXECUTORS_DEFAULT_EXECUTOR_JAN_11_2013_0700PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/threads/thread_executor.hpp>

#include <hpx/config/warnings_prefix.hpp>

namespace hpx { namespace threads { namespace executors
{
    namespace detail
    {
        class HPX_EXPORT default_executor 
          : public threads::detail::scheduled_executor_base
        {
        public:
            // Schedule the specified function for execution in this executor.
            // Depending on the subclass implementation, this may block in some
            // situations.
            void add(BOOST_RV_REF(HPX_STD_FUNCTION<void()>) f, char const* description,
                threads::thread_state_enum initial_state, bool run_now,
                error_code& ec);

            // Schedule given function for execution in this executor no sooner
            // than time abs_time. This call never blocks, and may violate
            // bounds on the executor's queue size.
            void add_at(boost::posix_time::ptime const& abs_time,
                BOOST_RV_REF(HPX_STD_FUNCTION<void()>) f, char const* description,
                error_code& ec);

            // Schedule given function for execution in this executor no sooner
            // than time rel_time from now. This call never blocks, and may
            // violate bounds on the executor's queue size.
            void add_after(boost::posix_time::time_duration const& rel_time,
                BOOST_RV_REF(HPX_STD_FUNCTION<void()>) f, char const* description,
                error_code& ec);

            // Return an estimate of the number of waiting tasks.
            std::size_t num_pending_closures(error_code& ec) const;
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    struct default_executor : public scheduled_executor
    {
        default_executor()
          : scheduled_executor(new detail::default_executor())
        {}
    };
}}}

#include <hpx/config/warnings_suffix.hpp>

#endif


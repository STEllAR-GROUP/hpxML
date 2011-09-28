//  Copyright (c) 2007-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_THROTTLE_SERVER_AUG_09_2011_0702PM)
#define HPX_THROTTLE_SERVER_AUG_09_2011_0702PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/promise.hpp>
#include <hpx/lcos/mutex.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/server/simple_component_base.hpp>

#include <boost/dynamic_bitset.hpp>

namespace throttle { namespace server
{
    ///////////////////////////////////////////////////////////////////////////
    class HPX_COMPONENT_EXPORT throttle
      : public hpx::components::simple_component_base<throttle>
    {
    private:
        typedef hpx::components::simple_component_base<throttle> base_type;
        typedef hpx::lcos::mutex mutex_type;

    public:
        throttle();
        ~throttle();

        // components must contain a typedef for wrapping_type defining the
        // component type used to encapsulate instances of this component
        typedef throttle wrapping_type;

        ///////////////////////////////////////////////////////////////////////
        // parcel action code: the action to be performed on the destination 
        // object (the accumulator)
        enum actions
        {
            throttle_suspend = 0,
            throttle_resume = 1,
            throttle_is_suspended = 2
        };

        void suspend(std::size_t shepherd);
        void resume(std::size_t shepherd);
        bool is_suspended(std::size_t shepherd) const;

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into an action
        // type, allowing to generate all required boilerplate code for threads,
        // serialization, etc.
        typedef hpx::actions::action1<
            throttle, throttle_suspend, std::size_t,
            &throttle::suspend, hpx::threads::thread_priority_critical
        > suspend_action;

        typedef hpx::actions::action1<
            throttle, throttle_resume, std::size_t,
            &throttle::resume, hpx::threads::thread_priority_critical
        > resume_action;

        typedef hpx::actions::result_action1<
            throttle const, bool, throttle_is_suspended, std::size_t,
            &throttle::is_suspended, hpx::threads::thread_priority_critical
        > is_suspended_action;

    private:
        // this function is periodically scheduled as a worker thread with the 
        // aim of blocking the execution of its shepherd thread
        void throttle_controller(std::size_t shepherd);

        // schedule a high priority task on the given shepherd thread
        void register_thread(std::size_t shepherd);
        void register_suspend_thread(std::size_t shepherd);

        // this is a bit mask where any set bit means the corresponding 
        // shepherd is to be blocked
        boost::dynamic_bitset<> blocked_os_threads_;
        mutable mutex_type mtx_;
    };
}}

#endif

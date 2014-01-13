//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_APPLIER_APPLY_HELPER_JUN_25_2008_0917PM)
#define HPX_APPLIER_APPLY_HELPER_JUN_25_2008_0917PM

#include <boost/mpl/bool.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/runtime/naming/address.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>

namespace hpx { namespace applier { namespace detail
{
    ///////////////////////////////////////////////////////////////////////
    template <typename Action>
    inline threads::thread_priority
        fix_priority(threads::thread_priority priority)
    {
        return hpx::actions::detail::thread_priority<
            static_cast<threads::thread_priority>(traits::action_priority<Action>::value)
        >::call(priority);
    }

    ///////////////////////////////////////////////////////////////////////
    template <typename Action,
        typename DirectExecute = typename Action::direct_execution>
    struct apply_helper;

    template <typename Action>
    struct apply_helper<Action, boost::mpl::false_>
    {
        template <typename Arguments>
        static void
        call (naming::id_type const& target, naming::address::address_type lva,
            threads::thread_priority priority, Arguments && args)
        {
            hpx::applier::register_work_plain(
                std::move(Action::construct_thread_function(
                    lva, std::forward<Arguments>(args))),
                target, actions::detail::get_action_name<Action>(), lva,
                threads::pending, fix_priority<Action>(priority), std::size_t(-1),
                static_cast<threads::thread_stacksize>(
                    traits::action_stacksize<Action>::value));
        }

        template <typename Arguments>
        static void
        call (actions::continuation_type& c, naming::id_type const& target,
            naming::address::address_type lva, threads::thread_priority priority,
            Arguments && args)
        {
            hpx::applier::register_work_plain(
                std::move(Action::construct_thread_function(c, lva,
                    std::forward<Arguments>(args))),
                target, actions::detail::get_action_name<Action>(), lva,
                threads::pending, fix_priority<Action>(priority), std::size_t(-1),
                static_cast<threads::thread_stacksize>(
                    traits::action_stacksize<Action>::value));
        }
    };

    template <typename Action>
    struct apply_helper<Action, boost::mpl::true_>
    {
        // If local and to be directly executed, just call the function
        template <typename Arguments>
        static void
        call (naming::id_type const& target, naming::address::address_type lva,
            threads::thread_priority, Arguments && args)
        {
            Action::execute_function(lva, std::forward<Arguments>(args));
        }

        template <typename Arguments>
        static void
        call (actions::continuation_type& c, naming::id_type const& target,
            naming::address::address_type lva, threads::thread_priority,
            Arguments && args)
        {
            try {
                c->trigger(std::move(Action::execute_function(
                    lva, std::forward<Arguments>(args))));
            }
            catch (hpx::exception const& /*e*/) {
                // make sure hpx::exceptions are propagated back to the client
                c->trigger_error(boost::current_exception());
            }
        }
    };
}}}

#endif

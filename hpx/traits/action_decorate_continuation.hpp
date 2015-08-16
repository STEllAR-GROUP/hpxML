//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_TRAITS_ACTION_DECORATE_CONTINUATION_MAR_30_2014_0725PM)
#define HPX_TRAITS_ACTION_DECORATE_CONTINUATION_MAR_30_2014_0725PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/always_void.hpp>

namespace hpx { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    // Customization point for action capabilities
    template <typename Action, typename Enable>
    struct action_decorate_continuation
    {
        static bool call(hpx::actions::continuation_type& cont)
        {
            // by default we do nothing
            return false; // continuation has not been modified
        }
    };

    template <typename Action>
    struct action_decorate_continuation<Action
      , typename util::always_void<typename Action::type>::type>
      : action_decorate_continuation<typename Action::type>
    {};
}}

#endif



//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EXAMPLES_BRIGHT_FUTURE_DATAFLOW_STUBS_DATAFLOW_TRIGGER_HPP
#define EXAMPLES_BRIGHT_FUTURE_DATAFLOW_STUBS_DATAFLOW_TRIGGER_HPP

#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/stubs/stub_base.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <examples/bright_future/dataflow/server/dataflow_trigger.hpp>

namespace hpx { namespace lcos {
    namespace stubs
    {
        struct dataflow_trigger
            : components::stubs::stub_base<
                server::dataflow_trigger
            >
        {
            typedef server::dataflow_trigger server_type;
        };
    }
}}
#endif

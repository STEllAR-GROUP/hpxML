//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/components/component_registry.hpp>
#include <hpx/runtime/components/base_lco_factory.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/lcos/promise.hpp>

#include <vector>

namespace hpx { namespace traits { namespace detail
{
    boost::detail::atomic_count unique_type(
        static_cast<long>(components::component_last));
}}}

namespace hpx { namespace components { namespace detail
{
    util::one_size_heap_list_base* create_promise_heap(
        components::component_type type)
    {
        typedef detail::wrapper_heap_list<
            detail::fixed_wrapper_heap<managed_promise>
        > heap_type;

        return new heap_type(type);
    }
}}}


//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COMPONENTS_REMOTE_OBJECT_NEW_IMPL_HPP
#define HPX_COMPONENTS_REMOTE_OBJECT_NEW_IMPL_HPP

#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/naming/address.hpp>
#include <hpx/util/function.hpp>

namespace hpx { namespace components
{
    namespace remote_object
    {
        // implementation of new
        naming::id_type
        new_impl(
            naming::id_type const & target_id
          , util::function<void(void**)> ctor
          , util::function<void(void**)> dtor
          );

        // the action to invoke new_impl
        typedef
            actions::plain_result_action3<
                naming::id_type
              , naming::id_type const &
              , util::function<void(void**)>
              , util::function<void(void**)>
              , &new_impl
            >
            new_impl_action;
    }
}}

#endif

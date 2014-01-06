//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_COMPONENTS_SERVER_COPY_COMPONENT_SEP_20_2013_0825PM)
#define HPX_RUNTIME_COMPONENTS_SERVER_COPY_COMPONENT_SEP_20_2013_0825PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/naming/name.hpp>
#include <hpx/runtime/get_ptr.hpp>
#include <hpx/runtime/components/stubs/runtime_support.hpp>

#include <boost/serialization/shared_ptr.hpp>

namespace hpx { namespace components { namespace server
{
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy given component to the specified target locality
    namespace detail
    {
        template <typename Component>
        naming::id_type copy_component_postproc(
            unique_future<boost::shared_ptr<Component> > f,
            naming::id_type const& target_locality)
        {
            boost::shared_ptr<Component> ptr = f.get();
            return stubs::runtime_support::copy_create_component<Component>(
                target_locality, ptr, target_locality == find_here());
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component>
    unique_future<naming::id_type> copy_component(naming::id_type const& to_copy,
        naming::id_type const& target_locality)
    {
        unique_future<boost::shared_ptr<Component> > f = get_ptr<Component>(to_copy);
        return f.then(util::bind(&detail::copy_component_postproc<Component>, 
            util::placeholders::_1, target_locality));
    }

    template <typename Component>
    struct copy_component_action
      : ::hpx::actions::plain_result_action2<
            unique_future<naming::id_type>, naming::id_type const&, naming::id_type const&
          , &copy_component<Component>
          , copy_component_action<Component> >
    {};
}}}

HPX_REGISTER_PLAIN_ACTION_TEMPLATE(
    (template <typename Component>), (hpx::components::server::copy_component_action<Component>)
)

#endif


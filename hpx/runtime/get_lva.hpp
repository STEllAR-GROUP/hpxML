//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_GET_LVA_JUN_22_2008_0451PM)
#define HPX_RUNTIME_GET_LVA_JUN_22_2008_0451PM

#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/naming/address.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    /// \class get_lva get_lva.hpp hpx/runtime/get_lva.hpp
    ///
    /// The \a get_lva template is a helper structure allowing to convert a
    /// local virtual address as stored in a local address (returned from
    /// the function \a resolver_client#resolve) to the address of the
    /// component implementing the action.
    ///
    /// The default implementation uses the template argument \a Component
    /// to deduce the type wrapping the component implementing the action. This
    /// is used to get the needed address.
    ///
    /// The specialization for the \a runtime_support component is needed
    /// because this is not wrapped by a separate type as all the other
    /// components.
    ///
    /// \tparam Component  This is the type of the component implementing the
    ///                    action to execute.
    template <typename Component>
    struct get_lva
    {
        struct is_simple_or_fixed_component
          : boost::mpl::or_<
                boost::is_base_and_derived<
                    components::detail::simple_component_tag, Component
                >,
                boost::is_base_and_derived<
                    components::detail::fixed_component_tag, Component
                >
            >
        {};

        static Component*
        call(naming::address::address_type lva, boost::mpl::false_)
        {
            typedef typename Component::wrapping_type wrapping_type;
            return reinterpret_cast<wrapping_type*>(lva)->get_checked();
        }

        static Component*
        call(naming::address::address_type lva, boost::mpl::true_)
        {
            return reinterpret_cast<Component*>(lva);
        }

        static Component*
        call(naming::address::address_type lva)
        {
            return call(lva, is_simple_or_fixed_component());
        }
    };

    // specialization for components::server::runtime_support
    template <>
    struct get_lva<components::server::runtime_support>
    {
        // for server::runtime_support the provided lva is directly usable
        // as the required local address
        static components::server::runtime_support*
        call(naming::address::address_type lva)
        {
            return reinterpret_cast<components::server::runtime_support*>(lva);
        }
    };

    // specialization for components::server::memory
    template <>
    struct get_lva<components::server::memory>
    {
        // for server::memory the provided lva is directly usable as the
        // required local address
        static components::server::memory*
        call(naming::address::address_type lva)
        {
            return reinterpret_cast<components::server::memory*>(lva);
        }
    };

    // specialization for components::server::memory_block
    template <>
    struct get_lva<components::server::memory_block>
    {
        // for server::memory_block the provided lva is directly usable as the
        // required local address
        static components::server::memory_block*
        call(naming::address::address_type lva)
        {
            return reinterpret_cast<components::server::memory_block*>(lva);
        }
    };

}

#endif


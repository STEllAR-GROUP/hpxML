//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_TRAITS_IS_COMPONENT_OCT_10_2012_0221PM)
#define HPX_TRAITS_IS_COMPONENT_OCT_10_2012_0221PM

#include <hpx/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/utility/enable_if.hpp>

namespace hpx { namespace traits
{
    namespace detail
    {
        struct fixed_component_tag {};
        struct simple_component_tag {};
        struct component_tag : simple_component_tag {};
        struct managed_component_tag {};
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component, typename Enable = void>
    struct is_component
      : boost::mpl::false_
    {};

    template <typename Component>
    struct is_component<Component const>
      : is_component<Component>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Simple components are components
    template <typename Component>
    struct is_component<Component,
            typename boost::enable_if<
                boost::is_base_and_derived<
                    detail::simple_component_tag, Component
                > >::type>
      : boost::mpl::true_
    {};

    // Fixed components are components
    template <typename Component>
    struct is_component<Component,
            typename boost::enable_if<
                boost::is_base_and_derived<
                    detail::fixed_component_tag, Component
                > >::type>
      : boost::mpl::true_
    {};

    // Managed components are components
    template <typename Component>
    struct is_component<Component,
            typename boost::enable_if<
                boost::is_base_and_derived<
                    detail::managed_component_tag, Component
                > >::type>
      : boost::mpl::true_
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Enable = void>
    struct is_component_or_component_array
      : is_component<T>
    {};

    template <typename T>
    struct is_component_or_component_array<T[]>
      : is_component<T>
    {};

    template <typename T, std::size_t N>
    struct is_component_or_component_array<T[N]>
      : is_component<T>
    {};
}}

#endif


////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//  Copyright (c) 2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_B08244B4_3831_436F_9F72_3E82FFAF03E8)
#define HPX_B08244B4_3831_436F_9F72_3E82FFAF03E8

#include <hpx/hpx_fwd.hpp>

namespace hpx { namespace components
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Component>
    class simple_component;

    template <typename Component>
    class abstract_simple_component_base 
      : private detail::simple_component_tag
    {
    private:
        typedef simple_component<Component> outer_wrapping_type;

    public:
        virtual ~abstract_simple_component_base() {}

        typedef Component base_type_holder;

        static component_type get_component_type()
        {
            return hpx::components::get_component_type<outer_wrapping_type>();
        }

        static void set_component_type(component_type t)
        {
            hpx::components::set_component_type<outer_wrapping_type>(t);
        }

        /// This is the default hook implementation for decorate_action which 
        /// does no hooking at all.
        static HPX_STD_FUNCTION<threads::thread_function_type> 
        wrap_action(HPX_STD_FUNCTION<threads::thread_function_type> f,
            naming::address::address_type)
        {
            return std::move(f);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component, typename Derived>
    class managed_component;

    template <typename Component, typename Wrapper>
    class abstract_managed_component_base
      : private detail::managed_component_tag
    {
    public:
        typedef managed_component<Component, Wrapper> wrapping_type;

        virtual ~abstract_managed_component_base() {}

        typedef Component base_type_holder;

        static component_type get_component_type()
        {
            return hpx::components::get_component_type<wrapping_type>();
        }

        static void set_component_type(component_type t)
        {
            hpx::components::set_component_type<wrapping_type>(t);
        }

        /// This is the default hook implementation for decorate_action which 
        /// does no hooking at all.
        static HPX_STD_FUNCTION<threads::thread_function_type> 
        wrap_action(HPX_STD_FUNCTION<threads::thread_function_type> f,
            naming::address::address_type)
        {
            return std::move(f);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component>
    class fixed_component;

    template <typename Component>
    class abstract_fixed_component_base 
      : private detail::fixed_component_tag
    {
    private:
        typedef fixed_component<Component> outer_wrapping_type;

    public:
        virtual ~abstract_fixed_component_base() {}

        typedef Component base_type_holder;

        static component_type get_component_type()
        {
            return hpx::components::get_component_type<outer_wrapping_type>();
        }

        static void set_component_type(component_type t)
        {
            hpx::components::set_component_type<outer_wrapping_type>(t);
        }

        /// This is the default hook implementation for decorate_action which 
        /// does no hooking at all.
        static HPX_STD_FUNCTION<threads::thread_function_type> 
        wrap_action(HPX_STD_FUNCTION<threads::thread_function_type> f,
            naming::address::address_type)
        {
            return std::move(f);
        }
    };
}}

#endif // HPX_B08244B4_3831_436F_9F72_3E82FFAF03E8


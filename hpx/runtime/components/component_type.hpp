//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENT_COMPONENT_TYPE_MAR_26_2008_1058AM)
#define HPX_COMPONENT_COMPONENT_TYPE_MAR_26_2008_1058AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/traits/component_type_database.hpp>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components
{
    /// \brief Return the string representation for a given component type id
    HPX_EXPORT std::string const get_component_type_name(boost::int32_t type);

    /// The lower short word of the component type is the type of the component
    /// exposing the actions.
    inline component_type get_base_type(boost::int64_t t)
    {
        return component_type(t & 0xFFFF);
    }

    /// The upper short word of the component is the actual component type
    inline component_type get_derived_type(boost::int64_t t)
    {
        return component_type((t >> 16) & 0xFFFF);
    }

    /// A component derived from a base component exposing the actions needs to
    /// have a specially formatted component type.
    inline component_type
    derived_component_type(boost::int64_t derived, boost::int64_t base)
    {
        return component_type(derived << 16 | base);
    }

    /// \brief Verify the two given component types are matching (compatible)
    inline bool types_are_compatible(boost::int64_t lhs, boost::int64_t rhs)
    {
        // don't compare types if one of them is unknown
        if (component_invalid == rhs || component_invalid == lhs)
            return true;    // no way of telling, so we assume the best :-P

        // don't compare types if one of them is component_runtime_support
        if (component_runtime_support == rhs || component_runtime_support == lhs)
            return true;

        component_type lhs_base = get_base_type(lhs);
        component_type rhs_base = get_base_type(rhs);

        // special case for lco's
        if ((lhs_base == component_base_lco && rhs_base == component_base_lco_with_value) ||
            (rhs_base == component_base_lco && lhs_base == component_base_lco_with_value))
        {
            return true;
        }
        return lhs_base == rhs_base;
    }
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Component>
    inline component_type get_component_type()
    {
        return traits::component_type_database<Component>::get();
    }

    template <typename Component>
    inline void set_component_type(component_type type)
    {
        return traits::component_type_database<Component>::set(type);
    }

    ///////////////////////////////////////////////////////////////////////////
    enum factory_property
    {
        factory_invalid = -1,
        factory_none = 0,                   ///< The factory has no special properties
        factory_is_multi_instance = 1,      ///< The factory can be used to
                                            ///< create more than one component
                                            ///< at the same time
        factory_instance_count_is_size = 2, ///< The component count will be
                                            ///< interpreted as the component
                                            ///< size instead
    };
}}

///////////////////////////////////////////////////////////////////////////////
#define HPX_DEFINE_GET_COMPONENT_TYPE(component)                              \
    namespace hpx { namespace traits                                          \
    {                                                                         \
        template <> HPX_ALWAYS_EXPORT                                         \
        components::component_type component_type_database<component>::get()  \
            { return value; }                                                 \
        template <> HPX_ALWAYS_EXPORT                                         \
        void component_type_database<component>::set(                         \
            components::component_type t) { value = t; }                      \
    }}                                                                        \
    /**/

///////////////////////////////////////////////////////////////////////////////
#define HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(component, type)                 \
    namespace hpx { namespace traits                                          \
    {                                                                         \
        template <> HPX_ALWAYS_EXPORT                                         \
        components::component_type component_type_database<component>::get()  \
            { return type; }                                                  \
        template <> HPX_ALWAYS_EXPORT                                         \
        void component_type_database<component>::set(components::component_type) \
            { BOOST_ASSERT(false); }                                          \
    }}                                                                        \
    /**/

#endif


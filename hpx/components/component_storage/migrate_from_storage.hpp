//  Copyright (c) 2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_MIGRATE_FROM_STORAGE_FEB_09_2015_0329PM)
#define HPX_MIGRATE_FROM_STORAGE_FEB_09_2015_0329PM

#include <hpx/include/lcos.hpp>
#include <hpx/include/naming.hpp>
#include <hpx/include/traits.hpp>

#include <hpx/components/component_storage/server/migrate_from_storage.hpp>

#include <type_traits>

namespace hpx { namespace components
{
    /// Migrate the component with the given id from the specified target
    /// storage (resurrect the object)
    ///
    /// The function \a migrate_from_storage<Component> will migrate the
    /// component referenced by \a to_resurrect from the storage facility
    /// specified with \a source_storage. It returns a future referring to
    /// the migrated component instance. The component instance is resurrected
    /// on the locality specified by \a target_locality.
    ///
    /// \param to_resurrect    [in] The global id of the component to migrate.
    /// \param source_storage  [in] The id of the storage facility to migrate
    ///                        this object from.
    /// \param target          [in] The optional locality to resurrect the
    ///                        object on. By default the object is resurrected
    ///                        on the locality it was located on last.
    ///
    /// \tparam  The only template argument specifies the component type of the
    ///          component to migrate from the given storage facility.
    ///
    /// \returns A future representing the global id of the migrated
    ///          component instance. This should be the same as \a to_resurrect.
    ///
    template <typename Component>
#if defined(DOXYGEN)
    future<naming::id_type>
#else
    inline typename std::enable_if<
        traits::is_component<Component>::value, future<naming::id_type>
    >::type
#endif
    migrate_from_storage(naming::id_type const& to_resurrect,
        naming::id_type const& source_storage,
        naming::id_type const& target = naming::invalid_id)
    {
        typedef server::migrate_from_storage_here_action<Component>
            action_type;
        return async_colocated<action_type>(source_storage, source_storage,
            to_resurrect, target);
    }

    template <typename Component>
#if defined(DOXYGEN)
    future<naming::id_type>
#else
    inline typename std::enable_if<
        traits::is_component<Component>::value, future<naming::id_type>
    >::type
#endif
    migrate_from_storage(naming::id_type const& to_resurrect,
        hpx::components::component_storage const& source_storage,
        naming::id_type const& target = naming::invalid_id)
    {
        return migrate_from_storage<Component>(source_storage.get_gid(),
            to_resurrect, target);
    }
}}

#endif



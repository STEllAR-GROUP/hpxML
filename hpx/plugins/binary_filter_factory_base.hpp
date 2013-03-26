//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_MESSAGE_HANDLER_FACTORY_BASE_MAR_24_2013_0339PM)
#define HPX_MESSAGE_HANDLER_FACTORY_BASE_MAR_24_2013_0339PM

#include <hpx/config.hpp>
#include <hpx/plugins/plugin_factory_base.hpp>

#include <hpx/util/plugin.hpp>
#include <hpx/util/plugin/export_plugin.hpp>
#include <hpx/util/binary_filter.hpp>

#include <boost/mpl/list.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace plugins
{
    ///////////////////////////////////////////////////////////////////////////
    /// The \a plugin_factory_base has to be used as a base class for all
    /// plugin factories.
    struct HPX_EXPORT binary_filter_factory_base : plugin_factory_base
    {
        virtual ~binary_filter_factory_base() {}

        /// Create a new instance of a binary filter
        ///
        /// return Returns the newly created instance of the binary filter
        ///        supported by this factory
        virtual util::binary_filter* create() = 0;
    };
}}

///////////////////////////////////////////////////////////////////////////////
/// This macro is used to register the given component factory with
/// Hpx.Plugin. This macro has to be used for each of the component factories.
#define HPX_REGISTER_BINARY_FILTER_FACTORY_BASE(FactoryType, componentname)   \
        HPX_PLUGIN_EXPORT(HPX_PLUGIN_PREFIX,                                  \
            hpx::plugins::binary_filter_factory_base, FactoryType,            \
            pluginname, binary_filter)                                        \
    /**/

#endif


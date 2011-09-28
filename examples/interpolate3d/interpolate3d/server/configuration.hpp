//  Copyright (c) 2007-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_INTERPOLATE3D_CONFIGURATION_AUG_07_2011_0641PM)
#define HPX_INTERPOLATE3D_CONFIGURATION_AUG_07_2011_0641PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/promise.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/server/simple_component_base.hpp>

namespace interpolate3d 
{
    ///////////////////////////////////////////////////////////////////////////
    struct config_data
    {
        config_data() : num_instances_(0) {}

        std::string datafile_name_;     // data file to load the data from
        std::string symbolic_name_;     // symbolic name this instance is registered
        std::size_t num_instances_;     // number of partition instances
    };
}

namespace interpolate3d { namespace server
{
    ///////////////////////////////////////////////////////////////////////////
    class HPX_COMPONENT_EXPORT configuration
      : public hpx::components::simple_component_base<configuration>
    {
    private:
        typedef hpx::components::simple_component_base<configuration> base_type;

    public:
        configuration();

        // components must contain a typedef for wrapping_type defining the
        // component type used to encapsulate instances of this component
        typedef configuration wrapping_type;

        ///////////////////////////////////////////////////////////////////////
        // parcel action code: the action to be performed on the destination 
        // object (the accumulator)
        enum actions
        {
            configuration_init = 0,
            configuration_get = 1
        };

        // exposed functionality
        void init(std::string const& datafile, std::string const& symbolic_name, 
            std::size_t num_instances);
        config_data get() const;

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into an action
        // type, allowing to generate all required boilerplate code for threads,
        // serialization, etc.
        typedef hpx::actions::action3<
            configuration, configuration_init, 
            std::string const&, std::string const&, std::size_t, 
            &configuration::init
        > init_action;

        typedef hpx::actions::result_action0<
            configuration const, config_data, configuration_get, 
            &configuration::get
        > get_action;

    private:
        config_data data_;
    };
}}

///////////////////////////////////////////////////////////////////////////////
// non-intrusive serialization
namespace boost { namespace serialization
{
    template <typename Archive>
    void serialize(Archive&, interpolate3d::config_data&, unsigned int const);
}}

#endif

//  Copyright (c) 2012 Vinay C Amatya
//
//  Distributed under the Boost Software License, Version 1.0. (Seec accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/runtime/agas/interface.hpp>
#include <hpx/runtime/components/component_factory_base.hpp>
#include <hpx/components/distributing_factory/distributing_factory.hpp>

#include <boost/foreach.hpp>
#include <boost/assert.hpp>

#include "distribution.hpp"

HPX_REGISTER_COMPONENT_MODULE(); //entry point for component factory

typedef distributed::datastructure datastructure_client_type;
HPX_DEFINE_GET_COMPONENT_TYPE(datastructure_client_type);

//----------------------------------------------------

namespace distributed
{
    distribution::distribution():comp_created_(false)
    {}
    distribution::~distribution(){}

    void distribution::create(std::string const& symbolic_name_base
        , std::size_t num_instances, std::vector<std::size_t> data_received)
    {
        std::size_t init_length = 1, init_value = 0;
        hpx::components::component_type type = 
            hpx::components::get_component_type<server::datastructure>();
        
        typedef hpx::components::distributing_factory distributing_factory;
    
        distributing_factory factory(
            distributing_factory::create_sync(hpx::find_here()));
        //asyncronously create comonents, which will be distributed across
        //all available localities
        distributing_factory::async_create_result_type result = 
            factory.create_components_async(type, num_instances);

        //initialize locality mappings: Total Component instances
        comp_instances_.reserve(num_instances);

        //wait for the components to be created
        distributing_factory::result_type results = result.get();
        distributing_factory::iterator_range_type parts = 
            hpx::components::server::locality_results(results);

        std::size_t cardinality = 0;
        //Also define cardinality here: TO DO
        BOOST_FOREACH(hpx::naming::id_type id, parts){
            comp_instances_.push_back(id);
        }

        //Initialize all attached component objects
        std::size_t num_comps = comp_instances_.size();
        BOOST_ASSERT( 0 != num_comps);
        BOOST_ASSERT( 0 != num_instances);
        std::vector<hpx::naming::id_type> prefixes = hpx::find_all_localities();
       
        std::vector<hpx::lcos::promise<void> > result_future;

        std::vector<hpx::naming::id_type>::iterator loc_itr = comp_instances_.begin();
        while(loc_itr != comp_instances_.end())
        {
            result_future.push_back(stubs::datastructure::data_init_async(*loc_itr
                , symbolic_name_base, num_comps, cardinality
                , init_length, init_value));
            ++cardinality;
            ++loc_itr;
        }
        hpx::lcos::wait(result_future);

        typedef std::vector<std::vector<std::size_t> > client_data_type;
        
        client_data_type dd_vector;
        
        split_client_data(num_instances, data_received, dd_vector);
        loc_itr = comp_instances_.begin();
        result_future.resize(0);
        client_data_type::iterator dd_itr;
        dd_itr = dd_vector.begin();
        loc_itr = comp_instances_.begin();
        cardinality = 0;
        while(loc_itr != comp_instances_.end())
        {
            result_future.push_back(stubs::datastructure::data_write_async(
                *loc_itr, symbolic_name_base, num_comps, cardinality
                , *dd_itr));
            ++cardinality;
            ++dd_itr;
            ++loc_itr;
        }
        hpx::lcos::wait(result_future);
        //Create component object locally. 
        comp_created_ = true;
    }

    void distribution::split_client_data(
        std::size_t num_instances, std::vector<std::size_t> &data_received
        , std::vector<std::vector<std::size_t>> &dd_vector)
    {

        dd_vector.resize(0);
        std::size_t client_vec_length = data_received.size();
        std::size_t quotient = client_vec_length / num_instances;
        std::size_t rem = client_vec_length%num_instances;
        std::vector<std::size_t>::iterator itr;
        itr = data_received.begin();
        std::vector<std::size_t> temp;
        if(rem == 0)
        {
            for(std::size_t i = 0; i<num_instances; ++i)
            {
                temp.resize(0);
                if(itr <= (data_received.end() - quotient))
                {
                    temp.assign(itr, itr + quotient);
                    dd_vector.push_back(temp);
                    itr+=quotient+1;
                }
            }
        }
        else
        {
            for(std::size_t i = 0; i<num_instances - 1; ++ i)
            {
                temp.resize(0);
                if(itr <= (data_received.end() - quotient))
                {
                    temp.assign(itr, itr+(quotient+1));
                    dd_vector.push_back(temp);
                    itr+=quotient+1;
                }
            }

            temp.resize(0);
            temp.assign(itr, data_received.end());
            dd_vector.push_back(temp);
        }
    }
}

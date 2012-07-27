//  Copyright (c) 2007-2011 Matthew Anderson
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include<iostream>
#include<vector>
#include<math.h>
#include "fname.h"

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>

#include "tsf/server/point.hpp"
#include <hpx/components/distributing_factory/distributing_factory.hpp>

bool fexists(std::string const filename)
{
  std::ifstream ifile(filename);
  return ifile ? true : false;
}

/// This function initializes a vector of \a tsf::point clients,
/// connecting them to components created with
/// \a hpx::components::distributing_factory.
inline void
init(hpx::components::server::distributing_factory::iterator_range_type const& r,
    std::vector<hpx::naming::id_type>& p)
{
    BOOST_FOREACH(hpx::naming::id_type const& id, r)
    {
        p.push_back(id);
    }
}


///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map &vm)
{
    {
        // Start a high resolution timer to record the execution time of this
        // example.
        hpx::util::high_resolution_timer t;

        ///////////////////////////////////////////////////////////////////////
        // Get the component type for our point component.
        hpx::components::component_type block_type =
        hpx::components::get_component_type<tsf::server::point>();

        hpx::components::distributing_factory factory;
        factory.create(hpx::find_here());

        std::size_t num_partitions = 10;
        hpx::components::distributing_factory::result_type blocks =
                                  factory.create_components(block_type, num_partitions);

        // This vector will hold client classes referring to all of the
        // components we just created.
        std::vector<hpx::naming::id_type> components;
        // Populate the client vectors.
        init(hpx::util::locality_results(blocks), components);

        {
          std::cout << " SETUP TEST " << std::endl;
          std::vector<hpx::lcos::future<void> > setup_phase;
          tsf::server::point::setup_action setup;
          for (std::size_t i=0;i<num_partitions;i++) {
            setup_phase.push_back(hpx::async(setup,components[i],num_partitions,i,components));
          }
          hpx::lcos::wait(setup_phase);
        }
          std::cout << " FINISHED SETUP TEST " << std::endl;

    } // Ensure things go out of scope before hpx::finalize is called.

    hpx::finalize();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    using boost::program_options::value;

    // Configure application-specific options.
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    return hpx::init(desc_commandline, argc, argv); // Initialize and run HPX.
}


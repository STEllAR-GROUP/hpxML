//  Copyright (c) 2012 Vinay C Amatya
//
//  Distributed under the Boost Software License, Version 1.0. (Seec accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <boost/assign/std.hpp>
#include "distributed_test/distribution.hpp"

using boost::program_options::variables_map;
using boost::program_options::options_description;

///////////////////////////////////////////////////////////////////////////////

int hpx_main(variables_map& vm)
{
    std::size_t num_instances = 2;
    //std::size_t my_cardinality = std::size_t(-1);
    std::size_t init_length = 9;//, init_value = 5;
    //--------------------------
    char const* distrib_symbolic_name = "distributed_symbolic_name";
   
    distributed::distribution distrib;
    std::vector<std::size_t> temp_data;
    while(init_length != temp_data.size())
    {
        std::size_t temp = std::rand();
        if (temp > 0 )
            temp_data.push_back(temp);
        else
            temp_data.push_back(0);
    }
    std::vector<hpx::naming::id_type> prefixes = hpx::find_all_localities();
    distrib.create(distrib_symbolic_name, num_instances, temp_data);
    //------------------------
    hpx::finalize();
    return 0;
}
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    //aplication specific options
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    //Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}

//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>

#include <hpx/include/parallel_executors.hpp>
#include <hpx/include/parallel_transform.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>

#include "evaluating_performances.hpp"

//-------------------------------------------
int hpx_main(boost::program_options::variables_map& vm)
{
    std::size_t Nx = vm["Nx"].as<std::size_t>();
    int level_octree = vm["level_octree"].as<int>();
    int steps = vm["steps"].as<int>();
    double distance_threshold = vm["distance"].as<double>(); 
    std::size_t number_of_instructions = vm["instructions"].as<std::size_t>();

    //initializing bodies and creating octree based on the given information
    std::vector<Cube*> octree;
    std::vector<Body*> body = initialize_bodies(Nx);
    creating_octree(level_octree, body, octree);
    creating_barneshut_interaction_list(distance_threshold, octree);

    // perform benchmark
    std::vector<std::vector<double> > timing;    
    timing = computing_forces_on_all_bodies(steps, body);
    //print_new_location(20, body);

     // --- SUMMARY --- 
    const char *label[3] = {
        "original_for_each:                       ", //with normal for_each
        "chunk_size_for_each:                     ", //with adaptive_chunk_size
        "prefetch_for_each:                       "  //with prfetching itr        
    };

    /*
	Number of total instructions:
	1000: 188000
	10000: 1880000
	100000: 18800000
	1000000: 18800000
    */
	
    const double bytes[3] = {
        static_cast<double>(number_of_instructions) * sizeof(double),
        static_cast<double>(number_of_instructions) * sizeof(double),
        static_cast<double>(number_of_instructions) * sizeof(double)
    };

    // Note: skip first iteration
    std::vector<double> avgtime(3, 0.0);
    std::vector<double> mintime(3, (std::numeric_limits<double>::max)());
    std::vector<double> maxtime(3, 0.0);
    for(int iteration = 1; iteration != steps; ++iteration)
    {
        for (std::size_t j=0; j<3; j++)
        {
            avgtime[j] = avgtime[j] + timing[j][iteration];
            mintime[j] = (std::min)(mintime[j], timing[j][iteration]);
            maxtime[j] = (std::max)(maxtime[j], timing[j][iteration]);
        }
    }

    printf("Function                           BestRate GB/s  Avg time     Min time     Max time\n");
    // Printing all
    
    for (std::size_t j = 0; j < 3; j++) {
        avgtime[j] = avgtime[j]/(double)(steps-1);

        printf("%s%12.1f  %11.6f  %11.6f  %11.6f\n", label[j],
           1.0E-09 * bytes[j]/mintime[j],
           avgtime[j],
           mintime[j],
           maxtime[j]);
    }

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    using namespace boost::program_options;

    options_description desc_commandline;
    desc_commandline.add_options()
        ("Nx", value<std::size_t>()->default_value(1000),
         "Number of bodies")
        ("level_octree", value<int>()->default_value(3),
         "Level of octree")
        ("distance", value<double>()->default_value(2),
         "distance threshhold for implmeneting BarnesHut algorithm")
        ("instructions", value<std::size_t>()->default_value(188000),
         "number of total instructions")
        ("steps", value<int>()->default_value(2),
         "Number of steps to compute force of each body")
    ;

    // parse command line here to extract the necessary settings for HPX
    parsed_options opts =
        command_line_parser(argc, argv)
            .allow_unregistered()
            .options(desc_commandline)
            .style(command_line_style::unix_style)
            .run();

    variables_map vm;
    store(opts, vm);

    std::vector<std::string> cfg = {
        "hpx.numa_sensitive=2"  // no-cross NUMA stealing
    };

    return hpx::init(desc_commandline, argc, argv, cfg);
}
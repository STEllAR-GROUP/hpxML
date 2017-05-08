//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/include/compute.hpp>

//new classes for implementing machine learning techniques
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/parallel/seq_or_par.hpp>
#include <hpx/parallel/chunk_size_determination.hpp>
#include <hpx/parallel/prefetching_distance_determination.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <hpx/parallel/executors/adaptive_chunk_size.hpp>

#include <boost/range/functions.hpp>

#include "octree.hpp"
#include "barnesHut.hpp"
#include "computing_force_location_velocity.hpp"

//Intitializing bodies
std::vector<Body*> initialize_bodies(int number_of_bodies) {
	std::vector<Body*> body;
	for(std::size_t i = 0; i < number_of_bodies; i++) {
		srand(i);
		Body* b = new Body();
		b->location[0] = rand() % 100 + 1;
		b->location[1] = rand() % 100 + 1;
		b->location[2] = rand() % 100 + 1;
		b->velocity[0] = rand() % 100 + 1;
		b->velocity[1] = rand() % 100 + 1;
		b->velocity[2] = rand() % 100 + 1;
		b->force[0] = 0;
		b->force[1] = 0;
		b->force[2] = 0;
		b->mass = rand() % 10 + 1;
		body.push_back(b);
	}

	return body;
}

//-------------------------------------------
//evaluating performances:
double mysecond()
{
    return hpx::util::high_resolution_clock::now()  * 1e-9;
}

std::vector<std::vector<double>> 
computing_forces_on_all_bodies(int steps, std::vector<Body*>& body) {

	// Get the numa targets we want to run on
    auto numa_nodes = hpx::compute::host::numa_domains();
    typedef hpx::compute::host::block_executor<> executor_type;
    typedef hpx::compute::host::block_allocator<double> allocator_type;
    executor_type exec(numa_nodes);

    // Creating the policy used in the parallel algorithms
    auto policy = hpx::parallel::execution::par.on(exec);
	
	int number_of_bodies = body.size();
	auto all_bodies = boost::irange(0, number_of_bodies);

	std::vector<std::vector<double>> timing(3, std::vector<double>(steps));
	//int sum1 = 0, sum2 = 0; //for counting number of instructions

	auto f = [&](std::size_t i) {

			body[i]->force[0] = 0.0;
			body[i]->force[1] = 0.0;
			body[i]->force[2] = 0.0;
			Cube* parent = body[i]->parent;
			for(std::size_t c = 0; c < (parent->near_cells).size(); c++) {
				compute_force_from_near_cells(body[i], 
											(parent->near_cells)[c]);				
			}
			for(std::size_t c = 0; c < (parent->remote_cells).size(); c++) {
				compute_force_from_remote_cells(body[i], 
												(parent->remote_cells)[c]);
			}

			//computing new location:
			compute_location_and_velocity(body[i]);

			//study if this body moved to another location:
			find_new_parent(body[i]);
		};

	//computing froce on each body in each time step
	//without using ML techniques:
	for(int t = 0; t < steps; t++) { //step * number_of_bodies * ( SUM1 + SUM2 + 37 + 140)

		////////////////////////////////////////////////
		//without using ML techniques
		timing[0][t] = mysecond();

		hpx::parallel::for_each(policy, all_bodies.begin(), all_bodies.end(), f);

		timing[0][t] = mysecond() - timing[0][t];	

		////////////////////////////////////////////////
		//efficient chunk size
		timing[1][t] = mysecond();
		
		hpx::parallel::for_each(policy.with(hpx::parallel::adaptive_chunk_size()), all_bodies.begin(), all_bodies.end(), f);
		
		timing[1][t] = mysecond() - timing[1][t];	

		////////////////////////////////////////////////
		//efficient prefetching distance
		timing[2][t] = mysecond();
		
		hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, 1, body), all_bodies.begin(), all_bodies.end(), f);

		timing[2][t] = mysecond() - timing[2][t];

		////////////////////////////////////////////////
	}	

	// total instructions:
	//int sum_total = (11 + sum1 * 74 + sum2 * 72 + 37 + 140 ) * body.size();
	//std::cout << "\n [ " << body.size() << " ] = " << sum_total << "\n";

	return timing;
}

//-------------------------------------------
//printing new locations:
void print_new_location(std::size_t size, std::vector<Body*>& body) {
	for(std::size_t i = 0; i < size; i++) {
		std::cout<<(double)(body[i]->location[0])<<", ";
	}
	std::cout<<std::endl;
}
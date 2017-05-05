//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "body_cube.hpp"

#if !defined(BARNESHUT_HPP_MAY_2017)
#define BARNESHUT_HPP_MAY_2017

/*
Once  the  particles  are  partitioned  into  an  Octree,  the  interaction  list  
for  each  particle is  created  by  a  traversal  of  the  Octree  by  each  sub-Octree
piece. The interaction list of the particle holds the list of the particles that are 
near objects to that particle and the cubes that are  modeled  as  faraway  objects  to  that  particle. 
The  remote  cube  of  the  particles  is  treated  as  a  single particle only if their "distance" 
is greater than its ("radiuse" / "distance_threshold"). "distance_threshold" controls the error of the
approximation. A smaller ratio produces more accurate results but increases the execution time. 
On the other hand, a larger ratio produces less accurate results but decreases the execution time.
*/

//creating BarnesHut list:
double distance(Cube* c1, Cube* c2, double distance_threshold) {
	double dist = 0.0;
	dist = sqrt(pow((c1->center_of_mass[0] - c2->center_of_mass[0]), 2.0) + 
				pow((c1->center_of_mass[1] - c2->center_of_mass[1]), 2.0) + 
				pow((c1->center_of_mass[2] - c2->center_of_mass[2]), 2.0)) * distance_threshold;
	return dist;
}

double radiuse(Cube* c) {
	double rd = sqrt(pow((c->boundary[1] - c->boundary[0]), 2.0));
	return rd;
}

void creating_barneshut_interaction_list(double distance_threshold, std::vector<Cube*>& octree) {

	//creating list of interaction for each cube:
	for(int i = 0; i < octree.size(); i++) {
		if((octree[i]->near_cells).size() == 0 && octree[i]->id != 0 && octree[i]->mass != 0) {
			int level = octree[i]->level;
			std::vector<int> start_end = finding_start_end(level);

			for(int c = start_end[0]; c < start_end[1] - 1; c++) {

				if(octree[c]->id != octree[i]->id) {
					if(distance(octree[i], octree[c], distance_threshold) < radiuse(octree[i])) {
						(octree[i]->near_cells).push_back(octree[c]);
					}

					else {
						(octree[i]->remote_cells).push_back(octree[c]);
					}
				}
			}
		}
	}
}

#endif
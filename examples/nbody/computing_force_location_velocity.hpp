//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "body_cube.hpp"

#if !defined(COMPUTING_FORCE_LOCATION_VELOCITY_HPP_MAY_2017)
#define COMPUTING_FORCE_LOCATION_VELOCITY_HPP_MAY_2017

/*
In the three dimensional N-Body problem, there are Nx particle masses, moving under the
influence of gravitational attraction. Each particle i has an initial position named as "location"
with initial "velocity". We use Newton’s law of gravity for computing the gravitational force
felt  by  the  mass "i" as it interacts with a single mass "j" in its parent's "near_cells"'s body_members or
by a remote cube of its parent's "remote_cells".
*/

double G=6.673;

//computing force on each body in an octree:
void compute_force_from_near_cells(Body* b, Cube* c){ // c->body_members).size() * 74
	for(std::size_t i = 0; i < (c->body_members).size() && (c->body_members)[i]->parent == c; i++) {
		Body* other_body = (c->body_members)[i]; //2
		b->force[0] +=  (G * b->mass * other_body->mass * (b->location[0] - other_body->location[0]))/pow((pow((b->location[0] - other_body->location[0]), 2.0) + 
						pow((b->location[1] - other_body->location[1]), 2.0) + 
						pow((b->location[2] - other_body->location[2]), 2.0)), 1.5); //24
		b->force[1] +=  (G * b->mass * other_body->mass * (b->location[1] - other_body->location[1]))/pow((pow((b->location[0] - other_body->location[0]), 2.0) + 
						pow((b->location[1] - other_body->location[1]), 2.0) + 
						pow((b->location[2] - other_body->location[2]), 2.0)), 1.5); //24
		b->force[2] +=  (G * b->mass * other_body->mass * (b->location[2] - other_body->location[2]))/pow((pow((b->location[0] - other_body->location[0]), 2.0) + 
						pow((b->location[1] - other_body->location[1]), 2.0) + 
						pow((b->location[2] - other_body->location[2]), 2.0)), 1.5); //24
	}

}

void compute_force_from_remote_cells(Body* b, Cube* c) { // 72
	b->force[0] +=  (G * b->mass * c->mass * (c->center_of_mass[0] - b->location[0]))/pow((pow((b->location[0] - c->center_of_mass[0]), 2.0) + 
					pow((b->location[1] - c->center_of_mass[1]), 2.0) + 
					pow((b->location[2] - c->center_of_mass[2]), 2.0)), 1.5); //24
	b->force[1] +=  (G * b->mass * c->mass * c->center_of_mass[1] - (b->location[1]))/pow((pow((b->location[0] - c->center_of_mass[0]), 2.0) + 
					pow((b->location[1] - c->center_of_mass[1]), 2.0) + 
					pow((b->location[2] - c->center_of_mass[2]), 2.0)), 1.5); //24
	b->force[2] +=  (G * b->mass * c->mass * (c->center_of_mass[2] - b->location[2]))/pow((pow((b->location[0] - c->center_of_mass[0]), 2.0) + 
					pow((b->location[1] - c->center_of_mass[1]), 2.0) + 
					pow((b->location[2] - c->center_of_mass[2]), 2.0)), 1.5); //24
}

//computing body's new location and new velocity resulted from the applied forces
void compute_location_and_velocity(Body* b) { //37
	double slope[3];
	for(int i = 0; i < 3; i++) {
		slope[i] =  b->force[i]/b->mass; //4
		b->velocity[i] += slope[i]; //3
		b->location[i] += (b->velocity[i] + slope[i]);	 //5	
	}
}

//study if a body moved to another cube
bool if_moved(Body* b, Cube* c) {
	if(b->location[0] < c->boundary[0] || b->location[0] > c->boundary[1] 
		|| b->location[1] < c->boundary[2] || b->location[1] > c->boundary[3]
		|| b->location[2] < c->boundary[4] || b->location[2] > c->boundary[5]) { //22
		return true;
	}

	return false;
}

//finding new parent for a moved-body
void find_parent(Body* b, Cube* c) { //127
	if(if_moved(b, c)) {

		//searching if moved to the left:
		if(b->location[0] < c->boundary[0] 
			&& b->location[1] >= c->boundary[2] && b->location[1] <= c->boundary[3]
			&& b->location[2] >= c->boundary[4] && b->location[2] <= c->boundary[5]) { //19
			if(c->left != nullptr) { //1
				find_parent(b, c->left);
			}
			else if((c->parent)->left != nullptr) { //1
				find_parent(b, (c->parent)->left);
			}
		}

		//searching if moved to the right:
		if(b->location[0] > c->boundary[1] 
			&& b->location[1] >= c->boundary[2] && b->location[1] <= c->boundary[3]
			&& b->location[2] >= c->boundary[4] && b->location[2] <= c->boundary[5]) { //19
			if(c->right != nullptr) { //1
				find_parent(b, c->right);
			}
			else if((c->parent)->right != nullptr) { //1
				find_parent(b, (c->parent)->right);
			}
		}

		//searching if moved down:
		if(b->location[1] < c->boundary[2] 
			&& b->location[0] >= c->boundary[0] && b->location[0] <= c->boundary[1]
			&& b->location[2] >= c->boundary[4] && b->location[2] <= c->boundary[5]) { //19
			if(c->down != nullptr) { //1
				find_parent(b, c->down);
			}
			else if((c->parent)->down != nullptr) { //1
				find_parent(b, (c->parent)->down);
			}
		}

		//searching if moved up:
		if(b->location[1] > c->boundary[3] 
			&& b->location[0] >= c->boundary[0] && b->location[0] <= c->boundary[1]
			&& b->location[2] >= c->boundary[4] && b->location[2] <= c->boundary[5]) { //19
			if(c->up != nullptr) { //1
				find_parent(b, c->up);
			}
			else if((c->parent)->up != nullptr) { //1
				find_parent(b, (c->parent)->up);
			}
		}

		//searching if moved back:
		if(b->location[2] < c->boundary[4] 
			&& b->location[0] >= c->boundary[0] && b->location[0] <= c->boundary[1]
			&& b->location[1] >= c->boundary[2] && b->location[1] <= c->boundary[3]) { //19
			if(c->back != nullptr) { //1
				find_parent(b, c->back);
			}
			else if((c->parent)->back != nullptr) { //1
				find_parent(b, (c->parent)->back);
			}
		}

		//searching if moved front:
		if(b->location[2] > c->boundary[5] 
			&& b->location[0] >= c->boundary[0] && b->location[0] <= c->boundary[1]
			&& b->location[1] >= c->boundary[2] && b->location[1] <= c->boundary[3]) { //19
			if(c->front != nullptr) { //1
				find_parent(b, c->front);
			}
			else if((c->parent)->front != nullptr) { //1
				find_parent(b, (c->parent)->front);
			}
		}
	}

	b->parent = c; //1
	//(c->body_members).push_back(b);
}

//finding new parent of a body if it moves out of its current parent
void find_new_parent(Body* b) { //127 + 13 = 140
	if(if_moved(b, b->parent)) { //13

		//changing its total mass & center_of_mass:
		(b->parent)->mass -= b->mass;

		(b->parent)->center_of_mass[0] -= (b->location[0]/(b->parent)->mass);
		(b->parent)->center_of_mass[1] -= (b->location[1]/(b->parent)->mass);
		(b->parent)->center_of_mass[2] -= (b->location[2]/(b->parent)->mass);

		find_parent(b, b->parent);
	}
}

#endif
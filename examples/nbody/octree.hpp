//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "body_cube.hpp"

#if !defined(OCTREE_HPP_MAY_2017)
#define OCTREE_HPP_MAY_2017

void dividing_parent_bodies_into_its_subcubes(Cube* parent, std::vector<Body*>& body, std::vector<Cube*>& octree) {

	for(int i = 1; i < 9; i++) {
		int parent_id = parent->id;
		int sub_cube_id = parent_id * 8 + i;		

		//inserting sub-cubes into parent cube:
		(octree[parent_id]->cube_members).push_back(octree[sub_cube_id]);

		//scattering parents bodies into its 8 sub-cubes:
		for(int i = 0; i < (octree[parent_id]->body_members).size(); i++) {
			Body* b = octree[parent_id]->body_members[i];

			if(b->location[0] >= octree[sub_cube_id]->boundary[0] && b->location[0] < octree[sub_cube_id]->boundary[1]
				&& b->location[1] >= octree[sub_cube_id]->boundary[2] && b->location[1] < octree[sub_cube_id]->boundary[3]
				&& b->location[2] >= octree[sub_cube_id]->boundary[4] && b->location[2] < octree[sub_cube_id]->boundary[5]) {
				
				(octree[sub_cube_id]->body_members).push_back(b);
				octree[sub_cube_id]->mass += b->mass;
				octree[sub_cube_id]->init_location[0] += b->location[0];
				octree[sub_cube_id]->init_location[1] += b->location[1];
				octree[sub_cube_id]->init_location[2] += b->location[2];
				b->parent = octree[sub_cube_id];
			}
		}

		//its center of mass : used for BarnesHut algorithm:
		if(octree[sub_cube_id]->mass != 0) {
			octree[sub_cube_id]->center_of_mass[0] = octree[sub_cube_id]->init_location[0]/octree[sub_cube_id]->mass;
			octree[sub_cube_id]->center_of_mass[1] = octree[sub_cube_id]->init_location[1]/octree[sub_cube_id]->mass;
			octree[sub_cube_id]->center_of_mass[2] = octree[sub_cube_id]->init_location[2]/octree[sub_cube_id]->mass;
		}
	}
}

//
std::vector<int> finding_start_end(int level) {

	std::vector<int> start_end(2, 0);

	//assiging start idx:
	int temp = level - 1;
	while(temp >= 0) {
		start_end[0] += pow(8, temp);
		temp--;
	}

	//assigning end_idx
	start_end[1] = pow(8, level) + 9;
	if(level == 1) {
		start_end[1] = 9;
	}

	return start_end;
}

//creating Octree:
void creating_octree(int level_octree, std::vector<Body*>& body, std::vector<Cube*>& octree) {

	//-------------------
	//big parrent:
	Cube* first_cube = new Cube();
	first_cube->id = 0;
	first_cube->level = 0;
	first_cube->boundary[0] = -500;
	first_cube->boundary[1] = 500;
	first_cube->boundary[2] = -500;
	first_cube->boundary[3] = 500;
	first_cube->boundary[4] = -500;
	first_cube->boundary[5] = 500;

	//all bodies will be inserted within this cube:
	for(int b = 0; b < body.size(); b++) {
		body[b]->parent = first_cube;
		first_cube->body_members.push_back(body[b]);
		first_cube->mass += body[b]->mass;
		first_cube->init_location[0] += body[b]->location[0];
		first_cube->init_location[1] += body[b]->location[1];
		first_cube->init_location[2] += body[b]->location[2];
	}

	//its center of mass : used for BarnesHut algorithm
	first_cube->center_of_mass[0] = first_cube->init_location[0]/first_cube->mass;
	first_cube->center_of_mass[1] = first_cube->init_location[1]/first_cube->mass;
	first_cube->center_of_mass[2] = first_cube->init_location[2]/first_cube->mass;

	octree.push_back(first_cube);

	//-------------------
	//creating octree based on the given level
	for(int l = 1; l < level_octree; l++) {
		
		std::vector<int> start_end = finding_start_end(l);
		int idx = start_end[0];

		while(idx < start_end[1]) {
			int idx_parent = ceil((idx - 1.0)/8.0);
			idx += 8;

			//main cube for division:
			Cube* p = octree[idx_parent];
			int level_parent = p->level;

			//initializing its 8 sub_cubes:
			Cube* sub_cube1 = new Cube();
			sub_cube1->id = p->id * 8 + 1; 
			sub_cube1->boundary[0] = p->boundary[0];
			sub_cube1->boundary[1] = p->boundary[0] + (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube1->boundary[2] = p->boundary[2];
			sub_cube1->boundary[3] = p->boundary[2] + (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube1->boundary[4] = p->boundary[4];
			sub_cube1->boundary[5] = p->boundary[4] + (p->boundary[5] - p->boundary[4])/2.0;
			p->c[0] = sub_cube1;
			sub_cube1->parent = p;
			sub_cube1->level = level_parent + 1;
			
			Cube* sub_cube2 = new Cube();
			sub_cube2->id = p->id * 8 + 2; 
			sub_cube2->boundary[0] = p->boundary[1] - (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube2->boundary[1] = p->boundary[1];
			sub_cube2->boundary[2] = p->boundary[3] - (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube2->boundary[3] = p->boundary[3];
			sub_cube2->boundary[4] = p->boundary[5] - (p->boundary[5] - p->boundary[4])/2.0;
			sub_cube2->boundary[5] = p->boundary[5];
			p->c[1] = sub_cube2;
			sub_cube2->parent = p;
			sub_cube2->level = level_parent + 1;
					
			Cube* sub_cube3 = new Cube();
			sub_cube3->id = p->id * 8 + 3; 
			sub_cube3->boundary[0] = p->boundary[0];
			sub_cube3->boundary[1] = p->boundary[0] + (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube3->boundary[2] = p->boundary[3] - (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube3->boundary[3] = p->boundary[3];
			sub_cube3->boundary[4] = p->boundary[5] - (p->boundary[5] - p->boundary[4])/2.0;
			sub_cube3->boundary[5] = p->boundary[5];
			p->c[2] = sub_cube3;
			sub_cube3->parent = p;
			sub_cube3->level = level_parent + 1;
			
			Cube* sub_cube4 = new Cube();
			sub_cube4->id = p->id * 8 + 4; 
			sub_cube4->boundary[0] = p->boundary[1] - (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube4->boundary[1] = p->boundary[1];
			sub_cube4->boundary[2] = p->boundary[2];
			sub_cube4->boundary[3] = p->boundary[2] + (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube4->boundary[4] = p->boundary[5] - (p->boundary[5] - p->boundary[4])/2.0;
			sub_cube4->boundary[5] = p->boundary[5];
			p->c[3] = sub_cube4;
			sub_cube4->parent = p;
			sub_cube4->level = level_parent + 1;
			
			Cube* sub_cube5 = new Cube();
			sub_cube5->id = p->id * 8 + 5; 
			sub_cube5->boundary[0] = p->boundary[1] - (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube5->boundary[1] = p->boundary[1];
			sub_cube5->boundary[2] = p->boundary[3] - (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube5->boundary[3] = p->boundary[3];
			sub_cube5->boundary[4] = p->boundary[4];
			sub_cube5->boundary[5] = p->boundary[4] + (p->boundary[5] - p->boundary[4])/2.0;
			p->c[4] = sub_cube5;
			sub_cube5->parent = p;
			sub_cube5->level = level_parent + 1;
			
			Cube* sub_cube6 = new Cube();
			sub_cube6->id = p->id * 8 + 6; 
			sub_cube6->boundary[0] = p->boundary[1] - (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube6->boundary[1] = p->boundary[1];
			sub_cube6->boundary[2] = p->boundary[2];
			sub_cube6->boundary[3] = p->boundary[2] + (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube6->boundary[4] = p->boundary[4];
			sub_cube6->boundary[5] = p->boundary[4] + (p->boundary[5] - p->boundary[4])/2.0;
			p->c[5] = sub_cube6;
			sub_cube6->parent = p;
			sub_cube6->level = level_parent + 1;
			
			Cube* sub_cube7 = new Cube();
			sub_cube7->id = p->id * 8 + 7; 
			sub_cube7->boundary[0] = p->boundary[0];
			sub_cube7->boundary[1] = p->boundary[0] + (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube7->boundary[2] = p->boundary[3] - (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube7->boundary[3] = p->boundary[3];
			sub_cube7->boundary[4] = p->boundary[4];
			sub_cube7->boundary[5] = p->boundary[4] + (p->boundary[5] - p->boundary[4])/2.0;
			p->c[6] = sub_cube7;
			sub_cube7->parent = p;
			sub_cube7->level = level_parent + 1;
			
			Cube* sub_cube8 = new Cube();
			sub_cube8->id = p->id * 8 + 8; 
			sub_cube8->boundary[0] = p->boundary[0];
			sub_cube8->boundary[1] = p->boundary[0] + (p->boundary[1] - p->boundary[0])/2.0;
			sub_cube8->boundary[2] = p->boundary[2];
			sub_cube8->boundary[3] = p->boundary[2] + (p->boundary[3] - p->boundary[2])/2.0;
			sub_cube8->boundary[4] = p->boundary[5] - (p->boundary[5] - p->boundary[4])/2.0;
			sub_cube8->boundary[5] = p->boundary[5];
			p->c[7] = sub_cube8;
			sub_cube8->parent = p;
			sub_cube8->level = level_parent + 1;
			
			//assiging their neghbors (left, right, up, down, front and back)
			sub_cube1->right = sub_cube6;
			sub_cube1->front = sub_cube7;
			sub_cube1->up = sub_cube8;

			sub_cube8->down = sub_cube1;
			sub_cube8->front = sub_cube3;
			sub_cube8->right = sub_cube4;

			sub_cube3->right = sub_cube2;
			sub_cube3->back = sub_cube8;
			sub_cube3->down = sub_cube7;

			sub_cube7->up = sub_cube3;
			sub_cube7->back = sub_cube1;
			sub_cube7->right = sub_cube5;

			sub_cube6->left = sub_cube1;
			sub_cube6->front = sub_cube5;
			sub_cube6->up = sub_cube4;

			sub_cube4->down = sub_cube6;
			sub_cube4->left = sub_cube8;
			sub_cube4->front = sub_cube2;

			sub_cube2->left = sub_cube3;
			sub_cube2->back = sub_cube4;
			sub_cube2->down = sub_cube5;

			sub_cube5->up = sub_cube2;
			sub_cube5->back = sub_cube6;
			sub_cube5->left = sub_cube7;

			//insering these new cubes within octree:
			octree.push_back(sub_cube1);
			octree.push_back(sub_cube2);
			octree.push_back(sub_cube3);
			octree.push_back(sub_cube4);
			octree.push_back(sub_cube5);
			octree.push_back(sub_cube6);
			octree.push_back(sub_cube7);
			octree.push_back(sub_cube8);

			dividing_parent_bodies_into_its_subcubes(p, body, octree);
		}
	}
}

#endif
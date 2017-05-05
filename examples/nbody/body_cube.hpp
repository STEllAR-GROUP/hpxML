//  Copyright (c) 2017 Zahra Khatami 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>

#include <hpx/runtime/serialization/vector.hpp>
#include <hpx/runtime/serialization/serialize.hpp>

#if !defined(BODY_CUBE_HPP_MAY_2017)
#define BODY_CUBE_HPP_MAY_2017

/*
Information regards to each body and cube with an octree:
*/

struct Cube;

//Body and Cube information:
struct Body
{
public:
    Cube* parent = nullptr;
    double location[3], 
    		velocity[3], 
    		force[3], 
    		mass;
    
    friend class hpx::serialization::access;
    template<typename Ar> void serialize(Ar &ar, unsigned){
    ar &parent &location &velocity &force &mass;}
};

struct Cube
{
public:
    int id, level;

    double mass = 0, 
    		boundary[6],
    		center_of_mass[3] = {0.0, 0.0, 0.0},
    		init_location[3] = {0.0, 0.0, 0.0}; //center_of_mass = init_location/mass

    std::vector<Cube*> cube_members;
    std::vector<Body*> body_members;

    //6 neighbors:
    Cube* up = nullptr;
    Cube* down = nullptr;
    Cube* right = nullptr;
    Cube* left = nullptr;
    Cube* front = nullptr;
    Cube* back = nullptr;  

    //8 sub_cubes:
    Cube* c[8];

    Cube* parent = nullptr;
    std::vector<Cube*> near_cells;
    std::vector<Cube*> remote_cells;  

    friend class hpx::serialization::access;  
    template<typename Ar> void serialize(Ar &ar, unsigned){
       	ar &id &level &parent &mass &boundary &center_of_mass &init_location 
       		&cube_members &body_members &up &down 
       		&right &left &front &back &c &parent &near_cells;}
};

#endif
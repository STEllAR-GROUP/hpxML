// Copyright (c) 2018 Gabriel Laberge
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <stdlib.h>
#include<ctime>
#include <vector>
#include<fstream>
#include <hpx/hpx_init.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <boost/range/irange.hpp>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <hpx/runtime/get_os_thread_count.hpp>
#include "headers/1_loop_level.h"
#include "headers/2_loop_level.h"
#include "headers/3_loop_level.h"
#include<string>
#include "headers/4_loop_level.h"

int hpx_main(int argc, char* argv[])
{
    // Initialization 
    int iterations=strtol(argv[2],NULL,10);
    float chunk_candidate=strtof(argv[3],NULL);

    if(std::strncmp(argv[1],"Nothing",7)==0){
        Nothing(iterations,chunk_candidate);
    }
    else if(std::strncmp(argv[1],"Swap",4)==0){
	Swap(iterations,chunk_candidate);    
    }
    else if(std::strncmp(argv[1],"Stream",6)==0){
	Stream(iterations,chunk_candidate);   
    }
    else if(std::strncmp(argv[1],"Matrix_Vector_Mult",18)==0){
	Matrix_Vector_Mult(iterations,chunk_candidate);    
    }
    else if(std::strncmp(argv[1],"Diadic_Prod",11)==0){
	Diadic_Prod(iterations,chunk_candidate);   
    }
    else if(std::strncmp(argv[1],"Cosine",6)==0){
	Cosine(iterations,chunk_candidate);   
    }
    else if(std::strncmp(argv[1],"Matrix_Matrix_Mult",20)==0){
        Matrix_Matrix_Mult(iterations,chunk_candidate);
    }
    else if(std::strncmp(argv[1],"Tensor_generator",16)==0){
        Tensor_generator(iterations,chunk_candidate);
    }
    else if(std::strncmp(argv[1],"Max",3)==0){
        Max(iterations,chunk_candidate);
    }
    else if(std::strncmp(argv[1],"Stencil",7)==0){
       Stencil(iterations,chunk_candidate);
    }
    else{ std::cout<<"Function not found"<<std::endl;}
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

// Copyright (c) 2018 Gabriel Laberge
//  Copyright (c) 2017 Zahra Khatami 
//  Copyright (c) 2016 David Pfander
//
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
#include "algorithms/dynamic_and_times/1_loop_level.h"
#include "algorithms/dynamic_and_times/2_loop_level.h"
#include "algorithms/dynamic_and_times/3_loop_level.h"
#include<string>
#include "algorithms/dynamic_and_times/4_loop_level.h"

int hpx_main(int argc, char* argv[])
{
    // Initialization 
    //
    int iterations=strtol(argv[2],NULL,10);
    std::vector<double> chunk_candidates(5);
    chunk_candidates[0]=0.5;chunk_candidates[1]=0.125;chunk_candidates[2]=0.03125;chunk_candidates[3]=0.0078125;chunk_candidates[4]=0.001953125;
    /*chunk_candidates[5]=0.5;;chunk_candidates[6]=0.5;/*chunk_candidates[7]=0.5;chunk_candidates[8]=0.005;chunk_candidates[9]=0.0025;*/
    srand(time(NULL));
    
    if(std::strncmp(argv[1],"Nothing",7)==0){    
        Nothing(iterations,chunk_candidates); 
    }   
    else if(std::strncmp(argv[1],"Swap",4)==0){
	Swap(iterations,chunk_candidates);    
    }
    else if(std::strncmp(argv[1],"Stream",6)==0){
	Stream(iterations,chunk_candidates);   
    }
    else if(std::strncmp(argv[1],"Matrix_Vector_Mult",18)==0){
	Matrix_Vector_Mult(iterations,chunk_candidates);    
    }
    else if(std::strncmp(argv[1],"Diadic_Prod",11)==0){
	Diadic_Prod(iterations,chunk_candidates);   
    }
    else if(std::strncmp(argv[1],"Cosine",6)==0){
	Cosine(iterations,chunk_candidates);   
    }

    else if(std::strncmp(argv[1],"Matrix_Matrix_Mult",20)==0){
        Matrix_Matrix_Mult(iterations,chunk_candidates);
    }
    else if(std::strncmp(argv[1],"Tensor_generator",16)==0){
        Tensor_generator(iterations,chunk_candidates);
    
    }
    else if(std::strncmp(argv[1],"Stencil",7)==0){
        Stencil(iterations,chunk_candidates);
    }
    else if(std::strncmp(argv[1],"Max",3)==0){
    	Max(iterations,chunk_candidates);
    }
    else{ std::cout<<"Function not found"<<std::endl;}

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

//  Copyright (c) 2018 Gabriel Laberge
//  Copyright (c) 2017 Zahra Khatami 
//  Copyright (c) 2016 David Pfander
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <map>
#include <hpx/hpx_init.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include "algorithms/dynamic_and_times/1_loop_level.h"
#include "algorithms/dynamic_and_times/2_loop_level.h"
#include "algorithms/dynamic_and_times/3_loop_level.h"
#include "algorithms/dynamic_and_times/4_loop_level.h"
std::map<char, void (*)(int, std::vector<double>, bool)> mymap;

void (*fctPtr1)(int, std::vector<double>, bool) = Nothing;
void (*fctPtr2)(int, std::vector<double>, bool) = Swap;
void (*fctPtr3)(int, std::vector<double>, bool) = Stream;
void (*fctPtr4)(int, std::vector<double>, bool) = Stencil;
void (*fctPtr5)(int, std::vector<double>, bool) = Matrix_Vector_Mult;
void (*fctPtr6)(int, std::vector<double>, bool) = Diadic_Prod;
void (*fctPtr7)(int, std::vector<double>, bool) = Cosine;
void (*fctPtr8)(int, std::vector<double>, bool) = Matrix_Matrix_Mult;
void (*fctPtr9)(int, std::vector<double>, bool) = Max;
void (*fctPtr10)(int, std::vector<double>, bool) = Tensor_generator;



int hpx_main(int argc, char* argv[])
{
    // Initialization 
    mymap.insert( std::pair<char, void (*)(int, std::vector<double>, bool)>("Nothing",fctPtr1) );
    //
    int iterations=strtol(argv[2],NULL,10);
    std::vector<double> chunk_candidates(5);
    chunk_candidates[0]=0.5;chunk_candidates[1]=0.125;chunk_candidates[2]=0.03125;chunk_candidates[3]=0.0078125;chunk_candidates[4]=0.001953125;
   /* 
    auto function=OPTIONS.find(argv[1]);
    if(function != OPTIONS.end()) {
        (*function)(iterations,chunk_candidates,true);
    }
    else{ std::cout<< "Function not found" <<std::endl;}

*/
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

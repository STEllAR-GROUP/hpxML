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
#include "algorithms/dynamic_and_times/all_functions.hpp"

int hpx_main(int argc, char* argv[])
{
    // Initialization 
    //
    Map_pointers OPTIONS;
    int iterations=strtol(argv[2], NULL, 10);
    std::vector<double> chunk_candidates(5);
    chunk_candidates[0] = 0.5; chunk_candidates[1] = 0.125; chunk_candidates[2] = 0.03125;
    chunk_candidates[3] = 0.0078125; chunk_candidates[4] = 0.001953125;

    Fill_map(OPTIONS);
   
    auto function=OPTIONS.find(argv[1]);
    if(function != OPTIONS.end()) {
        (*function).second(iterations, chunk_candidates, true);
    }
    else{ std::cout<< "Function not found" <<std::endl;}


    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

//  Copyright (c) 2018 Gabriel Laberge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include "1_loop_level.h"
#include "2_loop_level.h"
#include "3_loop_level.h"
#include "4_loop_level.h"

typedef std::map<std::string,void (*)(int, std::vector<double>, bool)> Map_pointers;

void Fill_map(Map_pointers& OPTIONS) {
    
    OPTIONS.insert( std::make_pair("Nothing", Nothing) );
    OPTIONS.insert( std::make_pair("Swap", Swap) );
    OPTIONS.insert( std::make_pair("Stream", Stream) );
    OPTIONS.insert( std::make_pair("Stencil", Stencil) );
    OPTIONS.insert( std::make_pair("Matrix_Vector_Mult", Matrix_Vector_Mult) );
    OPTIONS.insert( std::make_pair("Diadic_Prod", Diadic_Prod) );
    OPTIONS.insert( std::make_pair("Cosine", Cosine) );
    OPTIONS.insert( std::make_pair("Matrix_Matrix_Mult", Matrix_Matrix_Mult) );
    OPTIONS.insert( std::make_pair("Max", Max) );
    OPTIONS.insert( std::make_pair("Tensor_generator", Tensor_generator) );
}

//  Copyright (c) 2017 Zahra Khatami 
//  Copyright (c) 2016 David Pfander
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <stdlib.h>
#include<cmath>
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

void Tensor_generator(int iterations,std::vector<double> chunk_candidates) {
        
    int vector_size=iterations;
    auto time_range = boost::irange(0, iterations);
    
    std::vector<std::vector<double>> A(iterations*iterations,std::vector<double>(iterations*iterations,0));
    auto f = [&](int i){
        for(int j(0);j<vector_size;j++){
	    for(int k(0);k<vector_size;k++){
	        for(int l(0);l<vector_size;l++){
		    A[i*vector_size+j][k*vector_size+l]=i+j+k+l;		            
		}
	    }
	}
    };
    
   std::cout<<vector_size<<" "<<hpx::get_os_thread_count()<<" ";

    double t_chunk=0.0;
    double Nrep=10;
    double mean_time;
    double elapsed_time;
    for (int i(0);i<chunk_candidates.size();i++){
	mean_time=0;
	for(int j(0);j<Nrep+1;j++){
	    if(chunk_candidates[i]*vector_size>1){
	    t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
            elapsed_time= mysecond() - t_chunk;
	    }
	    else{
	    t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
            elapsed_time= mysecond() - t_chunk;
	    }
	    if(j!=0){
	        mean_time+=elapsed_time;
 	    }
	}
	std::cout<<mean_time/Nrep<<" ";
    }
    std::cout<<""<<std::endl;
}

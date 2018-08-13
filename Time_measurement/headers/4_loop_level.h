//  Copyright (c) 2018 Gabriel Laberge
//
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

void Tensor_generator(int iterations,float chunk_candidate) {
        
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

    double t_chunk=0.0;
    double Nrep=10;
    double mean_time;
    double elapsed_time;
    std::vector<double> times(Nrep);
    mean_time=0;
    for(int j(0);j<Nrep+1;j++){
        if(chunk_candidate*vector_size>1){
            t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidate)), time_range.begin(), time_range.end(), f);
            elapsed_time= mysecond() - t_chunk;
	}
        else{
	    t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
            elapsed_time= mysecond() - t_chunk;
	}
	if(j!=0){
	    times[j-1]=elapsed_time;
 	}
    }
    std::cout<<Mean(times)<<","<<Var(times)<<std::endl;


}

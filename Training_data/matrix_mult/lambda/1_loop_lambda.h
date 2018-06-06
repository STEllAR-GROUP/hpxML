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



double mysecond()
{
    return hpx::util::high_resolution_clock::now() * 1e-9;
}

//lambda1 C[i]=rand*(A[i]+B[1])
template<typename T>
void lambda1_1(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    auto f = [&](int i) {
        T result=0.0;
	result+=A[i];
	result+=B[i];
	result*=rand()%10+1;
	C[i]=result;
    };
  
  double t_chunk=0.0;
   file<<vector_size<<" "<<"1 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    
}



//lambda2 swap A and B
template<typename T>
void lambda1_2(std::vector<T>& A, std::vector<T>& B,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    
    auto f=[&](int i){
        T container=A[i];
        A[i]=B[i];
        B[i]=container;
    };
  
  
  
    double t_chunk=0.0;
    file<<vector_size<<" "<<"1 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    
}



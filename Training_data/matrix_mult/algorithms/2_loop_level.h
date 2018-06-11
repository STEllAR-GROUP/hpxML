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



void Max_Sum_Row(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
    
     
    int vector_size=iterations;
    int matrix_size=iterations*iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(vector_size);
    vector_generator(A,matrix_size,10,100);
    vector_generator(B,matrix_size,10,100);   

    auto f = [&](int i) {
	double result1=0.0;
        double result2=0.0;
        for(int k(0);k<vector_size;k++){
	    result1+=A[vector_size*i+k];
	    result2+=B[vector_size*i+k];
	}
	C[i]=std::max(result1,result2);

    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    

}
    


void Cum_Sum(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
    
         
    int vector_size=iterations;
    auto time_range = boost::irange(0, vector_size); 
    std::vector<double> A;
    std::vector<double> B(vector_size);
    vector_generator(A,vector_size,10,100);
    auto f=[&](int i){
        double result=0;
	for(int j(0);j<i;j++){
		result+=A[i];
	}
	B[i]=result;
    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
}


void Factorial(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
    
     
    int vector_size=iterations;
    auto time_range = boost::irange(0, vector_size); 
    std::vector<double> A;
    std::vector<double> B(vector_size);
    vector_generator(A,vector_size,10,100);  
    auto f=[&](int i){
        double result=1;
	for(int j(2);j<A[i];j++){
		result*=j;
	}
	B[i]=result;
    };


   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    

}


void Matrix_Vector_Mult(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
   
    int vector_size=iterations;
    int matrix_size=iterations*iterations;
    auto time_range = boost::irange(0, iterations);
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(matrix_size);
    vector_generator(A,matrix_size,10,100);
    vector_generator(B,matrix_size,10,100);  
    auto f=[&](int i){
    	if (i % 4 ==0){
	    double result1=0.0;
	    double result2=0.0;
	    double result3=0.0;
	    double result4=0.0;

	    for (int k=0;k<vector_size;k++){
	        result1+=A[i*vector_size+k]*B[k];
		result2+=A[(i+1)*vector_size+k]*B[k];
		result3+=A[(i+2)*vector_size+k]*B[k];
		result4+=A[(i+3)*vector_size+k]*B[k];
	    }
	    C[i]=result1;
	    C[i+1]=result2;
	    C[i+2]=result3;
	    C[i+3]=result4;
	}
    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    
}

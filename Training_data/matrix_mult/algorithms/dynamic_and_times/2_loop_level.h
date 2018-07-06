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
#include <cmath>

int factorial(int n){
    if(n==0){
        return 1;
    }
    else{
        int result=1;
        for(int i(0);i<n;i++){
	    result*=i;
	}
        return result;
    }
}

void Max_Sum_Row(int iterations,std::vector<double> chunk_candidates) {
     
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
   std::cout<<vector_size<<" "<<hpx::get_os_thread_count()<<" ";
    double t_chunk=0.0;
    double N_mean=10;
    double mean_time;
    for (int i(0);i<chunk_candidates.size();i++){
	mean_time=0;
	for(int j(0);j<N_mean;j++){
	t_chunk=mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
        mean_time+= mysecond() - t_chunk;
	}
	std::cout<<mean_time/N_mean<<" ";
    }
    std::cout<<""<<std::endl;
      

}
    
void Matrix_Vector_Mult(int iterations,std::vector<double> chunk_candidates) {
   
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
   
   std::cout<<vector_size<<" "<<hpx::get_os_thread_count()<<" ";
    double t_chunk=0.0;
    double N_mean=10;
    double mean_time;
    for (int i(0);i<chunk_candidates.size();i++){
	mean_time=0;
	for(int j(0);j<N_mean;j++){
	t_chunk=mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
        mean_time+= mysecond() - t_chunk;
	}
	std::cout<<mean_time/N_mean<<" ";
    }
    std::cout<<""<<std::endl;
    
    
}



void Diadic_Prod(int iterations,std::vector<double> chunk_candidates) {
   
    int vector_size=iterations;
    int matrix_size=iterations*iterations;
    auto time_range = boost::irange(0, iterations);
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(matrix_size);
    vector_generator(A,vector_size,10,100);
    vector_generator(B,vector_size,10,100);  
    auto f=[&](int i){
	for(int j(0);j<vector_size;j++){
	    C[vector_size*i+j]=A[i]*B[j];
	}
    };
   
   std::cout<<vector_size<<" "<<hpx::get_os_thread_count()<<" ";
    double t_chunk=0.0;
    double N_mean=10;
    double mean_time;
    for (int i(0);i<chunk_candidates.size();i++){
	mean_time=0;
	for(int j(0);j<N_mean;j++){
	t_chunk=mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
        mean_time+= mysecond() - t_chunk;
	}
	std::cout<<mean_time/N_mean<<" ";
    }
    std::cout<<""<<std::endl;
    
}
 void Cosine(int iterations,std::vector<double> chunk_candidates) {
   
    int vector_size=iterations;
    auto time_range = boost::irange(0, iterations);
    std::vector<double> A,B(vector_size,0);
    vector_generator(A,vector_size,10,1000);
    auto f=[&](int i){
	for(int n(0);n<100;n++){
	    B[i]+=std::pow(-1,n)/factorial(2*n)*std::pow(A[i],2*n);
	}
    };
   
   std::cout<<vector_size<<" "<<hpx::get_os_thread_count()<<" ";
    double t_chunk=0.0;
    double N_mean=10;
    double mean_time;
    for (int i(0);i<chunk_candidates.size();i++){
	mean_time=0;
	for(int j(0);j<N_mean;j++){
	t_chunk=mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
        mean_time+= mysecond() - t_chunk;
	}
	std::cout<<mean_time/N_mean<<" ";
    }
    std::cout<<""<<std::endl;
    
}
   

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


//random assigment of rows of A and B
template<typename T>
void lambda2_1(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    auto f = [&](int i) {
	T result1=0.0;
        T result2=0.0;
        for(int k(0);k<vector_size;k++){
	    result1+=A[vector_size*i+k];
	    result2+=B[vector_size*i+k];
	}
	C[vector_size*i+0]=std::max(result1,result2);
	C[vector_size*i+1]=std::min(result1,result2);
	C[vector_size*i+1]=result1*result2;
	C[vector_size*i+2]=(result1+result2)*(rand()*10+1);

    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    

}
    


//random loop Cummulative sum
template<typename T>
void lambda2_2(std::vector<T>& A, std::vector<T>& B,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    auto f=[&](int i){
        T result=0;
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
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
}

//random loop factorial point per point
template<typename T>
void lambda2_3(std::vector<T>& A, std::vector<T>& B,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 

    auto f=[&](int i){
        T result=1;
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
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;
    

}

//random loop matrix-vector multiplication
template<typename T>
void lambda2_4(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 

    auto f=[&](int i){
    	if (i % 4 ==0){
	    T result1=0.0;
	    T result2=0.0;
	    T result3=0.0;
	    T result4=0.0;

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
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;
    

}
/*
//Matrix Matrix multiplication A*B=C//
template<typename T>
void test_data_matrix(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,bool show_error,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    auto f = [&](int i) {
        if(i % 4 == 0) {
            for (int j = 0; j < vector_size; j += 4) {

                T result1 = 0.0;
                T result2 = 0.0;
                T result3 = 0.0;
                T result4 = 0.0;

                T result5 = 0.0;
                T result6 = 0.0;
                T result7 = 0.0;
                T result8 = 0.0;

                T result9 = 0.0;
                T result10 = 0.0;
                T result11 = 0.0;
                T result12 = 0.0;

                T result13 = 0.0;
                T result14 = 0.0;
                T result15 = 0.0;
                T result16 = 0.0;

                for (int k = 0; k < vector_size; k++) {                  

                    result1 += A[i * vector_size + k] * B[j * vector_size + k];
                    result2 += A[i * vector_size + k] * B[(j + 1) * vector_size + k];
                    result3 += A[i * vector_size + k] * B[(j + 2) * vector_size + k];
                    result4 += A[i * vector_size + k] * B[(j + 3) * vector_size + k];

                    result5 += A[(i + 1) * vector_size + k] * B[j * vector_size + k];
                    result6 += A[(i + 1) * vector_size + k] * B[(j + 1) * vector_size + k];
                    result7 += A[(i + 1) * vector_size + k] * B[(j + 2) * vector_size + k];
                    result8 += A[(i + 1) * vector_size + k] * B[(j + 3) * vector_size + k];

                    result9 += A[(i + 2) * vector_size + k] * B[j * vector_size + k];
                    result10 += A[(i + 2) * vector_size + k] * B[(j + 1) * vector_size + k];
                    result11 += A[(i + 2) * vector_size + k] * B[(j + 2) * vector_size + k];
                    result12 += A[(i + 2) * vector_size + k] * B[(j + 3) * vector_size + k];

                    result13 += A[(i + 3) * vector_size + k] * B[j * vector_size + k];
                    result14 += A[(i + 3) * vector_size + k] * B[(j + 1) * vector_size + k];
                    result15 += A[(i + 3) * vector_size + k] * B[(j + 2) * vector_size + k];
                    result16 += A[(i + 3) * vector_size + k] * B[(j + 3) * vector_size + k];
                }
                
                C[i * vector_size + j] = result1;
                C[i * vector_size + (j + 1)] = result2;
                C[i * vector_size + (j + 2)] = result3;
                C[i * vector_size + (j + 3)] = result4;

                C[(i + 1) * vector_size + j] = result5;
                C[(i + 1) * vector_size + (j + 1)] = result6;
                C[(i + 1) * vector_size + (j + 2)] = result7;
                C[(i + 1) * vector_size + (j + 3)] = result8;

                C[(i + 2) * vector_size + j] = result9;
                C[(i + 2) * vector_size + (j + 1)] = result10;
                C[(i + 2) * vector_size + (j + 2)] = result11;
                C[(i + 2) * vector_size + (j + 3)] = result12;

                C[(i + 3) * vector_size + j] = result13;
                C[(i + 3) * vector_size + (j + 1)] = result14;
                C[(i + 3) * vector_size + (j + 2)] = result15;
                C[(i + 3) * vector_size + (j + 3)] = result16;
            }
        }
    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;

}*/


//  Copyright (c) 2017 Zahra Khatami 
//  Copyright (c) 2016 David Pfander
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <stdlib.h>
#include <vector>
#include <hpx/hpx_init.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <boost/range/irange.hpp>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
 
#define lambda_inner_iteration 0                                                                                 

namespace hpx { namespace parallel {struct adaptive_chunk_size {}; } }


double random_double(double min,double max){
    return (min+1)+(((double) rand())/(double) RAND_MAX)*(max-(min+1));
}

template<typename T>
void vector_generator(std::vector<T> &A,int size,double min,double max){
    for(std::size_t r = 0; r < size; r++) {
        A.push_back(random_double(min,max));
    }
}

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
        for(int k(0);k<lambda_inner_iteration;k++){
	    result1+=A[vector_size*i+k];
	    result2+=B[vector_size*i+k];
	}
	C[i]=std::max(result1,result2);

    };
   //feature extraction Max_Sum_Row
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
    
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

	    for (int k=0;k<lambda_inner_iteration;k++){
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
    //feature extraction Matrix_Vector_Mult
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
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
	for(int j(0);j<lambda_inner_iteration;j++){
	    C[vector_size*i+j]=A[i]*B[j];
	}
    };
   //feature extraction Diadic_Prod
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
    
}
 void Cosine(int iterations,std::vector<double> chunk_candidates) {
   
    int vector_size=iterations;
    auto time_range = boost::irange(0, iterations);
    std::vector<double> A,B(vector_size,0);
    vector_generator(A,vector_size,10,1000);
    auto f=[&](int i){
	for(int j(0);j<100;j++){
	    A[i]+=std::pow(-1,j)/factorial(2*j)*std::pow(A[i],2*j);
	}
    };
  //feature extraction Cosine
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
    


}

int hpx_main(int argc, char* argv[])
{

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}
   

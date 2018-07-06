//  Copyright (c) 250          00   17 Zahra Khatami 
//  Copyright (c) 250          00   16 David Pfander
//
//  Distributed under the Boost Software License, Version 1.50          00   . (See accompanying
//  file LICENSE_1_50          00   .txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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

#define lambda_inner_iteration 0                                                                                    

namespace hpx { namespace parallel {struct adaptive_chunk_size {}; } }


double random_double(double min,double max){
    return (min+1)+(((double) rand())/(double) RAND_MAX)*(max-(min+1));
}

template<typename T>
void vector_generator(std::vector<T> &A,int size,double min,double max){
    for(std::size_t r = 0 ; r < size; r++) {
        A.push_back(random_double(min,max));
    }
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////
void Rand_Pond_Sum(int iterations,std::vector<double> chunk_candidates) {
  
    int vector_size=iterations;
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(vector_size);
    vector_generator(A,vector_size,10,100);
    vector_generator(B,vector_size,10,100);

    auto time_range = boost::irange(0 , vector_size); 
    auto f = [&](int i) {
        double result=0.0;
	result+=(rand()%10+1)*A[i];
	result+=(rand()%10+1)*B[i];
	C[i]=result;
};

 //feature extraction Rand_Pond_Sum
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
  
}


/////////////////////////////////////////////////////////////////////////////////////////////////
void Swap(int iterations,std::vector<double> chunk_candidates) {
      
  int vector_size=iterations;
  std::vector<double> A;
  std::vector<double> B;
  vector_generator(A,vector_size,10,100);
  vector_generator(B,vector_size,10,100);

    auto time_range = boost::irange(0, vector_size); 
    auto f=[&](int i){
        double container=A[i];
        A[i]=B[i];
        B[i]=container;
    };
  
  //feature extraction Swap
// hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
}
  


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Finite_Diff_Step(int iterations,std::vector<double> chunk_candidates) {
      
    int vector_size=iterations;
    std::vector<double> A;
    std::vector<double> B(vector_size);
    vector_generator(A,vector_size,10,100);

    auto time_range = boost::irange(0, vector_size); 
    
    auto f=[&](int i){
        if(i==0){
	    B[i]=(A[i]+A[i+1])/2;
	}
	else if(i==(vector_size-1)){
	    B[i]=(A[i]+A[i-1])/2;
	}
	else {
	    B[i]=(A[i-1]+A[i]+A[i+1])/2;
	}
    };

  //feature extraction Finite_Diff_Step
// hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////// 	
void Stream(int iterations,std::vector<double> chunk_candidates) {
      
    int vector_size=iterations;
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    vector_generator(A,vector_size,10,100);
    vector_generator(B,vector_size,10,100);
    vector_generator(C,vector_size,10,100);

    auto time_range = boost::irange(0, vector_size); 
    double k(14);
    auto f=[&](int i){
        C[i]=A[i];
	B[i]=k*C[i];
	C[i]=A[i]+B[i];
	A[i]=B[i]+k*C[i];
    };

     //feature extraction Stream
// hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
}

int hpx_main(int argc, char* argv[])
{

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

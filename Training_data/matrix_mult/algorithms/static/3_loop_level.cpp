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


void Matrix_Matrix_Mult(int iterations,std::vector<double> chunk_candidates) {
         

    int vector_size=iterations;
    int matrix_size=iterations*iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(matrix_size);
    vector_generator(A,matrix_size,10,100);
    vector_generator(B,matrix_size,10,100);   

    auto f = [&](int i) {
        if(i % 4 == 0) {
            for (int j = 0; j < lambda_inner_iteration; j += 4) {

                double result1 = 0.0;
                double result2 = 0.0;
                double result3 = 0.0;
                double result4 = 0.0;

                double result5 = 0.0;
                double result6 = 0.0;
                double result7 = 0.0;
                double result8 = 0.0;

                double result9 = 0.0;
                double result10 = 0.0;
                double result11 = 0.0;
                double result12 = 0.0;

                double result13 = 0.0;
                double result14 = 0.0;
                double result15 = 0.0;
                double result16 = 0.0;

                for (int k = 0; k < lambda_inner_iteration; k++) {                  

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

   //feature extraction Matrix_Matrix_Mult
//  hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);
  

}

void Max(int iterations,std::vector<double> chunk_candidates) {
         
    int vector_size=iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    vector_generator(A,vector_size*100*100,10,1000);   
    std::vector<double> max(vector_size,0);
    auto f = [&](int i) {
	for(int j(0);j<100;j++){
	    for(int k(0);k<100;k++){
	        if(A[i+vector_size*j+vector_size*100*k]>max[i]){
		    max[i]=max[i];
		}
	    }
	}	    
    };
    //feature extraction Max
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

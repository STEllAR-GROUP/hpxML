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

// finite element shape functions
double shape_function(int index,double eta){
    if(index==0){
        return (1-eta)/2;
    }
    else if(index==1){
        return (1+eta)/2;
    }
    else if(index==2){
        return 1-eta*eta;
    }
    else{ return 0;}
}

void Finite_Element_K(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
        
    int n_elements=iterations;
    int vector_size=iterations;
    auto time_range = boost::irange(0, n_elements);
    
    std::vector<double> A;
    std::vector<std::vector<int>> connect;
    std::vector<double> weights,gauss;
    std::vector<double> F(vector_size,0);
    vector_generator(A,vector_size,10,100);  
    weights[0]=5/9;weights[1]=8/9;weights[2]=5/9;
    gauss[0]=-0.77459;gauss[1]=0;gauss[2]=0.77459;
    std::vector<int> add;
    for(int i(0);i<n_elements;i++){
        add[0]=i;add[1]=i+1;
	add[2]=n_elements+1+i;
    }


    auto f = [&](int i){
	double result=0.0;
	for(int j(0);j<3;j++){
            result=0.0;
	    for(int k(0);k<3;k++){
                result+=weights[k]*A[i]*shape_function(j,gauss[k]);
	    }
	    F[connect[i][j]]=result;
	}
	
    };
    


   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"3 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;

}

void Triples(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
 
    int vector_size=iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<int> A;
    std::vector<int> B;
    std::vector<int> C;
    srand(1);
    for(int i(0);i<vector_size;i++){
        A.push_back(rand()%10+5);
        B.push_back(rand()%10+5);
        C.push_back(rand()%10+5);

    }

    std::vector<std::vector<int>> D;
    std::vector<int> add;
    auto f=[&](int i){
        for(int j(0);j<vector_size;j++){
	     for(int k(0);k<vector_size;k++){
	         if(A[i]==B[j] && B[j]==C[k]){
	             add.push_back(i);
		     add.push_back(j);
		     add.push_back(k);
		     D.push_back(add);
		     add.clear();
                 }
	     }
        }
    };	


   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"3 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;

}
void Cum_Product_Row(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
    
    int vector_size=iterations;
    int matrix_size=iterations*iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    std::vector<double> B(matrix_size);
    vector_generator(A,matrix_size,10,100);   
    
    auto f = [&](int i) {
	double result=0;
        for(int j(0);j<vector_size;j++){
	    result=0;
	    for(int k(0);k<j;k++){
	        result*=A[vector_size*i+k];
	    }
	    B[vector_size*i+j]=result;
	}
    };

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"3 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;

}


void Matrix_Matrix_Mult(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
         

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
            for (int j = 0; j < vector_size; j += 4) {

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
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
    }
    file<<""<<std::endl;

}



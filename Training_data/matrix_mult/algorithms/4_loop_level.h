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
    int matrix_size=iterations;
    auto time_range = boost::irange(0, n_elements);
    
    std::vector<double> A;
    std::vector<std::vector<int>> connect;
    std::vector<double> weights,gauss;
    std::vector<double> K((2*n_element+1)*(2n_element+1),0);
    vector_generator(A,matrix_size,10,100);  
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
	    for(int k(0);k<3;k++){
                result=0.0;
		for (int g(0);g<3;g++){
		    result+=weights[g]*A[i]*shape_function(j,gauss[g])*shape_function(k,guauss[g]);
		}
	        K[n_element*connect[i,j]+connect[i.k];
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

void Finite_Element_K(int iterations,std::vector<double> chunk_candidates,std::ofstream& file) {
        
    int vector_size=iterations;
    auto time_range = boost::irange(0, iterations);
    
    std::vector<std::vector<double>> A(iterations*iterations,vector<double>(iterations*iterations,0));
    srand(1)
    auto f = [&](int i){
        for(int j(0);j<vector_size;j++){
	    for(int k(0);k<vector_size;j++){
	        for(int l(0);l<iterations;l++){
		    A[i*vector_size+j][k*vector_size+l]=rand()%1000+10;		            }
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


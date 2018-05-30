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


//std::vector<int> std_range(int vector_size){
 //   std::vector<int> range;
  //  for (int i(0);i<vector_size;i++){
   //     range.push_back(i);
   // }
//}


//Matrix vector multiplication A*b=c
template<typename T>
void data_matrice_vector(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size) {
  
    auto time_range = boost::irange(0, vector_size);
//    auto time_range=std_range(vector_size); 
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

    // Parrallel execution
    double t_origin = mysecond();

    hpx::parallel::for_each(hpx::parallel::execution::par, time_range.begin(), time_range.end(), f);

    double elapsed_origin = mysecond() - t_origin;

    // Dynamic chunk size
    double t_chunk = mysecond();
    
    hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size()), time_range.begin(), time_range.end(), f);

    double elapsed_chunk = mysecond() - t_chunk;

    //Prefetching dictance:
    //std::size_t pref_dist_fac = 2;
    //auto policy = hpx::parallel::par;

    //double t_prefetch = mysecond();

    //hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, pref_dist_fac, A, B, C), time_range.begin(), time_range.end(), f);

    //double elapsed_prefetch = mysecond() - t_prefetch;

    
    // Printing results
    std::cout<<"Execution time for parralel policy : "<<elapsed_origin<<std::endl;
    std::cout<<"Execution time for dynamic_chunk_size() : "<<elapsed_chunk<<std::endl;
    //std::cout<<"Execution time for make_prefetcher_policy() : "<<elapsed_prefetch<<std::endl;

}



//Matrix Matrix multiplicaiton A*B=C//
template<typename T>
void data_matrices(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size) {
    
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

    //Sequential execution
    double t_seq = mysecond();

    hpx::parallel::for_each(hpx::parallel::execution::seq, time_range.begin(), time_range.end(), f);

    double elapsed_seq = mysecond() - t_seq;

    // Parralel execution
    double t_par = mysecond();

    hpx::parallel::for_each(hpx::parallel::execution::par, time_range.begin(), time_range.end(), f);

    double elapsed_par = mysecond() - t_par;

    // Dynamic chunk size
    double t_chunk = mysecond();
    
    hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size()), time_range.begin(), time_range.end(), f);

    double elapsed_chunk = mysecond() - t_chunk;

    //Prefetching dictance:
    //std::size_t pref_dist_fac = 2;
    //auto policy = hpx::parallel::par;

    //double t_prefetch = mysecond();

    //hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, pref_dist_fac, A, B, C), time_range.begin(), time_range.end(), f);

    //double elapsed_prefetch = mysecond() - t_prefetch;

    
    // Printing results
    std::cout<<"Execution time for sequential policy : "<<elapsed_seq<<std::endl;
    std::cout<<"Execution time for parralel policy : "<<elapsed_par<<std::endl;
    std::cout<<"Execution time for dynamic_chunk_size() : "<<elapsed_chunk<<std::endl;
    //std::cout<<"Execution time for make_prefetcher_policy() : "<<elapsed_prefetch<<std::endl;

}



//Determinant of A//
template<typename T>
void data_determinant(std::vector<T>& A,std::vector<T> Determinant,int vector_size) {
    
    auto time_range = boost::irange(0, vector_size);
//    auto time_range=std_range(vector_size); 
    auto f=[&](int i){
        T result1=1;
	T result2=1;
	for(int j=0;j<vector_size;j++){
	    result1*=A[j*vector_size+(j+i)%vector_size];
	    result2*=A[(vector_size-1-j)*vector_size+(j+i)%vector_size];
	}
	Determinant[i]+=result1;
	Determinant[i]-=result2;
    };

    // Parrallel execution
    double t_origin = mysecond();

    hpx::parallel::for_each(hpx::parallel::execution::par, time_range.begin(), time_range.end(), f);

    double elapsed_origin = mysecond() - t_origin;

    // Dynamic chunk size
    double t_chunk = mysecond();
    
    hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size()), time_range.begin(), time_range.end(), f);

    double elapsed_chunk = mysecond() - t_chunk;

    //Prefetching dictance:
    //std::size_t pref_dist_fac = 2;
    //auto policy = hpx::parallel::par;

    //double t_prefetch = mysecond();

    //hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, pref_dist_fac, A, B, C), time_range.begin(), time_range.end(), f);

    //double elapsed_prefetch = mysecond() - t_prefetch;

    
    // Printing results
    std::cout<<"Execution time for parralel policy : "<<elapsed_origin<<std::endl;
    std::cout<<"Execution time for dynamic_chunk_size() : "<<elapsed_chunk<<std::endl;
    //std::cout<<"Execution time for make_prefetcher_policy() : "<<elapsed_prefetch<<std::endl;

}



//Stencil (A,B,C)//
template<typename T>
void data_stencil(std::vector<T>& A,std::vector<T>& B,std::vector<T>& C,int vector_size) {
    
    auto time_range = boost::irange(0, vector_size);
  //  auto time_range=std_range(vector_size); 
    T scalar(3);

    auto f=[&](int i){
        C[i]=A[i];
    	B[i]=scalar*C[i];
	C[i]=A[i]+B[i];
	A[i]+B[i]+scalar*C[i];
    };

    // Parrallel execution
    double t_origin = mysecond();

    hpx::parallel::for_each(hpx::parallel::execution::seq, time_range.begin(), time_range.end(), f);

    double elapsed_origin = mysecond() - t_origin;

    // Dynamic chunk size
    double t_chunk = mysecond();
    
    hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size()), time_range.begin(), time_range.end(), f);

    double elapsed_chunk = mysecond() - t_chunk;

    //Prefetching dictance:
    //std::size_t pref_dist_fac = 2;
    //auto policy = hpx::parallel::par;

    //double t_prefetch = mysecond();

    //hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, pref_dist_fac, A, B, C), time_range.begin(), time_range.end(), f);

    //double elapsed_prefetch = mysecond() - t_prefetch;

    
    // Printing results
    std::cout<<"Execution time for parralel policy : "<<elapsed_origin<<std::endl;
    std::cout<<"Execution time for dynamic_chunk_size() : "<<elapsed_chunk<<std::endl;
    //std::cout<<"Execution time for make_prefetcher_policy() : "<<elapsed_prefetch<<std::endl;

}



int hpx_main(int argc, char* argv[])
{
    // Initialization
    int vector_size=500;
    std::size_t size_of_mat = vector_size * vector_size;
    std::vector<double> A(size_of_mat, 0.0);
    std::vector<double> B(size_of_mat, 0.0);
    std::vector<double> C(size_of_mat, 0.0);

    for(std::size_t r = 0; r < size_of_mat; r++) {
        srand(r);
        A[r] = (r + 1) * (r + 10) * (rand() % 10 + 1);
        B[r] = (r + 1) * (r + 10) * (rand() % 10 + 1);
        C[r] = (r + 1) * (r + 10) * (rand() % 10 + 1);
    }

    data_matrices(A, B, C,vector_size);
  
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

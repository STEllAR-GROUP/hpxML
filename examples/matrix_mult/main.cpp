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
#include <boost/range.hpp>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/parallel/executors/sequential_execution_wrapper.hpp>
#include <hpx/parallel/seq_or_par.hpp>
#include <hpx/parallel/chunk_size_determination.hpp>
#include <hpx/parallel/prefetching_distance_determination.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <hpx/parallel/executors/adaptive_chunk_size.hpp>


#define vector_size 200


double mysecond()
{
    return hpx::util::high_resolution_clock::now() * 1e-9;
}

template<typename T>
void comparing_perfromances(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C) {

    auto time_range = boost::irange(0, 200);
    
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

    ////////////////////////////////////////////////////////////////////////
    // [1] Original code implemantion with HPX
    double t_origin = mysecond();

    hpx::parallel::for_each(hpx::parallel::par, time_range.begin(), time_range.end(), f);

    double elapsed_origin = mysecond() - t_origin;

    ////////////////////////////////////////////////////////////////////////
    // [2] Efficient chunk size
    double t_chunk = mysecond();
    
	hpx::parallel::for_each(hpx::parallel::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);

    double elapsed_chunk = mysecond() - t_chunk;

    ////////////////////////////////////////////////////////////////////////
    // [3] Prefetching:
    std::size_t pref_dist_fac = 2;
    auto policy = hpx::parallel::par;

    double t_prefetch = mysecond();

	
	hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, pref_dist_fac, A, B, C), time_range.begin(), time_range.end(), f);

    double elapsed_prefetch = mysecond() - t_prefetch;

    ////////////////////////////////////////////////////////////////////////
    // Printing results

    double byte = vector_size * (16 + 
        (vector_size * ((7 + 3 * 8) + (8 + 3 * 9) + (8 + 3 * 9) + (8 + 3 * 9))) + 
        ((3 + 3 * 4) + (4 + 3 * 5) + (4 + 3 * 5) + (4 + 3 * 5)));

    // MB
    std::cout << std::left << "rate_origin = ";
    std::cout << std::left << (1.0E-09 * (byte * sizeof(double)) / (elapsed_origin)) << " [GB/s]";
    std::cout << std::left << "\nrate_chunk = ";
    std::cout << std::left << (1.0E-09 * (byte * sizeof(double)) / (elapsed_chunk)) << " [GB/s]";
    std::cout << std::left << "\nrate_prefetching = ";
    std::cout << std::left << (1.0E-09 * (byte * sizeof(double)) / (elapsed_prefetch)) << " [GB/s]";
    std::cout << std::endl;
}

int hpx_main(int argc, char* argv[])
{
    // Initialization
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

    comparing_perfromances(A, B, C);
  
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

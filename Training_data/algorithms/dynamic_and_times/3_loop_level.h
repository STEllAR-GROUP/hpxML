//  Copyright (c) 2017 Zahra Khatami 
//  Copyright (c) 2016 David Pfander
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include<ctime>
#include <vector>
#include<fstream>
#include<cmath>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/hpx_init.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <boost/range/irange.hpp>

double Mean(std::vector<double> times)
{
	double mean = 0;
	for(int i(0); i < times.size(); i++)
    {
		mean += times[i];
	}
	return mean/times.size();
}

double var(std::vector<double> times)
{
	double var = 0;
	double mean = Mean(times);
	for (int i(0); i < times.size(); i++)
    {
		var += std::pow(mean - times[i], 2);
	}
	return var/((times.size() - 1)*std::pow(mean, 2))*100;
}



void Matrix_Matrix_Mult(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features)
{
         
    int vector_size = iterations;
    int matrix_size = iterations*iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C(matrix_size);
    vector_generator(A,matrix_size, 10, 100);
    vector_generator(B,matrix_size, 10, 100);   

    auto f = [&](int i) 
    {
        if(i % 4 == 0) 
        {
            for (int j = 0; j < vector_size; j += 4) 
            {

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

                for (int k = 0; k < vector_size; k++) 
                {                  

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
    if (Print_dynamic_features) 
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() <<" ";
    }

    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    double mean_time;
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
	mean_time = 0;
	for(int j(0); j < Nrep + 1; j++)
    {
	    if(chunk_candidates[i]*vector_size > 1)
        {
	        t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
            elapsed_time = mysecond() - t_chunk;
	    }
	    else{
	        t_chunk = mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
            elapsed_time = mysecond() - t_chunk;
	    }
	    if(j != 0)
        {
	        mean_time += elapsed_time;
 	    }
	}
	std::cout<< mean_time/Nrep <<" ";
    }
    std::cout<< "" <<std::endl;

}
void Max(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features)
{
         
    int vector_size = iterations;
    auto time_range = boost::irange(0, vector_size);
    std::vector<double> A;
    vector_generator(A,vector_size*100*100, 10, 1000);   
    std::vector<double> max(vector_size, 0);
    auto f = [&](int i) 
    {
        for(int j(0); j < 100; j++)
        {
            for(int k(0); k < 100; k++)
            {
                if(A[i+vector_size*j+vector_size*100*k] > max[i])
                {
                max[i]=max[i+vector_size*j+vectr_size*100*k];
                }
            }
	    }	    
    };
    if (Print_dynamic_features) 
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() <<" ";
    }

    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    double mean_time;
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
	mean_time = 0;
	for(int j(0); j < Nrep + 1; j++)
    {
	    if(chunk_candidates[i]*vector_size > 1)
        {
	        t_chunk=mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);
            elapsed_time = mysecond() - t_chunk;
	    }
	    else{
	        t_chunk = mysecond();
            hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
            elapsed_time = mysecond() - t_chunk;
	    }
	    if(j != 0)
        {
	        mean_time += elapsed_time;
 	    }
	}
	std::cout<< mean_time/Nrep <<" ";
    }
    std::cout<< "" <<std::endl;

}

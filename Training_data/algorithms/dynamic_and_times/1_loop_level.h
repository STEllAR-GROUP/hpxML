//  Copyright (c) 2018 Gabriel Laberge 
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <vector>
#include <cmath>
#include <hpx/hpx_init.hpp>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <boost/range/irange.hpp>

using namespace hpx::parallel;

double mysecond()
{
    return hpx::util::high_resolution_clock::now() * 1e-9;
}

double random_double(double min, double max)
{
    return (min + 1)+(((double) rand())/(double) RAND_MAX)*(max - (min + 1));
}

template<typename T>
void vector_generator(std::vector<T> &A, int size, double min, double max)
{
    for(std::size_t r = 0; r < size; r++) {
        A.push_back(random_double(min, max));
    }
}

double mean(std::vector<double> times) {
    double mean = 0;
    for (int i(0); i < times.size(); i++) {
        mean += times[i];
    }
    mean /= times.size();
    return mean;
}


double var(std::vector<double> times) {
    double mean_time = mean(times);
    double var = 0;
    for (int i(0);i < times.size(); i++) {
        var += std::pow(times[i] - mean_time,2);
    }
    var /= times.size() -1;
    return var;
}
        


void Nothing(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features) {
    
    int vector_size = iterations;
    
    auto f=[&](int i) 
    {
    };
    if (Print_dynamic_features) 
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() <<" ";
    }

    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    std::vector<double> all_times(Nrep, 0);
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
        for(int j(0); j < Nrep + 1; j++)
        {
            if(chunk_candidates[i]*vector_size > 1)
            {
                t_chunk=mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), 
                                                                time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            else{
                t_chunk = mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            if(j != 0)
            {
                all_times[j - 1] = elapsed_time;
            }
        }
        std::cout << mean(all_times) << " " << var(all_times) << " ";
    }
    std::cout << std::endl;
}

   

/////////////////////////////////////////////////////////////////////////////////////////////////
void Swap(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features) 
{
    
    int vector_size = iterations;
    std::vector<double> A;
    std::vector<double> B;
    vector_generator(A, vector_size, 10, 100);
    vector_generator(B, vector_size, 10, 100);

    
    auto f=[&](int i)
    {
        std::swap(A[i],B[i]);
    };
  
    if (Print_dynamic_features) 
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() <<" ";
    }
    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    std::vector<double> all_times(Nrep, 0);
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
        for(int j(0); j < Nrep + 1; j++)
        {
            if(chunk_candidates[i]*vector_size > 1)
            {
                t_chunk=mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), 
                                                                time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            else{
                t_chunk = mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            if(j != 0)
            {
                all_times[j - 1] = elapsed_time;
            }
        }
        std::cout<< mean(all_times) << " " << var(all_times) << " ";
    }
    std::cout << std::endl;

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////// 	
void Stream(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features)
{
        
    int vector_size = iterations;
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    vector_generator(A, vector_size, 10, 100);
    vector_generator(B, vector_size, 10, 100);
    vector_generator(C, vector_size, 10, 100);

    double k(14);
    auto f=[&](int i)
    {
    C[i] = A[i];
	B[i] = k*C[i];
	C[i] = A[i] + B[i];
	A[i] = B[i] + k*C[i];
    };

    if (Print_dynamic_features)
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() << " ";
    }
    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    std::vector<double> all_times(Nrep, 0);
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
        for(int j(0); j < Nrep + 1; j++)
        {
            if(chunk_candidates[i]*vector_size > 1)
            {
                t_chunk=mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), 
                                                                time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            else{
                t_chunk = mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            if(j != 0)
            {
                all_times[j - 1] = elapsed_time;
            }
        }
        std::cout << mean(all_times) << " " << var(all_times) << " ";
    }
    std::cout << std::endl;
}

/////////////////////////////////////////////////
void Stencil(int iterations, std::vector<double> chunk_candidates, bool Print_dynamic_features) {
        
    int vector_size = iterations;
    std::vector<double> A;
    std::vector<double> B(iterations);
    vector_generator(A, vector_size, 10, 100);

    
    auto f=[&](int i)
    {
        if(0 < i && i < iterations - 1)
        {
	    B[i] = 1/2*A[i-1] + A[i] + 1/2*A[i+1];
	    }   
    };

    if (Print_dynamic_features) 
    {
        std::cout<< vector_size << " " << hpx::get_os_thread_count() << " ";
    } 
    auto time_range = boost::irange(0, vector_size);
    int Nrep = 10;
    double t_chunk = 0.0;
    std::vector<double> all_times(Nrep, 0);
    double elapsed_time;
    for (int i(0);i < chunk_candidates.size(); i++)
    {
        for(int j(0); j < Nrep + 1; j++)
        {
            if(chunk_candidates[i]*vector_size > 1)
            {
                t_chunk=mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), 
                                                                time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            else{
                t_chunk = mysecond();
                for_each(execution::par.with(execution::dynamic_chunk_size(1)), time_range.begin(), time_range.end(), f);
                elapsed_time = mysecond() - t_chunk;
            }
            if(j != 0)
            {
                all_times[j - 1] = elapsed_time;
            }
        }
        std::cout << mean(all_times) << " " << var(all_times) << " ";
    }
    std::cout << std::endl;   
}


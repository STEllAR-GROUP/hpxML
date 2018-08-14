//  Copyright (c) 2018 Gabriel Laberge 

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <hpx/hpx_init.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/parallel/executors/dynamic_chunk_size.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <boost/range/irange.hpp>

#define lambda_inner_iteration 0                                                                 

namespace hpx { namespace parallel {struct adaptive_chunk_size {}; } }


double random_double(double min, double max)
{
    return (min + 1)+(((double) rand())/(double) RAND_MAX)*(max - (min + 1));
}

template<typename T>
void vector_generator(std::vector<T> &A, int size, double min, double max)
{
    for(std::size_t r = 0; r < size; r++)
    {
        A.push_back(random_double(min, max));
    }
}



void Tensor_generator(int iterations, std::vector<double> chunk_candidates, std::ofstream& file)
{
        
    int vector_size = iterations;
    auto time_range = boost::irange(0, iterations);
    
    std::vector<std::vector<double>> A(iterations*iterations,std::vector<double>(iterations*iterations, 0));
    auto f = [&](int i)
    {
        for(int j(0);j < lambda_inner_iteration; j++)
        {
	        for(int k(0i);k < lambda_inner_iteration; k++)
            {
	            for(int l(0); l < lambda_inner_iteration; l++)
                {
		            A[i*vector_size + j][k*vector_size + l]=i + j + k + l;		            
		        }
	        }
	    }
    };
  //feature extraction Tensor_generator
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


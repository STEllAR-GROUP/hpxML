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
#include "lambda/1_loop_lambda.h"
#include "lambda/2_loop_lambda.h"



double random_double(double min,double max){
    return (min+1)+(((double) rand())/(double) RAND_MAX)*(max-(min+1));
}

template<typename T>
void vector_generator(std::vector<T> &A,int size,char type){
    if(type=='f'){
        for(std::size_t r = 0; r < size; r++) {
	    A.push_back(random_double(1,100));
	}
    }
    else if(type=='i'){
        for(std::size_t r = 0; r < size; r++) {
	    A.push_back((r+10)*(rand() % 10 + 1));
	}
    }
}
	
        

int hpx_main(int argc, char* argv[])
{
    // Initialization
    int iterations=strtol(argv[3],NULL,10);
    std::vector<double> chunk_candidates(7);
    chunk_candidates[0]=0.001;chunk_candidates[1]=0.005;chunk_candidates[2]=0.01;chunk_candidates[3]=0.05;chunk_candidates[4]=0.1;
    chunk_candidates[5]=0.2;chunk_candidates[6]=0.5;
    
    srand(time(NULL));
    std::ofstream file("./files/train_data_matrix_debug.txt",std::ios::app);
    if(file){
        if(argv[1][6]=='1' && argv[1][8]=='1'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		std::vector<int> C;
		vector_generator(A,iterations,argv[2][0]);
		vector_generator(B,iterations,argv[2][0]);
		vector_generator(C,iterations,argv[2][0]);
                lambda1_1(A,B,C,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		std::vector<double> C;
		vector_generator(A,iterations,argv[2][0]);
		vector_generator(B,iterations,argv[2][0]);
		vector_generator(C,iterations,argv[2][0]);
		lambda1_1(A,B,C,iterations,chunk_candidates,file);    
	    }
        }
       
        else if(argv[1][6]=='1' && argv[1][8]=='2'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		vector_generator(A,iterations,argv[2][0]);
		vector_generator(B,iterations,argv[2][0]);
                lambda1_2(A,B,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		vector_generator(A,iterations,argv[2][0]);
		vector_generator(B,iterations,argv[2][0]);
		lambda1_2(A,B,iterations,chunk_candidates,file);    
	    }
        }

        else if(argv[1][6]=='2' && argv[1][8]=='1'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		std::vector<int> C;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		vector_generator(C,iterations*iterations,argv[2][0]);
                lambda2_1(A,B,C,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		std::vector<double> C;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		vector_generator(C,iterations*iterations,argv[2][0]);
		lambda2_1(A,B,C,iterations,chunk_candidates,file);    
	    }
        } 
	else if(argv[1][6]=='2' && argv[1][8]=='2'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
                lambda2_2(A,B,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		lambda2_2(A,B,iterations,chunk_candidates,file);    
	    }
        }
        else if(argv[1][6]=='2' && argv[1][8]=='3'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
                lambda2_3(A,B,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		lambda2_3(A,B,iterations,chunk_candidates,file);    
	    }
        }
        else if(argv[1][6]=='2' && argv[1][8]=='4'){
	    if(argv[2][0]=='i'){
	        std::vector<int> A;
		std::vector<int> B;
		std::vector<int> C;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		vector_generator(C,iterations*iterations,argv[2][0]);
                lambda2_4(A,B,C,iterations,chunk_candidates,file);
		}
	    else if(argv[2][0]=='f'){
	        std::vector<double> A;
		std::vector<double> B;
		std::vector<double> C;
		vector_generator(A,iterations*iterations,argv[2][0]);
		vector_generator(B,iterations*iterations,argv[2][0]);
		vector_generator(C,iterations*iterations,argv[2][0]);
		lambda2_4(A,B,C,iterations,chunk_candidates,file);    
	    }
        }

    }
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

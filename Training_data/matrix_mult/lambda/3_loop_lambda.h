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



double mysecond()
{
    return hpx::util::high_resolution_clock::now() * 1e-9;
}



template<typename T>
double absolute_mean_error(std::vector<T> const& A,std::vector<T> const& B){
    double error(0);
    for(int i(0);i<A.size();i++){
        error+=std::abs(A[i]-B[i]);
    }
    error/=A.size();
    return error;
}

//random loop 1
template<typename T>
void train_1_data_matrix(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,bool show_error,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    //auto f = [&](int i) {
    //    T result=0.0;
	//result+=A[i];
	//result+=B[i];
	//result*=rand()%10+1;
	//C[i]=result;

    //};
    auto f=[&](int i){
        T container=A[i];
        A[i]=B[i];
        B[i]=container;
    };
  
  
  
  double t_chunk=0.0;
   file<<vector_size<<" "<<"1 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;
    
}


//random loop 2
template<typename T>
void train_2_data_matrix(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,bool show_error,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    /*auto f = [&](int i) {
	T result1=0.0;
        T result2=0.0;
        for(int k(0);k<vector_size;k++){
	    result1+=A[vector_size*i+k];
	    result2+=B[vector_size*i+k];
	}
	C[vector_size*i+0]=std::max(result1,result2);
	C[vector_size*i+1]=std::min(result1,result2);
	C[vector_size*i+1]=result1*result2;
	C[vector_size*i+2]=(result1+result2)*(rand()*10+1);

    };*/
    /*auto f=[&](int i){
        T result=0;
	for(int j(0);j<i;j++){
		result+=A[i];
	}
	B[i]=result;
    };*/

    /*auto f=[&](int i){
        T result=1;
	for(int j(2);j<A[i];j++){
		result*=j;
	}
	B[i]=result;
    };*/

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

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" "<<"2 ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;
    

}


//random loop 3
template<typename T>
void train_3_data_matrix(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,bool show_error,std::ofstream& file) {
    
    auto time_range = boost::irange(0, vector_size); 
    /*auto f = [&](int i) {
	T result=1;
        for(int j(0);j<vector_size;j++){
	    result=1;
	    for(int k(2);k<A[i*vector_size+j];k++){
	        result*=k;
	    }
	    B[vector_size*i+j]=result;
	}
    };*/
    /*
    auto f = [&](int i) {
       srand(i);
       int max_ite=rand()%int(vector_size/4)+int(vector_size/4);
       if(i % 4 == 0) {
            for (int j = 0; j < max_ite; j += 4) {

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

                for (int k = 0; k < max_ite; k++) {                  

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
    };*/
    /*auto f = [&](int i) {
	T result=0;
        for(int j(0);j<vector_size;j++){
	    result=0;
	    for(int k(0);k<j;k++){
	        result*=A[vector_size*i+k];
	    }
	    B[vector_size*i+j]=result;
	}
    };*/
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
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;

}





//Matrix Matrix multiplication A*B=C//
template<typename T>
void test_data_matrix(std::vector<T>& A, std::vector<T>& B, std::vector<T>& C,int vector_size,std::vector<double> chunk_candidates,bool show_error,std::ofstream& file) {
    
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

   // Dynamic chunk size/////////
   double t_chunk=0.0;
   file<<vector_size<<" ";

    for (int i(0);i<chunk_candidates.size();i++){
        t_chunk = mysecond();
        hpx::parallel::for_each(hpx::parallel::execution::par.with(hpx::parallel::execution::dynamic_chunk_size(vector_size*chunk_candidates[i])), time_range.begin(), time_range.end(), f);

        double elapsed_chunk = mysecond() - t_chunk;
	file<<elapsed_chunk<<" ";
      //  if (show_error){
   //	std::cout<<"The mean absolute error is : "<<absolute_mean_error(reference,C)<<std::endl;
    //    }
    }
    file<<""<<std::endl;

}


int hpx_main(int argc, char* argv[])
{
    // Initialization
    int vector_size=strtol(argv[1],NULL,10);

    std::size_t size_of_mat = vector_size * vector_size;
    std::vector<double> A(size_of_mat, 0.0);
    std::vector<double> B(size_of_mat, 0.0);
    std::vector<double> C(size_of_mat, 0.0);
    std::vector<double> chunk_candidates(7);
    chunk_candidates[0]=0.001;chunk_candidates[1]=0.005;chunk_candidates[2]=0.01;chunk_candidates[3]=0.05;chunk_candidates[4]=0.1;
    chunk_candidates[5]=0.2;chunk_candidates[6]=0.5;//chunk_candidates[7]=0.08;chunk_candidates[8]=0.09;chunk_candidates[9]=0.1;
    for(std::size_t r = 0; r < size_of_mat; r++) {
        srand(r);
        A[r] =(r+10)*(rand() % 10 + 1);
        B[r] =(r+10)*(rand() % 10 + 1);
        C[r] =(r+10)*(rand() % 10 + 1);
    }
    std::ofstream file("./../train_data_matrix.txt",std::ios::app);
    if(file){
    train_3_data_matrix<double>(A, B, C,vector_size,chunk_candidates,false,file);
    }
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    return hpx::init(argc, argv);
}

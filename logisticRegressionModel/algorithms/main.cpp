//  Copyright (c) 2017 BOARD OF SUPERVISORS OF LOUISIANA STATE UNIVERSITY AND AGRICULTURAL AND MECHANICAL COLLEGE
//  Developers Zahra Khatami, Gabriel Laberge
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cmath>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <limits>
#include "models/regression_models.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>


using namespace Eigen;



void reading_input_values(std::size_t number_of_experiments, std::size_t number_of_features, 
                            std::size_t number_of_multi_classes, MatrixXf& experimental_results, 
                            int* targets, MatrixXf& execution_times,float * candidates, std::ifstream& myfile) {

    std::string line;
    std::size_t e = 0;

    //assigning values for experimental_results:
    while(e < number_of_experiments) {

    	getline(myfile, line);
        std::stringstream ss(line);
        std::string str;
        std::size_t f = 0;

        //reading features:
        while(f < number_of_features) {
            getline(ss, str, ' ');
            experimental_results(e, f) = std::atof(str.c_str());
            f++;
        }

        //reading exec time for assiging target value
        float t_min = std::numeric_limits<float>::max();
        int which_class;
        for(int c = 0; c < number_of_multi_classes; c++) {
            getline(ss, str, ' ');
            float time_ = std::atof(str.c_str());
            execution_times(e, c) = time_;
            if(time_ < t_min){// && candidates[c]*experimental_results(e,4)>1){
                t_min = time_;
                which_class = c;
            }
        }

        //assiging the class of that experiments
        targets[e] = which_class;
        e++;    
    }
}

/*
void implementing_binary_logistic_regression_model(){
    float threshold = 0.2;
    std::string line;

    //learning two classes    
    std::cout <<"\n****************** Binary logistic regression model ******************\n"<<std::endl;

    //reading first line
    std::ifstream myfile ("../inputs/par_if.dat");
    getline(myfile, line);
    std::stringstream ss(line);
    std::string str;
    getline(ss, str, ' ');
    std::cout<<str<<std::endl;
    std::size_t number_of_experiments_two_class =std::stoi(str);
    getline(ss, str, ' ');
    std::cout<<str<<std::endl;
    std::size_t number_of_features_two_class = std::stoi(str);
    getline(ss, str, ' ');
    std::cout<<str<<std::endl;
    std::size_t number_of_multi_classes = std::stoi(str);





    //initializing
    float** experimental_results_two_class = new float*[number_of_experiments_two_class];
    float** execution_times_two_class = new float*[number_of_experiments_two_class];
    
    for(std::size_t n = 0; n < number_of_experiments_two_class; n++) {
        experimental_results_two_class[n] = new float[number_of_features_two_class];
        execution_times_two_class[n] = new float[2];
    }
    int* targets_two_class = new int[number_of_experiments_two_class];    


    //reading input data
    reading_input_values(number_of_experiments_two_class, number_of_features_two_class, number_of_multi_classes, 
                                    experimental_results_two_class, targets_two_class, execution_times_two_class, myfile);
    
    //implementing binary regression model on input data
    learning_binary_regression_model my_nw(number_of_experiments_two_class, number_of_features_two_class,
                                          threshold, experimental_results_two_class, targets_two_class, execution_times_two_class);

    my_nw.learning_two_classes();
    std::cout<<"Learning has been done!\n"<<std::endl;
    std::cout<<"\nThe predicated weights for each features are: "<<std::endl;
    my_nw.retrieving_weights_two_classes_into_txt_file();
    my_nw.printing_predicted_output_two_class();
    my_nw.finalizing_step();
}
*/
void implementing_multinomial_logistic_regression_model() {

    float threshold = 0.02;
    float eta = 0.01;
    float time_threshold = 0.1;
    int Max_ite = 5000;

    std::string line;
    
    //learning multi classes    
    std::cout << "\n****************** Multi-class logistic regression model ******************\n" <<std::endl;
    //reading input data : number of experiments, number of feautures and number of output_classes in each experiments
    //chunk size training data:
    std::ifstream myfile("./../inputs/train.dat");
    // prefetching distance training data:
    //std::ifstream myfile ("./../inputs/data_prefetch.dat");
    

    //read first line
    getline(myfile, line);
    std::stringstream ss(line);
    std::string str;
    getline(ss, str, ' ');
    std::size_t number_of_experiments = std::stoi(str);
    getline(ss, str, ' ');
    std::size_t number_of_features = std::stoi(str);
    getline(ss, str, ' ');
    std::size_t number_of_multi_classes = std::stoi(str);

    //read second line
    
    float* chunk_size_candidates = new float[number_of_multi_classes];
    getline(myfile,line);
    std::stringstream ss2(line);
    for(int i(0);i < number_of_features+number_of_multi_classes; i++) {
        if(i<number_of_features) {
	        getline(ss2, str, ' ');
	}
	    else {
	        getline(ss2, str, ' ');
	        chunk_size_candidates[i-number_of_features] = std::stof(str, NULL);
    	}
    }   
    
    
    //initializing     
    int* targets_multi_class = new int[number_of_experiments];
    MatrixXf experimental_results = MatrixXf::Random(number_of_experiments,number_of_features);
    MatrixXf execution_times = MatrixXf::Random(number_of_experiments,number_of_multi_classes);
    MatrixXf Y = MatrixXf::Random(number_of_experiments,number_of_multi_classes);

    //reading real input data
    reading_input_values(number_of_experiments, number_of_features,
                        number_of_multi_classes, experimental_results, 
                        targets_multi_class, execution_times,chunk_size_candidates, myfile);
    
   
   ////////normilazing features/////////
   float* averages =new float[number_of_features];
   float* averages_2 =new float[number_of_features];
   float* var =new float[number_of_features];

    for(std::size_t i = 0; i < number_of_features; i++) {
        averages[i] = 0;
	    averages_2[i] = 0;
	    var[i] = 0;
    }

    //computing average and variance values for each feature
    for(std::size_t i = 0; i < number_of_experiments; i++) {		
	    for(std::size_t j = 0; j < number_of_features; j++) {
	        averages[j] += experimental_results(i, j);
	        averages_2[j] += (pow(experimental_results(i, j), 2.0));
	    }
    }
    for(std::size_t i = 0; i < number_of_features; i++) {		
	    averages[i] = float(averages[i]/number_of_experiments);
	    averages_2[i] = float(averages_2[i]/number_of_experiments);
	    var[i] = sqrt(averages_2[i] - pow(averages[i], 2.0));		
    }

    for(std::size_t n = 0; n < number_of_experiments; n++) {
	    for(std::size_t f = 0; f < number_of_features; f++) {
	        experimental_results(n, f) = float((experimental_results(n, f) - averages[f])/var[f]);
	    }
    }
  
    multinomial_logistic_regression_model my_nw;
                                                           
    //convert targets to binary to get Y 
    my_nw.convert_target_to_binary(targets_multi_class, Y); 
    
    my_nw.fit(experimental_results, Y, execution_times, eta, threshold, time_threshold, Max_ite, true);
    std::cout<< "\nLearning has been done!\n" <<std::endl;
    //std::cout<<"\nThe predicated weights for each features are: "<<std::endl;    
    //my_nw.retrieving_weights_multi_classes_into_text_file();
    //my_nw.printing_predicted_output_multi_class();
    //my_nw.misclassification_ratio();
    

    //releasing memory
    delete[] chunk_size_candidates;
    delete[] targets_multi_class;
}

int main(int argc, const char * argv[]) {  

    //learning two classes
    //implementing_binary_logistic_regression_model();

    //learning multi classes
    implementing_multinomial_logistic_regression_model();  
    
    return 0;
}

#include <math.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <limits>
#include "../models/regression_models.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>

using namespace Eigen;


void reading_input_values(std::size_t number_of_experiments, std::size_t number_of_features, std::size_t number_of_multi_classes, 
                                        MatrixXf& experimental_results, int* targets, MatrixXf& execution_times_multi_class,float* candidates, std::ifstream& myfile) {

    std::string line;
    std::size_t e = 0;
    // Number of each class experiments
    std::vector<std::size_t> num_class(number_of_multi_classes, 0);

    //assigning values for experimental_results:
    while(e < number_of_experiments) {

    	getline(myfile, line);
        std::stringstream ss(line);
        std::string str;
        std::size_t f = 0;

        //reading features:
        while(f < number_of_features) {
            getline(ss, str, ' ');
            experimental_results(e,f) = std::atof(str.c_str());
            f++;
        }

        //reading exec time for assiging target value
        float t_min = std::numeric_limits<float>::max();
        int which_class;
        for(int c = 0; c < number_of_multi_classes; c++) {
            getline(ss, str, ' ');
            float time_ = std::atof(str.c_str());
            execution_times_multi_class(e,c) = time_;
            if(time_ < t_min){// && candidates[c]*experimental_results[e][4]>1) {
                t_min = time_;
                which_class = c;
            }
        }

        //assiging the class of that experiments
        targets[e] = which_class;
        num_class[which_class]++;

        e++;    
    }
}



void implementing_multinomial_logistic_regression_cross_validation(){
    float threshold = 0.08;
    float time_threshold=0.2;
    float eta=0.01;
    int Max_ite=50000;
    int k=10;
    std::string line;
    
    //learning multi classes    
    std::cout <<"\n****************** Multi-class logistic regression model cross Validation ******************\n"<<std::endl;
    //reading input data : number of experiments, number of feautures and number of output_classes in each experiments
    //chunk size training data:
    std::ifstream myfile("./../../inputs/matrix_mul_uniform_log.dat");
    // prefetching distance training data:
    //std::ifstream myfile ("./../inputs/data_prefetch.dat");
    

    //read first line
    getline(myfile, line);
    std::stringstream ss(line);
    std::string str;
    getline(ss, str, ' ');
    std::size_t number_of_experiments_multi_class = std::stoi(str);
    getline(ss, str, ' ');
    std::size_t number_of_features_multi_class = std::stoi(str);
    getline(ss, str, ' ');
    std::size_t number_of_multi_classes = std::stoi(str);

    float* chunk_size_candidates=new float[number_of_multi_classes];
    //read second line
    getline(myfile,line);
    std::stringstream ss2(line);
    for(int i(0);i<number_of_features_multi_class+number_of_multi_classes;i++){
        if(i<number_of_features_multi_class){
	    getline(ss2,str,' ');
	}
	else{
	    getline(ss2,str,' ');
	    chunk_size_candidates[i-number_of_features_multi_class]=std::stof(str,NULL);
	}
    }
    
    //initializing     
    int* targets_multi_class = new int[number_of_experiments_multi_class];
    MatrixXf experimental_results_multi_class= MatrixXf::Random(number_of_experiments_multi_class,number_of_features_multi_class);
    MatrixXf execution_times_multi_class=MatrixXf::Random(number_of_experiments_multi_class,number_of_multi_classes);
    int* threads_total=new int[number_of_experiments_multi_class];

    //reading real input data
    reading_input_values(number_of_experiments_multi_class, number_of_features_multi_class, number_of_multi_classes, 
                          experimental_results_multi_class, targets_multi_class, execution_times_multi_class,chunk_size_candidates, myfile);

    for(int i(0);i<number_of_experiments_multi_class;i++){
        threads_total[i]=experimental_results_multi_class(i,number_of_features_multi_class-1);
    }
     
    
    float* averages;							//parameters for normalization
    float* averages_2;							//parameters for normalization
    float* var;									//parameters for normalization	
    averages = new float[number_of_features_multi_class];
    averages_2 = new float[number_of_features_multi_class];
    var = new float[number_of_features_multi_class];
    //initializing
    for(std::size_t i = 0; i < number_of_features_multi_class; i++) {
  	averages[i] = 0;
	averages_2[i] = 0;
	var[i] = 0;
    }

    //computing average and variance values for each feature
    for(std::size_t i = 0; i < number_of_experiments_multi_class; i++) {		
	for(std::size_t j = 0; j < number_of_features_multi_class; j++) {
	    averages[j] += experimental_results_multi_class(i,j);
	    averages_2[j] += (std::pow(experimental_results_multi_class(i,j), 2.0));
	}
    }
    for(std::size_t i = 0; i < number_of_features_multi_class; i++) {		
	averages[i] = float(averages[i]/number_of_experiments_multi_class);
	averages_2[i] = float(averages_2[i]/number_of_experiments_multi_class);
	var[i] = sqrt(averages_2[i] - std::pow(averages[i], 2.0));		
    }

    for(std::size_t n = 0; n < number_of_experiments_multi_class; n++) {
	for(std::size_t f = 0; f < number_of_features_multi_class; f++) {
	    experimental_results_multi_class(n,f) = float((experimental_results_multi_class(n,f) - averages[f])/var[f]);
	}
    }



    //cross validation constants
    int delta=std::floor(number_of_experiments_multi_class/k);
    int last_delta=delta+(number_of_experiments_multi_class % k);
    int train_length,test_length;
    int train_index,test_index;
    float error=0;

    
    //initialize test sets table
    MatrixXf experimental_results_train(1,1);
    MatrixXf execution_times_train(1,1);
    MatrixXf targets_train(1,1);
    MatrixXf experimental_results_test(1,1);
    MatrixXf execution_times_test(1,1);

    //initialize logistic regression
     multinomial_logistic_regression_model my_nw;

    //convert predictions to dummy variables
    MatrixXf targets(number_of_experiments_multi_class,number_of_multi_classes);
    my_nw.convert_target_to_binary(targets_multi_class,targets);


   
   //loop over k subsets
    for(int i(0);i<k;i++){

        //dividing into train sets and test sets
        if(i==k-1){
	    test_length=last_delta;
	}
	else {
	     test_length=delta;   
	}    

	train_length=number_of_experiments_multi_class-test_length;

	//initializing train sets
        experimental_results_train.resize(train_length,number_of_features_multi_class);
        execution_times_train.resize(train_length,number_of_multi_classes);
	targets_train.resize(train_length,number_of_multi_classes);

        //initialization od test sets
        experimental_results_test.resize(test_length,number_of_features_multi_class);
	execution_times_test.resize(test_length,number_of_multi_classes);
        int* predictions_test=new int[test_length];
	int* targets_test=new int[test_length];
	int* threads=new int[test_length];
        
	
	train_index=0;
        test_index=0;
	//getting the train set
        for(int n(0);n<number_of_experiments_multi_class;n++){
	    if(i*delta<=n && n<=i*delta+test_length-1){
	    
	        //test set
    	        //features
                for(size_t j(0);j<number_of_features_multi_class;j++){
	            experimental_results_test(test_index,j)=experimental_results_multi_class(n,j);
		
	        }
	        for(size_t j(0);j<number_of_multi_classes;j++){
	            execution_times_test(test_index,j)=execution_times_multi_class(n,j);
	            targets_test[test_index]=targets_multi_class[n];	
		}
		threads[test_index]=threads_total[n];
	        test_index+=1;
	    }    
	   
	    
	    else {
	        //train set
	        //features
                for(size_t j(0);j<number_of_features_multi_class;j++){
	            experimental_results_train(train_index,j)=experimental_results_multi_class(n,j);
	        }
	        //targets
	        //Execution_times
                for(size_t j(0);j<number_of_multi_classes;j++){
	            execution_times_train(train_index,j)=execution_times_multi_class(n,j);
	            targets_train(train_index,j)=targets(n,j);
		}
	        train_index+=1;
	    }
	}
        
 
   

        //fit the train setmy_nw.fit(experimental_results_train,targets_train,execution_times_train,eta,threshold,time_threshold,Max_ite,false);
	my_nw.fit(experimental_results_train,targets_train,execution_times_train,eta,threshold,time_threshold,Max_ite,false);
        //predict on test set
	my_nw.predict(experimental_results_test,predictions_test);

/*
        //print prediction in a prediction file
    
        for(int j(0);j<test_length;j++){
	    while(1/chunk_size_candidates[predictions_test[j]]<threads[j]){
	       predictions_test[j]+=1;
	    }
	    std::cout<<chunk_size_candidates[predictions_test[j]]<<std::endl;
	   // std::cout<<threads[j]<<std::endl;
	}
*/

        //get the error on test set
        error= my_nw.computing_new_least_squared_err_multi_class(execution_times_test,predictions_test,targets_test,time_threshold); 
        std::cout<<error<<std::endl;


	delete[] predictions_test;
	delete[] targets_test;
        delete[] threads;
    }
    delete[] averages;
    delete[] averages_2;
    delete[] var;
    delete[] threads_total;
    delete[] chunk_size_candidates;
    delete[] targets_multi_class;

}

int main(int argc, const char * argv[]) {  

    implementing_multinomial_logistic_regression_cross_validation();  
    
    return 0;
}

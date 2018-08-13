//  Copyright (c) 2018 Gabriel Laberge 
//  Copyright (c) 2017 Zahra Khatami
//
// Train your data, then record them in an output file stated in "retrieving_weights_multi_classes_into_text_file"

#include <limits>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>

using namespace Eigen;

#define MAX_FLOAT (std::numeric_limits<float>::max())
#define MIN_FLOAT (std::numeric_limits<float>::min())

class multinomial_logistic_regression_model {

	MatrixXf weightsm; 							//weights of our learning network : F * K
	MatrixXf biases;
	MatrixXf outputsm;							//outputs of the training data : N * K
	MatrixXf gradientw;							//gradient of E : F * K
	MatrixXf gradientb;
	int number_of_features;
	int number_of_classes;
	
        void initialize(std::size_t number_expr,std::size_t number_features,std::size_t number_classes,float initial_values);
	
	void computing_all_output(MatrixXf X,MatrixXf& Y);
	void computing_all_gradient(MatrixXf X,MatrixXf Y);
	void updating_values_of_weigths_multi_class(float eta);
	
	void printing_weights_multi_class();
	
public:
	multinomial_logistic_regression_model() {
    	    MatrixXf weightsm;
	    MatrixXf biases;
	    MatrixXf outputsm;							//outputs of the training data : N * K
	    MatrixXf gradientw;							//gradient of E : F * K
	    MatrixXf gradientb;
	    int number_of_features;
	    int number_of_classes;

	}

	void convert_target_to_binary(int* targets, MatrixXf& Binary);	
	void convert_binary_to_target(MatrixXf Binary,int* targets);
	void fit(MatrixXf X,MatrixXf Y,MatrixXf execution_times,float eta,float threshold,float time_treshold,int Max_ite,bool print);
        void predict(MatrixXf X,int* predictions);
	float computing_new_least_squared_err_multi_class(MatrixXf execution_times,int* predictions,int* real,float time_threshold);	
        void retrieving_weights_multi_classes_into_text_file(float* averages,float* var,std::ofstream& outputFile);	
	void misclassification_ratio(int* predictions, int* real,int number_of_experiments);
        void Total_times(int* predictions,MatrixXf execution_times);
};

void multinomial_logistic_regression_model::initialize(std::size_t number_of_experiments,std::size_t number_features, std::size_t number_classes,float initial_values){
    weightsm=MatrixXf::Random(number_classes,number_features);
    biases=MatrixXf::Random(number_classes,1);
    gradientw=MatrixXf::Random(number_classes,number_features);
    gradientb=MatrixXf::Random(number_classes,1);
    outputsm=MatrixXf::Random(number_of_experiments,number_classes);
    number_of_features=number_features;
    number_of_classes=number_classes;

    //initializing weights
    for(std::size_t  c= 0; c < number_of_classes; c++) {
        biases(c,0)=0;
	for(std::size_t f = 0; f < number_of_features; f++) {
	    weightsm(c, f) = initial_values;
	}
    }
}


void multinomial_logistic_regression_model::convert_target_to_binary(int* target, MatrixXf& Binary) {
	for(std::size_t n = 0; n < Binary.rows(); n++) {
		for(std::size_t k = 0; k < Binary.cols(); k++) {
			if(target[n] == k) {
				Binary(n, k) = 1.0;
			}
			else {
				Binary(n, k) = 0.0;
			}
		}
	}
}


void multinomial_logistic_regression_model::convert_binary_to_target(MatrixXf Binary,int* target) {	
        for(std::size_t n = 0; n < Binary.rows(); n++) {
		float prob = MIN_FLOAT;
		for(std::size_t k = 0; k < Binary.cols(); k++) {
			if(prob < Binary(n, k)) {
				target[n] = k;
				prob =Binary(n, k);
			}
		}
	}
}

//computing outputs
void multinomial_logistic_regression_model::computing_all_output(MatrixXf X,MatrixXf& Y) {
	MatrixXf sum_w_experimental_results = MatrixXf::Zero(X.rows(),1);
	//w^T * X
	MatrixXf W_X = MatrixXf::Random(number_of_classes, X.rows());
	W_X = weightsm * X.transpose();

        //Add biases
	for(int i(0);i<X.rows();i++){
	    W_X.col(i)+=biases;
	}
	//sigma(exp(wQ))
	for(std::size_t n = 0; n < X.rows(); n++) {
		for(std::size_t k = 0; k < number_of_classes; k++) {
			sum_w_experimental_results(n, 0) += exp(W_X(k, n));
		}
	}
	
	//normalisation
	for(std::size_t n = 0; n < X.rows(); n++) {
		for(std::size_t k = 0; k < number_of_classes; k++) {		
			Y(n,k) = float(exp(W_X(k, n))/sum_w_experimental_results(n, 0)); 
		}
	}
}

//computing gradient 
void multinomial_logistic_regression_model::computing_all_gradient(MatrixXf X,MatrixXf Y){
	//initializing
	float sum=0;
	gradientw *= 0.0;
	gradientb*=0.0;
	MatrixXf Substraction=(outputsm-Y);
	gradientw=Substraction.transpose()*X;
        //biases
	for(int i(0);i<number_of_classes;i++){
	    sum=0;
	    for(int j(0);j<X.rows();j++){
	        sum+=Substraction(j,i);
	    }
	    gradientb(i,0)=sum;
	}
}


//computing leas squares err
float multinomial_logistic_regression_model::computing_new_least_squared_err_multi_class(MatrixXf execution_times,int* predictions,int* real,float time_threshold) {	
	std::size_t num_err = 0;
	for(std::size_t n = 0; n < execution_times.rows(); n++) {
		if(abs(execution_times(n, predictions[n]) - execution_times(n, real[n])) > time_threshold) {
			num_err++;
		}		
	}
	float prec = float(num_err) / execution_times.rows();
	return prec;
}

//updating weights
void multinomial_logistic_regression_model::updating_values_of_weigths_multi_class(float eta) {	
	weightsm= weightsm- eta*gradientw;
	biases=biases-eta*gradientb;
}

void multinomial_logistic_regression_model::printing_weights_multi_class() {
	std::cout<<weightsm<<std::endl;
	std::cout<<"\n --------------------\n";
}


//updating weights till error meets the defined threshold
void multinomial_logistic_regression_model::fit(MatrixXf X,MatrixXf Y,MatrixXf execution_times,float eta,float threshold,float time_treshold,int Max_ite,bool print) {
	float least_squared_err = MAX_FLOAT;
	std::size_t itr = 1;
	int* predictions=new int[X.rows()];
	int* real=new int[X.rows()];
	convert_binary_to_target(Y,real);
        //initializing weights,gradients,outputsm and constants
        initialize(X.rows(),X.cols(),Y.cols(),0.1);
	computing_all_output(X,outputsm);
       // computing_all_output(X,outputsm);
	while(threshold < least_squared_err && itr<Max_ite) {
		computing_all_gradient(X,Y);								
		updating_values_of_weigths_multi_class(eta);
		computing_all_output(X,outputsm);
		convert_binary_to_target(outputsm,predictions);
		least_squared_err = computing_new_least_squared_err_multi_class(execution_times,predictions,real,time_treshold);
   	        if(print){
		    std::cout<<"("<<itr<<")"<<"Least_squared_err =\t" << least_squared_err<<std::endl;		
		    printing_weights_multi_class();
		    std::cout<<"biases = "<<biases<<std::endl;
		}		
		itr++;
	}
	if(print){std::cout<<"("<<itr<<") => "<<"Least_squared_err =\t" << least_squared_err<<std::endl;
	    misclassification_ratio(predictions,real,X.rows());
	    Total_times(predictions,execution_times);
	}
	delete[] predictions;
	delete[] real;
}
void multinomial_logistic_regression_model::predict(MatrixXf X,int* predictions){
    //forward propogation
    MatrixXf Y=MatrixXf::Zero(X.rows(),number_of_classes);
    computing_all_output(X,Y);
    convert_binary_to_target(Y,predictions);
}


//retrieving information into the external file, which is going to be used at runtime
void multinomial_logistic_regression_model::retrieving_weights_multi_classes_into_text_file(float* averages,float* var,std::ofstream& outputFile) {	
  
	//normalization parameters (variance and average) in the first line
	for(std::size_t p = 0; p < number_of_features - 1; p++) {
		outputFile << var[p] << " " << averages[p] << " "; 
	}
	outputFile << var[number_of_features - 1] << " " << averages[number_of_features - 1] << std::endl;

	for(std::size_t c = 0; c < number_of_classes; c++) {
		for(std::size_t f = 0; f < number_of_features - 1; f++) {
			outputFile << weightsm(f, c) << " ";
		}
		outputFile << weightsm(number_of_features - 1, c);
		if(c != number_of_classes - 1) {
			outputFile << std::endl;
		}
	}
}


void multinomial_logistic_regression_model::misclassification_ratio(int* predictions, int* real,int number_of_experiments){
	std::size_t num_err = 0;
	MatrixXi confusion_matrix=MatrixXi::Zero(number_of_classes,number_of_classes);
	for(std::size_t n = 0; n < number_of_experiments; n++) {		
	    confusion_matrix(predictions[n],real[n])+=1;
	    if(predictions[n] != real[n]){
	        num_err+=1;
	    }
	}
        std::cout<<confusion_matrix<<std::endl;
	std::cout<<"\n number of misclassifications predicted is\t"<<num_err<<" out of "<<number_of_experiments<<std::endl;
}

void multinomial_logistic_regression_model::Total_times(int* predictions,MatrixXf execution_times){
    double optimal_time=0;
    double actual_time=0;
    double min_t;
    std::vector<double> times_candidates(number_of_classes,0);
    for(std::size_t n=0;n<execution_times.rows();n++){
        actual_time+=execution_times(n,predictions[n]);
	min_t=execution_times(n,0);
	for(std::size_t c=0;c<number_of_classes;c++){
	    times_candidates[c]+=execution_times(n,c);
	    if(execution_times(n,c)<min_t){
	        min_t=execution_times(n,c);
	    }
	}
	optimal_time+=min_t;

    }
    std::cout<<"The total is :"<<actual_time<<std::endl;
    std::cout<<"The optimal time is "<<optimal_time<<std::endl;
    for(std::size_t c=0;c<number_of_classes;c++){
        std::cout<<"The time for candidate "<<c<<" is "<<times_candidates[c]<<std::endl;
    }
}


#include <limits>
#include <math.h>
#include <iostream>

#define MAX_DOUBLE (std::numeric_limits<double>::max())
#define MIN_DOUBLE (std::numeric_limits<double>::min())

class learning_network {

	unsigned number_of_experiments;
	unsigned number_of_features;
	unsigned number_of_classes;
	double** experimental_results; 				//the experimental values of the features of the training data
	double threshold; 							//the convergence for estimating the final weights

	//two-class logistic regression
	double* weightsb; 							//weights of our learning network
	double* new_weightsb;						//updated weights after each step	
	unsigned* targets_two_class;				//outputs of the training data
	double** diag_weightsb; 					//used for updating weights
	double* M; 									//used for updating weights
	
	//multi-class logistic regression
	double** weightsm; 							//weights of our learning network : (F * K) * 1
	double** new_weightsm;						//updated weights after each step : (F * K) * 1
	unsigned** targets_multi_class;				//real output of each experimental results : N * K
	double** outputsm;							//outputs of the training data : N * K
	double** gradient;							//gradient of E : (F * K) * 1
	double** hessian;							//hessian of E : (F * K) * (F * K)
	double** Ihessian;							//inverse of hessian of E : (F * K) * (F * K)
	double** delta_weight;						//used for updating weight : (F * K) * 1
	double* sum_w_experimental_results;			//used for computing output : N 
	unsigned* predicted_output;					//predicted class of each experimental results
	unsigned* real_output;						//real output of each experimental results
	
	void inverse_mat(double** mat, double** inverse, unsigned size);
	void get_cofactor(double **src, double **dest, unsigned p, unsigned q, unsigned size);
	double calc_determinant( double **mat, unsigned size);
	void adjoint(double** mat, double** adj, unsigned size);
	
	/*
	two-class logistic regression (binary logistic regression) :
	*/
	void normalizing_weights_two_class();
	double get_value_of_M(unsigned i);
	void updating_values_of_M_and_diag_weights();		
	void inverse_martix_XSX(double** mat, double** inverse, unsigned size);
	void updating_values_of_weights_two_class();
	void new_values_for_weightsb();
	double computing_new_least_squared_err_two_class();	
	void learning_weights_two_classes();
	void printing_weights_two_class();	

	/*
	multi-class logistic regression 
	*/
	void normalizing_weights_multi_class();
	void convert_target_to_binary(unsigned* target_src, unsigned** targets_dst);
	void sum_w_experimental_results_n(unsigned n);
	double output_nk(unsigned n, unsigned k);
	void computing_all_output_n(unsigned n);
	void computing_all_output();
	int eye_kj(unsigned k, unsigned j);
	void gradient_E_k(unsigned k);
	void computing_all_gradient();
	double hessian_E_kj(unsigned k, unsigned j);
	void computing_all_hessian();
	void computing_inverse_hessian();
	void learning_weights_multi_classes();
	void computing_delta_weight();
	void new_values_for_weightsm();
	double computing_new_least_squared_err_multi_class();	
	void updating_values_of_weights_multi_class();
	void printing_weights_multi_class();
	void estimating_output_class();
	
public:
	learning_network(unsigned number_of_expr, unsigned number_of_ftrs, 
						unsigned number_of_cls, double th) {
		number_of_experiments = number_of_expr;
		number_of_features = number_of_ftrs;
		number_of_classes = number_of_cls;
		threshold = th;		
	}	

	//initilializer for two_class
	void initilializer_two_class(double** expr_results, unsigned* target_expr){
		weightsb = new double[number_of_features +  1];
		new_weightsb = new double[number_of_features +  1];
		targets_two_class = new unsigned[number_of_experiments];
		diag_weightsb = new double*[number_of_experiments];
		M = new double[number_of_experiments];
		experimental_results = new double*[number_of_experiments];

		//initializing weights
		for(unsigned i = 0; i < number_of_features +  1; i++) {
			weightsb[i] = 0.1;
		}				

		for(unsigned i = 0; i < number_of_experiments; i++) {
			experimental_results[i] = new double[number_of_features + 1];
			targets_two_class[i] = target_expr[i];
			diag_weightsb[i] = new double[number_of_experiments];
			M[i] = 0.0;

			//initializing experimental_results
			experimental_results[i][0] = 1.0; // 1 + wf + ....
			for(unsigned j = 1; j < number_of_features + 1; j++) {
				experimental_results[i][j] = expr_results[i][j - 1];
			}

			//initializing diag_weightsb
			for(unsigned j = 0; j < number_of_experiments; j++) {
				diag_weightsb[i][j] = 0.0;
			}
		}
	}	

	//initilializer for multi_class
	void initilializer_multi_class(double** expr_results, unsigned* target_expr) {
		sum_w_experimental_results = new double[number_of_experiments];
		unsigned num_row = number_of_features * number_of_classes;
		weightsm = new double*[num_row]; 							
		new_weightsm = new double*[num_row];
		gradient = new double*[num_row];
		delta_weight = 	new double*[num_row];
		hessian = new double*[num_row];
		Ihessian = new double*[num_row];
		experimental_results = new double*[number_of_experiments];
		targets_multi_class = new unsigned*[number_of_experiments];
		outputsm = new double*[number_of_experiments];
		predicted_output = new unsigned[number_of_experiments];
		real_output = new unsigned[number_of_experiments];

		for(unsigned i = 0; i < num_row; i++) {
			weightsm[i] =  new double[1];
			new_weightsm[i] =  new double[1];
			gradient[i] =  new double[1];
			delta_weight[i] =  new double[1];
			hessian[i] =  new double[num_row];
			Ihessian[i] =  new double[num_row];

			//initializing weights
			weightsm[i][0] = 1;
		}

		
		for(unsigned i = 0; i < number_of_experiments; i++) {
			experimental_results[i] = new double[number_of_features];
			targets_multi_class[i] = new unsigned[number_of_classes];
			outputsm[i] = new double[number_of_classes];

			//initializing experimental_results
			for(unsigned f = 0; f < number_of_features; f++) {
				experimental_results[i][f] = expr_results[i][f];
			}

			//initializing real outputs
			real_output[i] = target_expr[i];
		}

		//initializing targets_multi_class
		convert_target_to_binary(target_expr, targets_multi_class);
	}

	//two-class logistic regression
	void learning_two_classes();
	double* retrieving_weights_two_classes();
	void finalizing_two_classes();

	//multi-class logistic regression
	void learning_multi_classes();
	double** retrieving_weights_multi_classes();
	void finalizing_multi_classes();
	void printing_predicted_output_classes();
};


/*
two-class logistic regression (binary logistic regression) :
*/

double learning_network::get_value_of_M(unsigned i) {
	double temp = 0.0;
	for(unsigned j = 0; j < number_of_features + 1; j++) {
		temp += weightsb[j] * experimental_results[i][j];
	}
	double result = (1 / (1 + double(1 / exp(temp))));
	return result;
}

void learning_network::updating_values_of_M_and_diag_weights() {
	for(unsigned i = 0; i < number_of_experiments; i++) {
		M[i] = get_value_of_M(i);
		diag_weightsb[i][i] = M[i] * (1 - M[i]);
	}
}

// calculate the cofactor of element (row,col)
void learning_network::get_cofactor(double **src, double **dest, unsigned p, 
									unsigned q, unsigned size) {
	
	unsigned i = 0, j = 0;

    // Looping for each element of the matrix
    for (unsigned row = 0; row < size; row++) {
        for (unsigned col = 0; col < size; col++) {
            //  Copying unsignedo temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q) {
                dest[i][j++] = src[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Calculate the determinant recursively.
double learning_network::calc_determinant(double **mat, unsigned size) {
	//size must be >= 0
	//stop the recursion when matrix is a single element
	double det = 0; // Initialize result
     if (size == 1) {
        return mat[0][0];
    }
 
 	// To store cofactors
    double** temp = new double*[size];
    for(unsigned i = 0; i < size; i++) {
    	temp[i] = new double[size];
    } 
 
    double sign = 1.0;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (unsigned f = 0; f < size; f++) {
        // Getting Cofactor of mat[0][f]
        get_cofactor(mat, temp, 0, f, size);
        det += sign * mat[0][f] * calc_determinant(temp, size - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    } 

    //releasing memory
    for(unsigned i = 0; i < size; i++) {
    	delete[] temp[i];
    	temp[i] = nullptr;
    }
    delete[] temp;

    return det;
}

// Function to get adjoint of mat in adj
void learning_network::adjoint(double** mat, double** adj, unsigned size) {
    if (size == 1) {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of mat
    double sign = 1.0;
    double** temp = new double*[size];
    for(unsigned i = 0; i < size; i++) {
    	temp[i] = new double[size];
    }
 
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            // Get cofactor of mat[i][j]
            get_cofactor(mat, temp, i, j, size);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1: -1;
 
            // unsignederchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(calc_determinant(temp, size - 1));
        }
    }

    //releasing memory
    for(unsigned i = 0; i < size; i++) {
    	delete[] temp[i];
    	temp[i] = nullptr;
    }
    delete[] temp;
}

// Function to calculate and store inverse, returns false if
// matrix is singular
void learning_network::inverse_mat(double** mat, double** inverse, unsigned size) {    
    double det = calc_determinant(mat, size);
    if (det == 0) {
        std::cout<<"\n************Singular matrix, can't find its inverse************\n";
        return;
    }
 
    // Find adjoint
    double** adj = new double*[size];
    for(unsigned i = 0; i < size; i++) {
    	adj[i] = new double[size];
    }

    adjoint(mat, adj, size);
 
    // Find Inverse using formula "inverse(mat) = adj(mat)/det(mat)"
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            inverse[i][j] = adj[i][j]/det;
        }
    }

	for(unsigned i = 0; i < size; i++) {
		delete adj[i];
	}    
	delete[] adj;
 }

void learning_network::inverse_martix_XSX(double** mat, double** inverse, unsigned size) {
    inverse_mat(mat, inverse, size);
}

void learning_network::new_values_for_weightsb() {
	//allocating memory
	double** temp1; //XSX : f * f
	double** temp2; //SXW + y - M : expr * 1
	double** temp3; //XSX * X^T : f * expr
	double** temp4; //X^T * S
	double** inverse_temp1;
	temp1 = new double*[number_of_features + 1];
	temp2 = new double*[number_of_experiments];
	temp3 = new double*[number_of_features + 1];
	temp4 = new double*[number_of_features + 1]; 
	inverse_temp1 = new double*[number_of_features + 1];    

	//initializing
	for(unsigned i = 0; i < number_of_features + 1; i++) {
    	inverse_temp1[i] = new double[number_of_features + 1];
    }

	for(unsigned i = 0; i < number_of_features + 1; i++) {
		temp1[i] = new double[number_of_features + 1];
		temp3[i] = new double[number_of_experiments];
		temp4[i] = new double[number_of_experiments];
	}	
	
	for(unsigned i = 0; i < number_of_experiments; i++) {
		temp2[i] = new double[1];
		temp2[i][0] = 0.0;
	}

	for(unsigned i = 0; i < number_of_features + 1; i++) {
		for(unsigned j = 0; j < number_of_experiments; j++) {
			//initializing value
			if(j == 0) {
				temp4[i][j] = 0;	
			}
			temp4[i][j] = experimental_results[j][i] * diag_weightsb[j][j];
		}

		for(unsigned j = 0; j < number_of_features + 1; j++) {
			for(unsigned k = 0; k < number_of_experiments; k++) {
				//initializing value
				if(k == 0) {
					temp1[i][j] = 0;
				}
				temp1[i][j] += temp4[i][k] * experimental_results[k][j];
			}
		}
	}

	inverse_martix_XSX(temp1, inverse_temp1, number_of_features + 1);

	//computing temp2
	for(unsigned i = 0; i < number_of_experiments; i++) { 
		for(unsigned j = 0; j < number_of_features + 1; j++) {
			temp2[i][0] += diag_weightsb[i][i] * experimental_results[i][j] * weightsb[j]; 
		}
		temp2[i][0] += targets_two_class[i] - M[i];
	}

	//updating weightsb
	for(unsigned i = 0; i < number_of_features + 1; i++) {
		new_weightsb[i] = 0.0;
		for(unsigned j = 0; j < number_of_experiments; j++) {
			for(unsigned k = 0; k < number_of_features + 1; k++) {
				if(k == 0) {
					temp3[i][j] = 0.0;
				}
				temp3[i][j] += inverse_temp1[i][k] * experimental_results[j][k];
			}
			new_weightsb[i] += temp3[i][j] * temp2[j][0];
		}
	}

	//releasing memory
	for(unsigned i = 0; i < number_of_features + 1; i++) {
		delete[] temp1[i];
		delete[] inverse_temp1[i];
		delete[] temp3[i];
		delete[] temp4[i];
		temp1[i] = nullptr;
		inverse_temp1[i] = nullptr;
		temp3[i] = nullptr;
		temp4[i] = nullptr;
	}
	for(unsigned i = 0; i < number_of_experiments; i++) {
		delete[] temp2[i];
		temp2[i] = nullptr;
	}
	delete[] temp1;
	delete[] inverse_temp1;
	delete[] temp2;
	delete[] temp3;
	delete[] temp4;
}

double learning_network::computing_new_least_squared_err_two_class() {
	double temp_err = 0.0;
	double old_wx, new_wz;
	for(unsigned i = 0; i < number_of_experiments; i++) {
		old_wx = 0;
		new_wz = 0;
		for(unsigned j = 0; j < number_of_features + 1; j++) {
			old_wx += weightsb[j] * experimental_results[i][j];
			new_wz += new_weightsb[j] * experimental_results[i][j];
		}
		temp_err += pow( ((1 / (1 + (1 / exp(old_wx))))) - (1 / (1 + (1 / exp(new_wz)))) , 2.0);
	}
	return sqrt(temp_err);
}

void learning_network::updating_values_of_weights_two_class() {
	for(unsigned i = 0; i < number_of_features + 1; i++) {
		weightsb[i] = new_weightsb[i];
	}
}

void learning_network::printing_weights_two_class() {
	for(unsigned i = 0; i < number_of_features + 1; i++) {
		std::cout<<"weights["<<i<<"] = "<<weightsb[i]<<"\t";
	}
	std::cout<<"\n----------"<<std::endl;
}

//this func applys experimental values of the training data on our learning network
void learning_network::learning_weights_two_classes() {
	double least_squared_err = MAX_DOUBLE;	
	unsigned itr = 0;
	while(threshold < least_squared_err) {		
		updating_values_of_M_and_diag_weights();
		new_values_for_weightsb();
		least_squared_err = computing_new_least_squared_err_two_class();
		std::cout<<"("<<itr<<")\t"<<"Least_squared_err =\t" << least_squared_err<<std::endl;
		updating_values_of_weights_two_class();		
		printing_weights_two_class();
		itr++;
	}
}

void learning_network::normalizing_weights_two_class() {
	//normalizing all features, except first one, which is 1 for all
	double* averages = new double[number_of_features];
	double* averages_2 = new double[number_of_features];
	double* var = new double[number_of_features];
	//initializing
	for(unsigned i = 0; i < number_of_features; i++) {
		averages[i] = 0;
		averages_2[i] = 0;
		var[i] = 0;
	}

	//computing average and variance values for each feature
	for(unsigned i = 0; i < number_of_experiments; i++) {		
		for(unsigned j = 1; j < number_of_features + 1; j++) {
			averages[j - 1] += experimental_results[i][j];
			averages_2[j - 1] += (pow(experimental_results[i][j], 2.0));
		}
	}
	for(unsigned i = 0; i < number_of_features; i++) {		
		averages[i] = double(averages[i]/number_of_experiments);
		averages_2[i] = double(averages_2[i]/number_of_experiments);
		var[i] = sqrt(averages_2[i] - pow(averages[i], 2.0));		
	}

	for(unsigned n = 0; n < number_of_experiments; n++) {
		for(unsigned f = 1; f < number_of_features + 1; f++) {
			experimental_results[n][f] = (experimental_results[n][f] - averages[f])/var[f];
		}
	}

	//releasing memory
	delete[] averages;
	delete[] averages_2;
	delete[] var;
}

void learning_network::learning_two_classes() {
	//normalizing_weights_two_class();
	learning_weights_two_classes();
}

double* learning_network::retrieving_weights_two_classes() {
	return weightsb;
}

void learning_network::finalizing_two_classes() {
	//releasing memory
	for(unsigned n = 0; n < number_of_experiments; n++) {
		delete[] experimental_results[n];
		delete[] diag_weightsb[n];
		experimental_results[n] = nullptr;
		diag_weightsb[n] = nullptr;
	}		
	delete[] experimental_results;
	delete[] diag_weightsb;
	delete[] weightsb;
	delete[] new_weightsb;
	delete[] targets_two_class;		
	delete[] M;
	weightsb = nullptr;
	new_weightsb = nullptr;
	targets_two_class = nullptr;
	M = nullptr;
}

/*
multi-class logistic regression 
*/

void learning_network::convert_target_to_binary(unsigned* target_src, unsigned** targets_dst) {
	for(unsigned n = 0; n < number_of_experiments; n++) {
		for(unsigned k = 0; k < number_of_classes; k++) {
			if(target_src[n] == k) {
				targets_dst[n][k] = 1;
			}
			else {
				targets_dst[n][k] = 0;
			}
		}
	}
}

//Ikj
int learning_network::eye_kj(unsigned k, unsigned j) {
	if(k == j) {
		return 1;
	}
	return 0;
}

//computing ouput
void learning_network::sum_w_experimental_results_n(unsigned n) {
	sum_w_experimental_results[n] = 0.0;	
	for(unsigned k = 0; k < number_of_classes; k++) {
		unsigned offset = k * number_of_features;
		for(unsigned f = 0; f < number_of_features; f++) {
			sum_w_experimental_results[n] += weightsm[offset + f][0] * experimental_results[n][f];
		}
	}
}

double learning_network::output_nk(unsigned n, unsigned k) {
	double temp = 0.0;
	unsigned offset = k * number_of_features;
	for(unsigned f = 0; f < number_of_features; f++) {
		temp += weightsm[offset + f][0] * experimental_results[n][f];
	}

	double out = (double)(exp(temp)/exp(sum_w_experimental_results[n]));
	return out;
}

void learning_network::computing_all_output_n(unsigned n) {	
	sum_w_experimental_results_n(n);
	for(unsigned k = 0; k < number_of_classes; k++) {
		outputsm[n][k] = output_nk(n, k);
	}
}

void learning_network::computing_all_output() {
	for(unsigned n = 0; n < number_of_experiments; n++) {
		computing_all_output_n(n);		
	}
}

//computing gradient for each W
void learning_network::gradient_E_k(unsigned k) {
	unsigned offset = k * number_of_features;
	for(unsigned f = 0; f < number_of_features; f++) {
		gradient[offset + f][0] = 0.0;
		for(unsigned n = 0; n < number_of_experiments; n++) {
			gradient[offset + f][0] += (output_nk(n, k) - targets_multi_class[n][k]) * experimental_results[n][f];			
		}
	}
}

void learning_network::computing_all_gradient(){
	for(unsigned k = 0; k < number_of_classes; k++) {
		gradient_E_k(k);
	}
}

//computing hessian 
double learning_network::hessian_E_kj(unsigned k, unsigned j) {
	unsigned row_offset = k * number_of_features;
	unsigned col_offset = j * number_of_features;

	for(unsigned i = 0; i < number_of_features; i++) {
		for(unsigned f = 0; f < number_of_features; f++) {
			hessian[row_offset + i][col_offset + f] = 0.0;
			for(unsigned n = 0; n < number_of_experiments; n++) {
				hessian[row_offset + i][col_offset + f] += outputsm[n][k] * (eye_kj(k, j) - outputsm[n][j]) * experimental_results[n][i] * experimental_results[n][f];
			}
			hessian[row_offset + i][col_offset + f] = (-1) * hessian[row_offset + i][col_offset + f];
		}
	}
}

void learning_network::computing_all_hessian() {
	for(unsigned k  = 0; k < number_of_classes; k++) {
		for(unsigned j = 0; j < number_of_classes; j++) {
			hessian_E_kj(k, j);
		}
	}
}

void learning_network::computing_inverse_hessian() {
	unsigned size = number_of_classes * number_of_features;
	inverse_mat(hessian, Ihessian, size);
}

//Ihessian * gradient
void learning_network::computing_delta_weight() {
	unsigned size = number_of_classes * number_of_features;
	for(unsigned i = 0; i < size; i++) {
		delta_weight[i][0] = 0;
		for(unsigned j = 0; j < size; j++) {
			delta_weight[i][0] += Ihessian[i][j] * gradient[j][0];
		}
	}
}

void learning_network::new_values_for_weightsm() {
	computing_inverse_hessian();	
	computing_delta_weight();

	unsigned size = number_of_classes * number_of_features;
	for(unsigned i = 0; i < size; i++) {
		new_weightsm[i][0] = weightsm[i][0] - delta_weight[i][0];
	}
}

//computing leas squares err
double learning_network::computing_new_least_squared_err_multi_class() {
	double err = 0.0;
	unsigned size = number_of_classes * number_of_features;
	for(unsigned i = 0; i < size; i++) {
		err += pow((new_weightsm[i][0] - weightsm[i][0]), 2.0);
	}
	return sqrt(err);
}

//updating weights
void learning_network::updating_values_of_weights_multi_class() {
	unsigned size = number_of_classes * number_of_features;
	for(unsigned i = 0; i < size; i++) {
		weightsm[i][0] = new_weightsm[i][0];
	}
}

void learning_network::printing_weights_multi_class() {
	unsigned size = number_of_classes * number_of_features;
	for(unsigned k = 0; k < number_of_classes; k++) {
		for(unsigned f = 0; f < number_of_features; f++) {
			unsigned offset = k * number_of_features + f;
			std::cout<<"weights["<<k<<"]["<<f<<"] = "<<weightsm[offset][0]<<"\t";
		}
		std::cout<<std::endl;		
	}
	std::cout<<"\n----------\n"<<std::endl;
}

//updating weights till error meets the defined threshold
void learning_network::learning_weights_multi_classes() {
	double least_squared_err = MAX_DOUBLE;
	unsigned itr = 0;
	while(threshold < least_squared_err) {
		computing_all_output();		
		computing_all_gradient();
		computing_all_hessian();		
		new_values_for_weightsm();		
		least_squared_err = computing_new_least_squared_err_multi_class();
		std::cout<<"("<<itr<<")"<<"Least_squared_err =\t" << least_squared_err<<std::endl;
		printing_weights_multi_class();
		updating_values_of_weights_multi_class();		
		itr++;
	}
}

void learning_network::normalizing_weights_multi_class() {
	double* averages = new double[number_of_features];
	double* averages_2 = new double[number_of_features];
	double* var = new double[number_of_features];
	//initializing
	for(unsigned i = 0; i < number_of_features; i++) {
		averages[i] = 0;
		averages_2[i] = 0;
		var[i] = 0;
	}

	//computing average and variance values for each feature
	for(unsigned i = 0; i < number_of_experiments; i++) {		
		for(unsigned j = 0; j < number_of_features; j++) {
			averages[j] += experimental_results[i][j];
			averages_2[j] += (pow(experimental_results[i][j], 2.0));
		}
	}
	for(unsigned i = 0; i < number_of_features; i++) {		
		averages[i] = double(averages[i]/number_of_experiments);
		averages_2[i] = double(averages_2[i]/number_of_experiments);
		var[i] = sqrt(averages_2[i] - pow(averages[i], 2.0));		
	}

	for(unsigned n = 0; n < number_of_experiments; n++) {
		for(unsigned f = 0; f < number_of_features; f++) {
			experimental_results[n][f] = (experimental_results[n][f] - averages[f])/var[f];
		}
	}

	//releasing memory
	delete[] averages;
	delete[] averages_2;
	delete[] var;
}

void learning_network::learning_multi_classes() {
	normalizing_weights_multi_class();
	learning_weights_multi_classes();
}

double** learning_network::retrieving_weights_multi_classes() {
	return weightsm;
}

//estimating class of each experimental results based on the computed weights
void learning_network::estimating_output_class() {
	for(unsigned n = 0; n < number_of_experiments; n++) {
		double prob = MIN_DOUBLE;
		for(unsigned k = 0; k < number_of_classes; k++) {
			double out = output_nk(n, k);
			if(prob < outputsm[n][k]) {
				predicted_output[n] = k;
				prob = outputsm[n][k];
			}
		}
	}
	std::cout<<std::endl;
}

void learning_network::printing_predicted_output_classes(){
	estimating_output_class();
	unsigned num_err = 0;
	for(unsigned n = 0; n < number_of_experiments; n++) {
		std::cout<<"\n class["<<n<<"] =\t"<<predicted_output[n]<<"\t"<<real_output[n];
		if(predicted_output[n] != real_output[n]){
			num_err++;
		}
	}
	std::cout<<"\n number of error predicted is\t"<<num_err<<std::endl;
}

void learning_network::finalizing_multi_classes() {
	//relasing memory
	for(unsigned n = 0; n < number_of_experiments; n++) {
		delete[] experimental_results[n];
		delete[] targets_multi_class[n];
		delete[] outputsm[n];
		experimental_results[n] = nullptr;
		targets_multi_class[n] = nullptr;
		outputsm[n] = nullptr;
	}
	delete[] experimental_results;
	delete[] targets_multi_class;
	delete[] outputsm;

	unsigned num_row = number_of_features * number_of_classes;
	for(unsigned r = 0; r < num_row; r++) {
		delete[] weightsm[r];
		delete[] new_weightsm[r];
		delete[] gradient[r];
		delete[] delta_weight[r];
		delete[] hessian[r];
		delete[] Ihessian[r];
		weightsm[r] = nullptr;
		new_weightsm[r] = nullptr;
		gradient[r] = nullptr;
		delta_weight[r] = nullptr;
		hessian[r] = nullptr;
		Ihessian[r] = nullptr;
	}
	delete[] weightsm;
	delete[] new_weightsm;
	delete[] gradient;
	delete[] delta_weight;
	delete[] hessian;
	delete[] Ihessian;
	delete[] sum_w_experimental_results;
	delete[] predicted_output;
	delete[] real_output;
	real_output = nullptr;
	predicted_output = nullptr;
	sum_w_experimental_results = nullptr;
}

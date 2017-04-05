
# Table of Contents
1. [Logistic Regression Model](README.md#hpx-clangtool)
2. [Training Data](README.md#training-data)
3. [Trained Weights](README.md#trained-weights)
4. [Instructions](README.md#instructions)

## Logistic Regression Model

We use the binary and multinomial logistic regression models to select the optimum execution policy, chunk size, and prefetching distance for certain HPX loops based on both, static and dynamic information, with the goal of minimizing execution time. Here, the static information about the loop body (such as the number of operations, see Table ...) collected by the compiler and the dynamic information (such as the number of cores used to execute the loop) as provided by the runtime system is used to feed a logistic regression model enabling a runtime decision which ensures best possible performance of the loop under consideration. 

The presented method relies on a compiler-based source-to-source transformation. The compiler transforms certain loops which were annotated by the user by providing special execution policies -- `par_if` `make_prefetcher_policy` and `adaptive_chunk_size` -- into code controlling runtime behavior. This transformed code instructs the runtime system to apply a logistic regression model and to select either an appropriate code path (e.g. parallel or sequential loop execution) or certain parameters for the loop execution itself (e.g. chunk size or prefetching distance).

We briefly discuss these learning models in the following sections. 

### Binary Logistic Regression Model

In order to select the optimum execution policy (sequential or parallel) for a loop, we implemented a binary logistic regression model in HPX which analyzes the static information extracted from the loop by the compiler and the dynamic information as provided by the runtime. In this model, the weights parameters having `k` features ![eq 1](https://latex.codecogs.com/gif.latex?W%5ET%20%3D%20%5B%5Comega%20_1%2C%20%5Comega%20_2%2C%20...%2C%20%5Comega%20_%7Bk%7D%5D) are determined by considering features values ![eq 2](https://latex.codecogs.com/gif.latex?x_r%20%28i%29) of each experiment ![eq 3](https://latex.codecogs.com/gif.latex?X_i%20%3D%20%5B1%2C%20x_1%20%28i%29%2C%20...%2C%20x_%7Bk%7D%20%28i%29%5D%5ET) which minimize the log-likelihood of the Bernoulli distribution value as follow:

![eq 4](https://latex.codecogs.com/gif.latex?%5Cmu_i%20%3D%201/%281%20+%20e%5E%7B-W%5ET%20X_i%7D%29)

 
The values of ![eq 5](https://latex.codecogs.com/gif.latex?%5Comega) are updated in each step $t$ as follows:

![eq 6](https://latex.codecogs.com/gif.latex?%5Comega_%7Bt%20+%201%7D%20%3D%20%28X%5ETS_tX%29%5E%7B-1%7DX%5ET%28S_tX%5Comega_t%20+%20y%20-%20%5Cmu_t%29)



, where `S` is a diagonal matrix with ![eq 7](https://latex.codecogs.com/gif.latex?S%28i%2C%20i%29%20%3D%20%5Cmu_i%281%20-%20%5Cmu_i%29). The output is determined by considering the following decision rule:

![eq 8](https://latex.codecogs.com/gif.latex?y%28x%29%20%3D%201%20%5Clongleftrightarrow%20p%28y%20%3D%201%20%7C%20x%29%20%3E%200.5)

### Multinomial Logistic Regression Model

In order to predict the optimum values for the chunk size and the prefetching distance, we implemented a multinomial logistic regression model in HPX which also analyzes the static information extracted from the loop by the compiler and the dynamic information as provided by the runtime. Assume that we have `N` experiments that are classified in `C` classes and each has `K` features. In this method, the posterior probabilities are computed by using a softmax transformation of the feature variables linear functions for an experiment `n` with a class `c` as follow:

![eq 9](https://latex.codecogs.com/gif.latex?y_%7Bnc%7D%20%3D%20y_c%28X_n%29%20%3D%20%5Cfrac%7Bexp%28W_c%5ETX_n%29%7D%7B%5Csum_%7Bi%3D1%7D%5E%7BC%7D%20exp%28W_i%5ETX_n%29%7D)

The cross entropy error function is defined as follows:

![eq 10](https://latex.codecogs.com/gif.latex?E%28%5Comega_1%2C%20%5Comega_2%2C%20...%2C%20%5Comega_C%29%20%3D%20-%5Csum_%7Bn%3D1%7D%5E%7BN%7D%5Csum_%7Bc%3D1%7D%5E%7BC%7D%20t_%7Bnc%7D%20lny_%7Bnc%7D)


, where `T` is a ![eq 11](https://latex.codecogs.com/gif.latex?N%5Ctimes%20C) matrix of target variables with ![eq 12](https://latex.codecogs.com/gif.latex?t_%7Bnc%7D) elements. The gradient of `E` is computed as follows:

![eq 13](https://latex.codecogs.com/gif.latex?%5Cnabla_%7B%5Comega_%7Bc%7D%7DE%28%5Comega_1%2C%20%5Comega_2%2C%20...%2C%20%5Comega_C%29%20%3D%20%5Csum_%7Bn%3D1%7D%5E%7BN%7D%28y_%7Bnc%7D%20-%20t_%7Bnc%7D%29X_n)

In this method, we use the gradient desecnt method to update the weights values in each step:

![eq 14](https://latex.codecogs.com/gif.latex?%5Comega_%7Bnew%7D%20%3D%20%5Comega_%7Bold%7D%20-%20%5Calpha%20%5Ctimes%20%5Cnabla%20E%28%5Comega%29)

where ![eq 15](https://latex.codecogs.com/gif.latex?%5Calpha) is `0.001` here.

More details can be found in:

C Bishop. Pattern recognition and machine learning (information science and statistics), 1st edn. 2006. corr. 2nd printing edn. Springer, New York, 2007.

## Features Set

Initially, we selected `10` static features to be collected at compile time and `2` dynamic features to be determined at runtime to be evaluated by our learning model.

|static/dynamic | Information |
|---|---|
| dynamic | number of threads |
| dynamic | number of iterations |
| static | number of total operations |
| static | number of float operation |
| static | number of comparison operations |
| static | deepest loop level |
| static | number of integer variables |
| static | number of float variables |
| static | number of if statements |
| static | number of if statements within inner loops |
| static | number of function calls |
| static | number of function calls within inner loops |

To avoid overfitting the model, we chose `6` first critical features in the Table to include in the actual decision tree classification, which reduces the initial feature set in a tree building process based on information gain value. This value is used to decide which feature to be selected for spliting data at each step in a tree building process. 

## Training Data 

To design an efficient learning model that could be able to cover various cases, we collected over $300$ training data sets (see `/algorithms/inputs`) by analyzing different applications that implement `par_if` `make_prefetcher_policy`, or `adaptive_chunk_size`} on their loops. Both the binary and multinomial logistic regression models are implemented in C++ that can be found in `/algorithms`. These models are designed based on the collected data, in which the values of ![eq 16](https://latex.codecogs.com/gif.latex?%5Comega) are determined whenever the sum of square errors reaches its minimum value. Then they are stored in an output file located at `/learning_weights` that will be used for predicting the optimal execution policy, chunk size, or prefetching distance at runtime. 

It should be noted that the multinomial logistic regression model must be initialized with the allowed boundaries for the chunk size and prefetching distance in order to choose an efficient value. In this study we selected `0.001`, `0.01`, `0.1`, and `0.5` of the number of iterations of a loop as chunk size candidates and `10`, `50`, `100`, `1000` and `5000` cache lines as prefetching distance candidates. These candidates are validated with different tests and based on their results, they are selected. Also, they are already included in the implementation of the proposed technique discussed in the next section and it is not required for the users to include them manually. This learning step can be done offline, which also doesn't add any overhead at compile time nor does at runtime.

## Trained Weights

We gathered the rained weights from implementing learning model on our own machine on the inputs found at `algorithms/inputs` in `/learning_weights`:

	weights_chunk_size.dat
	weights_prefetcher_distance_factor.dat
	weights_seq_par.dat

These weights are trained using `Clang 4.0.0` and `HPX V0.9.99` on the test machine with two `Intel Xeon E5-2630` processors, each with `8` cores clocked at `2.4GHZ` and `65GB` of main memory. 

- It should be note that these weights may be different with the one you may get from training on your machine.

## Instructions

To run these provided algorithms, compile your code with:

	g++ -std=c++11 -I /path/to/eigen3/ main.cpp -o main.o
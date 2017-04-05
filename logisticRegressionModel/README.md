
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







## Training Data 

## Trained Weights

## Instructions

g++ -std=c++11 -I /usr/bin/include/eigen3/ main.cpp -o main.o
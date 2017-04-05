
# Table of Contents
1. [Logistic Regression Model](README.md#hpx-clangtool)
2. [Training Data](README.md#training-data)
3. [Trained Weights]((README.md#trained-weights)
4. [Instructions](README.md#instructions)

## Logistic Regression Model

We use the binary and multinomial logistic regression models to select the optimum execution policy, chunk size, and prefetching distance for certain HPX loops based on both, static and dynamic information, with the goal of minimizing execution time. Here, the static information about the loop body (such as the number of operations, see Table ...) collected by the compiler and the dynamic information (such as the number of cores used to execute the loop) as provided by the runtime system is used to feed a logistic regression model enabling a runtime decision which ensures best possible performance of the loop under consideration. 

The presented method relies on a compiler-based source-to-source transformation. The compiler transforms certain loops which were annotated by the user by providing special execution policies -- par_if` `make_prefetcher_policy` and `adaptive_chunk_size` -- into code controlling runtime behavior. This transformed code instructs the runtime system to apply a logistic regression model and to select either an appropriate code path (e.g. parallel or sequential loop execution) or certain parameters for the loop execution itself (e.g. chunk size or prefetching distance).

We briefly discuss these learning models in the following sections. 

### Binary Logistic Regression Model

In order to select the optimum execution policy (sequential or parallel) for a loop, we implemented a binary logistic regression model in HPX which analyzes the static information extracted from the loop by the compiler and the dynamic information as provided by the runtime. In this model, the weights parameters having `k` features ![eq 1](https://latex.codecogs.com/gif.latex?W%5ET%20%3D%20%5B%5Comega%20_1%2C%20%5Comega%20_2%2C%20...%2C%20%5Comega%20_%7Bk%7D%5D) are determined by considering features values `x_r (i)` of each experiment $X_i = [1, x_1 (i), ..., x_{k} (i)]^T$ which minimize the log-likelihood of the Bernoulli distribution value as follow:
\begin{equation} 
\mu_i = 1/(1 + e^{-W^T X_i}). 
\end{equation}
 
The values of $\omega$ are updated in each step $t$ as follows:
\begin{equation} \label{eq1}
\omega_{t + 1} = (X^TS_tX)^{-1}X^T(S_tX\omega_t + y - \mu_t)
\end{equation}

\noindent
, where $S$ is a diagonal matrix with $S(i, i) = \mu_i(1 - \mu_i)$. The output is determined by considering the following decision rule:
\begin{equation} 
\label{eq2}
y(x) = 1 \longleftrightarrow p(y = 1 | x) > 0.5
\end{equation}

\subsection{Multinomial Logistic Regression Model }
\label{sec:mult}

In order to predict the optimum values for the chunk size and the prefetching distance, we implemented a multinomial logistic regression model \cite{bishop1} in HPX which also analyzes the static information extracted from the loop by the compiler and the dynamic information as provided by the runtime. Assume that we have $N$ experiments that are classified in $C$ classes and each has $K$ features. In this method, the posterior probabilities are computed by using a softmax transformation of the feature variables linear functions for an experiment $n$ with a class $c$ as follow:

\begin{equation}
\label{eq3}
y_{nc} = y_c(X_n) = \frac{exp(W_c^TX_n)}{\sum_{i=1}^{C} exp(W_i^TX_n)}
\end{equation}

\noindent
The cross entropy error function is defined as follows:

\begin{equation}
\label{eq4}
E(\omega_1, \omega_2, ..., \omega_C) = -\sum_{n=1}^{N}\sum_{c=1}^{C} t_{nc} lny_{nc}
\end{equation}

\noindent
, where T is a $N\times C$ matrix of target variables with $t_{nc}$ elements. The gradient of $E$ is computed as follows:

\begin{equation}
\label{eq5}
\nabla_{\omega_{c}}E(\omega_1, \omega_2, ..., \omega_C) = \sum_{n=1}^{N}(y_{nc} - t_{nc})X_n
\end{equation}

In this method, we use the Newton-Raphson method \cite{nr} to update the weights values in each step:

\begin{equation}
\label{eq6}
\omega_{new} = \omega_{old} - H^{-1}\nabla E(\omega)
\end{equation}

\noindent
where $H$ is the Hessian matrix defined as follows:

\begin{equation}
\label{eq7}
\nabla_{\omega_{i}}\nabla_{\omega_{j}} E(\omega_1, \omega_2, ..., \omega_C)=\sum_{n=1}^{N} y_{ni}(I_{ij} - y_{nj})X_n X^T_n %i,j\in\{1,...,C\}
\end{equation}

Since the Hessian matrix for this regression model is positive definite, its error function has a unique minimum. At the end of this iterative process, a set of weights is determined for a learning model that gives the best classification on a given set of training data. More details can be found in \cite{bishop2}. 







## Training Data 

## Trained Weights

## Instructions

g++ -std=c++11 -I /usr/bin/include/eigen3/ main.cpp -o main.o
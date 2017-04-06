
# Table of Contents
1. [hpxML](README.md#hpxML)
2. [Instructions](README.md#instructions)


## hpxML
The performance of many parallel applications depends on loop-level parallelism. However, manually parallelizing all loops may result in degrading parallel performance, as some of them cannot scale desirably to a large number of threads. In addition, the overheads of manually tuning loop parameters might prevent an application from reaching its maximum parallel performance. We illustrate how machine learning techniques can be applied to address these challenges. In hpxML project, we develop a framework that is able to automatically capture the static and dynamic information of a loop. Moreover, we advocate a novel method for determining the execution policy, chunk size, and prefetching distance of an HPX loop to achieve best possible performance by feeding static information captured during compilation and runtime-based dynamic information to our learning model.

The goal of this project is to combine machine learning methods, compiler transformations, and runtime introspection in order to maximize the use of available resources and to minimize execution time of the loops. Its design and implementation has several steps categorized as follow: 

1. Special Execution Policies and Parameters
2. Designing the Learning Model and Feature Extraction
3. Learning Model Implementation

### Special Execution Policies and Parameters

We introduce two new HPX execution policies and one new HPX execution policy parameter, which enables the weights gathered by the learning model to be applied on the loop: `par_if` and `make_prefetcher_policy`. These policies instrument executors to be able to consume the weights produced by a binary logistic regression model, which is used to select the execution policy corresponding to the optimal code path to execute (sequential or parallel), and a multinomial logistic regression model, which is used to determine an efficient prefetching distance. Additionally we created an new execution policy parameter, `adaptive_chunk_size`, which uses a multinomial logistic regression model to determine an efficient chunk size. We have created a new special ClangTool which recognizes these annotated loops and transform them into equivalent code which instructs the runtime to apply the described regression models. More details can be found in `/ClangTool`.

### Designing the Learning Model and Feature Extraction

We use the binary and multinomial logistic regression models to select the optimum execution policy, chunk size, and prefetching distance for certain HPX loops based on both, static and dynamic information, with the goal of minimizing execution time. More details can be found in `/logisticRegressionModel`.

### Learning Model Implementation

We propose three new techniques that implement binary and multinomial logistic regression models at runtime:

1. We propose a new function `seq_par` (`/hpxml/hpx/parallel/seq_or_par.hpp`) that passes the extracted features for a loop that uses `par_if` as its execution policy. In this technique, a Clang compiler automatically adds extra lines within a user's code as below that allows the runtime system to decide whether execute a loop sequentially or in parallel based on the return value of `seq_par`. 
	
		Before compilation:
		for_each(par_if,range.begin(),range.end(),lambda);

		After compilation:
		if(seq_par(EXTRACTED_STATICE_DYNAMIC_FEATURES))
		for_each(seq, range.begin(),range.end(),lambda);  
		else
		for_each(par, range.begin(),range.end(),lambda);
		...

If the output is `false` the loop will execute sequentially and if the output is `true` the loop will execute in parallel. This function takes the weights extracted during compilation and the values polled at runtime as inputs. 

2. We propose a new function `chunk_size_determination` (`/hpxml/hpx/parallel/chunk_size_determination.hpp`) that passes the extracted features for a loop that uses `adaptive_chunk_size` as its execution policy's parameter. In this technique, a Clang compiler changes a user's code automatically as below that makes runtime system to choose an optimum chunk size based on the output of `chunk_size_determination` that is based on the chunk size candidate's probability. In addition to the extracted compile time static information, number of threads and number of iterations are also measured and included in this function. 

		Before compilation:
		for_each(policy.with(adaptive_chunk_size()),range.begin(),
			range.end(),lambda); 

		After compilation:
		for_each(policy.with(chunk_size_determination(EXTRACTED_STATICE_DYNAMIC_FEATURES))), 
			range.begin(),range.end(),lambda);
		...

3. We propose a new function `prefetching_distance_determination` (`/hpxml/hpx/parallel/prefetching_distance_determination.hpp`) that passes the extracted features for a loop that uses `make_prefetcher_policy` as its execution policy. In this technique, a Clang compiler changes a user's code automatically as below that makes runtime system to choose an optimum prefetching distance based on the output of `prefetching_distance_determination`. Same as `seq_par` and `chunk_size_determination`, this function includes the compiler extracted static information in addition to dynamically measured number of threads and number of iterations.	

		Before compilation:
		for_each(make_prefetcher_policy(policy, 
			prefetching_distance_factor, ...), 
			range.begin(),range.end(),lambda); 	

		After compilation:
		for_each(make_prefetcher_policy(policy, 
			prefetching_distance_determination(EXTRACTED_STATICE_DYNAMIC_FEATURES), ...), 
			range.begin(),range.end(),lambda); 
		...

More details can be found in our recent published paper:



## Instructions

1. Install HPX (see instructions in `/hpxml`)
2. Install Clang 4.0.0 add our new ClangTool (see instructions in `/ClangTool`)
3. Design learning model (see instructions in `/logisticRegressionModel`)


Don't forget to join our IRC `#ste||ar` if you need any help :) 
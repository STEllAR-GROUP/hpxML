
# Table of Contents
1. [HPX ClangTool](README.md#hpx-clangtool)
2. [Instructions](README.md#instructions)

## HPX ClangTool

We introduce a new ClangTool `LoopConvert.cpp` using `LibTooling` as a custom compiler pass to be executed by the Clang compiler, which is intended to collect the static features at compile time. The logistic regression model is implemented as a learning model that considers these captured features and the dynamic information as provided by the runtime system for predicting efficient parameters for an hpx parallel algorithm. 

For implementing this learning model on a loop, we propose new execution policies and parameters, `par_if` `make_prefetcher_policy` and `adaptive_chunk_size`. As a results, the Clang compiler transforms certain loops which were annotated by the user by providing these special execution policies into code controlling runtime behavior. This transformed code instructs the runtime system to apply a logistic regression model and to select either an appropriate code path (e.g. parallel or sequential loop execution) or certain parameters for the loop execution itself (e.g. chunk size or prefetching distance). This technique enables a runtime decision which ensures best possible performance of the loop under consideration. 

## Instructions

Add a new ClangTool `LoopConvert.cpp` in a new directory loop-convert as follow:

	cd /path/to/clang-llvm/llvm/
	mkdir tools/clang/tools/extra/loop-convert
	mv /path/to/LoopConvert.cpp tools/clang/tools/extra/loop-convert/
	mv /path/to/CMakeLists.txt tools/clang/tools/extra/loop-convert/
    echo 'add_subdirectory(loop-convert)' >> tools/extra/CMakeLists.txt


Compile our new tool as follow. We recommend using `Ninja` for this process. 

	cd /path/to/clang-llvm/build
	ninja loop-convert

More details about building tools using LibTooling and LibASTMatchers can be found in `https://clang.llvm.org/docs/LibASTMatchersTutorial.html`

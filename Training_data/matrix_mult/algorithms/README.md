# Data Generations

This directory allows for automatic data generation. To generate data, functions located in the algorithms/ folder are called in main.cpp.
These functions apply a for_each loop on a given lambda functions and outputs the execution time for different chunk_size candidates. The results
in a file located in the files/ folder. Here are the current functions:

1. Rand_Ponderated_Sum()
1. Swap()
1. Stream()

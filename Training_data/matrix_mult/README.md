# Data Generations

This directory allows for data generation. To generate data, lambda functions are run with different chunk-size candidates and the execution times are measured and outputted.

here are the different function which are defines in headers files at algorithm/dynamic_and_execution/ here are the different functions

1. Rand_Ponderated_Sum()
1. Swap()
1. Finite_Diff_Step()
1. Stream()
1. Max_Sum_Row()
1. Cosine()
1. Matrix_Vector_Mult()
1. Diadic_Prod()
1. Triples
1. Matrix_Matrix_Mult()
1. Tensor_generator()

More can easily be added.

Experiments are scheduled using the *train.sbatch* file using 
```
sbatch train.sbatch training.txt
```
training.txt is a file where every line is structured like the following

```
function_name,header_file_index,number_of_iterations_number_of_threads
```


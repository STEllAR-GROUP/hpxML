#!/usr/bin/env bash

#SBATCH -o glaberge_%j.out
#SBATCH -t 0-10:00
#SBATCH -p marvin
#SBATCH -N 1
export TCMALLOC_LARGE_ALLOC_REPORT_THRESHOLD=30000000000
for line in `cat $1`
do
	#function and iterations read
	param1=`echo $line | cut -d "," -f 1`
	param2=`echo $line | cut -d "," -f 2`
	param3=`echo $line | cut -d "," -f 3` 
	param4=`echo $line | cut -d "," -f 4`
	#find the right line
#	line1=`grep "//feature extraction ${param1}" "algorithms/static/${param2}_loop_level.cpp" -n | tr -dc '0-9'`
#	let "line1=line1+1"
	#uncomment the right for_each call
#	sed -i "${line1}s|//|  |" "./algorithms/static/${param2}_loop_level.cpp"
        
	#define lambda_inner_iteration
#	line2=`grep "#define lambda_inner_iteration 0" "algorithms/static/${param2}_loop_level.cpp" -n | tr -dc '1-9'`
#	sed -i "${line2}s|0|${param3} |" "./algorithms/static/${param2}_loop_level.cpp"
	
	#use the clang tool to extract static features
#	~/compile/cfe-6.0.0.src/build/bin/loop-convert "algorithms/static/${param2}_loop_level.cpp" -- -Iinclude `./include.sh`

        
	#run the main.cpp to extract dynamic features and execution timesrun ~/hpxML/Training_data/matrix_mult/build/data ${param1} ${param3} -- -threads=8
	srun ~/hpxML/Training_data/matrix_mult/build/data ${param1} ${param3} "--hpx:threads=${param4}"
	#comment the right for_each call
#	sed -i "${line1}s|  |//|" "./algorithms/static/${param2}_loop_level.cpp"
	
	#define lambda_innter_iteration 0
#	sed -i "${line2}s|${param3}|0|" "./algorithms/static/${param2}_loop_level.cpp"
done


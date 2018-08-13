#!/usr/bin/env bash

export TCMALLOC_LARGE_ALLOC_REPORT_THRESHOLD=30000000000

for i in `seq 1 278`
do
	function=`sed -n "${i}p" $1`
	prediction=`sed -n "${i}p" $2`

	param1=`echo ${function} | cut -d "," -f 1`
	param2=`echo ${function} | cut -d "," -f 3`
	param3=`echo ${function} | cut -d "," -f 4`


	#run the main.cpp to extract dynamic features and execution timesrun ~/hpxML/Training_data/matrix_mult/build/data ${param1} ${param3} -- -threads=8
	srun ./build/times ${param1} ${param2} ${prediction} "--hpx:threads=${param3}"
done

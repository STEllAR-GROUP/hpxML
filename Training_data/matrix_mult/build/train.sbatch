#!/usr/bin/env bash

#SBATCH -o glaberge_%j.out
#SBATCH -t 0-30:00
#SBATCH -p beowulf
#SBATCH -N 10
for line in `cat $1`
do
	param1=`echo $line | cut -d "," -f 1`
	param2=`echo $line | cut -d "," -f 2`
	param3=`echo $line | cut -d "," -f 3` 
	srun ~/hpxML/Training_data/matrix_mult/build/name ${param1} ${param2} ${param3}
done

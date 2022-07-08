#!/bin/bash

#PBS -l walltime=00:01:00,nodes=7:ppn=2
#PBS -N LfiTsarukB02-004b
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 6 ./a.out 1000
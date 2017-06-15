#!/usr/bin/env bash
#PBS -l nodes=1:ppn=20:K40c
#PBS -l partition=gpu
#PBS -l walltime=02:00:00
#PBS -j oe
#PBS -m ae

cd $PBS_O_WORKDIR

source $VSC_DATA/miniconda3/bin/activate tensorflow

time python gan.py --train --output "output.${PBS_JOBID}"

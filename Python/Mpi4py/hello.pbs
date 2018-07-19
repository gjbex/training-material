#!/usr/bin/env bash
#PBS -A lpt1_sysadmin
#PBS -l nodes=2:ppn=20
#PBS -l walltime=00:02:00

module purge
module load Python/2.7.11-foss-2016a

cd $PBS_O_WORKDIR

export PYTHONPATH="${VSC_HOME}/python_lib/lib/python2.7/site-packages:${PYTHONPATH}"

mpirun --map-by core python ./hello.py --iters 20 --sleep 5.0

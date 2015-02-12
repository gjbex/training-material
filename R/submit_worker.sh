#!/bin/bash -l

module load worker/1.5.1-intel-2014a

wsub -batch compute_parameterized.pbs -data data.csv \
     -walltime=00:15:00 -nodes=1:ppn=4

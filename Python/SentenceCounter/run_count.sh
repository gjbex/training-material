#!/bin/bash

source /apps/leuven/etc/bash.bashrc
module load openmpi/1.4.3_intel python/2.7.1

mpirun -np 4 ./count_sentences_par.py $@


#!/bin/bash

module purge
module load Python/2.7.6-foss-2014a

mpirun -np 4 ./ring.py

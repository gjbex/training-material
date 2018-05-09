#!/usr/bin/env bash

source setup.sh

export LD_PRELOAD=libVTfs.so
mpirun -n 4 ./deadlock_f90.exe

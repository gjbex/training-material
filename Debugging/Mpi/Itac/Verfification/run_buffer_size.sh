#!/usr/bin/env bash

source setup.sh

make

if [[ $? -eq 0 ]]
then
    mpirun -np 4 -check-mpi ./buffer_size.exe
fi

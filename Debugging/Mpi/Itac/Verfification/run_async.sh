#!/usr/bin/env bash

source setup.sh

make

if [[ $? -eq 0 ]]
then
    mpirun -genv I_MPI_SHM_LMT=shm -np 2 -check-mpi ./async.exe
fi

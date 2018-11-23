#!/usr/bin/env bash

source setup.sh

make

export SUPPRESS_FILE="/opt/intel/itac/2018.1.017/intel64/lib/impi.supp"
if [[ $? -eq 0 ]]
then
    mpirun -genv I_MPI_SHM_LMT=shm -np 2 -check-mpi -l \
        valgrind --suppressions="${SUPPRESS_FILE}" ./async.exe
fi

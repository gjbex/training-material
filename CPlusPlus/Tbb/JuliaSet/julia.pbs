#!/usr/bin/env bash
#PBS -l nodes=1:ppn=20
#PBS -l pmem=3gb
#PBS -l walltime=00:05:00
#PBS -j oe

if [[ -n "${PBS_O_WORKDIR}" ]]
then
    cd "{$PBS_O_WORKDIR}"
fi

module purge
module try-load intel

>&2 echo "serial:"
time ./julia.exe 16384 > /dev/null

>&2 echo "TBB:"
time ./julia_tbb.exe 16384 > /dev/null

>&2 echo "OpenMP:"
time ./julia_omp.exe 16384 > /dev/null

>&2 echo "OpenMP taskloop:"
time ./julia_tasks_omp.exe 16384 > /dev/null

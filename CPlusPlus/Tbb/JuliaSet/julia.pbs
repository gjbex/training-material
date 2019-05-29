#!/usr/bin/env bash
#PBS-A lp_sys
#PBS -l nodes=1:ppn=36
#PBS -l pmem=5gb
#PBS -l walltime=00:05:00
#PBS -j oe

if [[ -n "${PBS_O_WORKDIR}" ]]
then
    cd "${PBS_O_WORKDIR}"
fi

module purge
module try-load intel

>&2 echo "serial:"
time ./julia.exe 16384 > julia_serial.txt

>&2 echo "TBB:"
time ./julia_tbb.exe 16384 > julia_tbb.txt

>&2 echo "OpenMP:"
time ./julia_omp.exe 16384 > julia_omp.txt

>&2 echo "OpenMP taskloop:"
time ./julia_tasks_omp.exe 16384 > julia_tasks_omp.txt

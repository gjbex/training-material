#!/usr/bin/env bash
#PBS -A lp_sys
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

echo "serial:"
./julia.exe 16384 > julia_serial.txt

echo "TBB:"
./julia_tbb.exe 16384 > julia_tbb.txt

echo "OpenMP default:"
./julia_omp.exe 16384 > julia_omp_default.txt

echo "OpenMP staic:"
OMP_SCHUDULE=staic ./julia_omp.exe 16384 > julia_static_omp.txt

echo "OpenMP dynamic:"
OMP_SCHUDULE=dynamic ./julia_omp.exe 16384 > julia_dynamic_omp.txt

echo "OpenMP guided:"
OMP_SCHUDULE=guided ./julia_omp.exe 16384 > julia_guided_omp.txt

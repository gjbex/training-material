#!/usr/bin/env bash
#PBS -l nodes=1:ppn=20
#PBS -l pmem=3gb
#PBS -l walltime=00:05:00
#PBS -j oe

cd $PBS_O_WORKDIR

INTEL_BASEDIR=/apps/leuven/thinking/2015a/software/intel
INTEL_VERSION=cluster_studio_2016
INTEL_DIR="$INTEL_BASEDIR/$INTEL_VERSION"

source $INTEL_DIR/bin/compilervars.sh intel64
source $INTEL_DIR/tbb/bin/tbbvars.sh intel64

>&2 echo "serial:"
time ./julia.exe 16384 > /dev/null

>&2 echo "TBB:"
time ./julia_tbb.exe 16384 > /dev/null

>&2 echo "OpenMP:"
time ./julia_omp.exe 16384 > /dev/null

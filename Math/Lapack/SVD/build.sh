#!/bin/bash -l

module load intel/2014a
module load HDF5/1.8.12-intel-2014a-serial

FFLAGS="-O2 -g -openmp -I${MKLROOT}/include"
MATH_LIBS="-L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -lpthread -lm"

make F90=ifort FFLAGS="${FFLAGS}" HDF5_DIR="${EBROOTHDF5}" \
     MATH_LIBS="${MATH_LIBS}" all

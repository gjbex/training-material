#!/bin/bash -l

source setup_intel.sh

make F90=ifort OMP=-openmp

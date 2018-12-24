# JuliaProcesses

Illustration of optimizing application parameters by running
processes.

## What is it?

  1. `julia_omp.cpp`: C++ application that compute the Julia set
    fractal, using OpenMP for parallelization.  The parallel
    for-loop schedule is `runtime`, and hence can be controled
    using the `OMP_SCHEDULE` environment variable. Timing
    information is writting to standard error.
  1. `Makefile`: make file to build the Julia set application.
  1. `julia_optimize.py`: Python script to find optimal OpenMP
    schedule, chunk size and number of threads for the Julia set
    application.
  1. `julia_gcc.pbs`: PBS script to optimize the Julia set
    applciation parameters as a job (GCC compiler).
  1. `julia_intel.pbs`: PBS script to optimize the Julia set
    applciation parameters as a job (Intel compiler).

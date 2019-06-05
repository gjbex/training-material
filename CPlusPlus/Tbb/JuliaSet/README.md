# Tbb
Implementation of the Julia set computatino using Intel Threading Building Blocks (TBB) and
OpenMP.

## What is it?
1. `julia_abs.cpp`: serial Julia set implementation as base case.
1. `julia.cpp`: serial Julia set implementation as base case, slightly faster by avoiding
    the complex norm function..
1. `julia_tbb.cpp`: TBB implementation of Julia set.
1. `julia_omp.cpp`: OpenMP implementation of Julia set.
1. `julia_tasks_omp.cpp`: OpenMP tasks implementation of Julia set
    (*Note:* doesn't work with Intel 2018a).
1. `Makefile`: make file to build the applications.
1. `plot_julia.sh`: bash script to plot the Julia set using `gnuplot`.

# Tbb
Intel Threading Building Blocks (TBB) is a library for multithreaded
programming in C++.

## What is it?
1. `simple_cpp`: simple application illustrating a `parallel_for`
    loop over a `valarray`.
1. `julia.cpp`: serial Julia set implementation as base case.
1. `julia_tbb.cpp`: TBB implementation of Julia set.
1. `Makefile`: make file to build the applications.
1. `plot_julia.sh`: bash script to plot the Julia set using `gnuplot`.
1. `build.sh`: bash script to conveniently build the application on
    the VSC cluster.
1. `run.sh`: bash script to conveniently run the application on
    the VSC cluster.

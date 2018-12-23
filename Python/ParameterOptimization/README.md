# ParameterOptimization

Here a number of implementations of algorithms to find optimal
values a in parameter space are explored.

## What is it?

  1. `parameter_optimization.ipynb`: Jupyter notebook
    illustrating the hyperopt and the BayianOptimization module.
  1. `continuous_process.py`: Python script that takes x and y
    y values as `--x` and `--y` options, and prints the value of
    the function to optimize to standard output.
  1. `hyperopt_imize.py`: Illustrates using the hyperopt TPE
    algorithm to optimize the parameters for an application, i.e.,
    `continuous_process.py`.
  1. `julia_omp.cpp`: C++ application that compute the Julia set
    fractal, using OpenMP for parallelization.  The parallel
    for-loop schedule is `runtime`, and hence can be controled
    using the `OMP_SCHEDULE` environment variable. Timing
    information is writting to standard error.
  1. `Makefile`: make file to build the Julia set application.
  1. `julia.pbs`: PBS script to run the Julia set applciation
    as a job.
  1. `julia_optimize.py`: Python script to find optimal OpenMP
    schedule, chunk size and number of threads for the Julia set
    application.

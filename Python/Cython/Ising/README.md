# Ising
Simulation of a 2D Ising system.

## What is it?
1. `averager.py`: class making it easy to perform multiple independent
    simulation runs, and averaging the relevant quantities produced by
    these runs.  When multiple cores ara available, runs will be done in
    parallel.
1. `ising.py`: pure Python implmentation of the 2D Ising system.
1. `ising_cython.py`: Cython implmentation of the 2D Ising system.
1. `ising_sim.py`: dirver for running simulations to cmopute relevant
    ensemble averages.  Can switch between implementation for timing
    comparisons.
1. `runner.py`: various runner implementation that execute s single run of
    the 2D Ising system for various purposes.
1. `util.py`: helper utilities.
1. `setup.py`: build file for Cython version.
1. `Makefile`: make file to build Cython implementation and run the
    profiler.

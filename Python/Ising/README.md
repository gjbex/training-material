# Ising
Simulation of a 2D Ising system with an emphasis on visualization.

## What is it?
1. `averager.py`: class making it easy to perform multiple independent
    simulation runs, and averaging the relevant quantities produced by
    these runs.  When multiple cores ara available, runs will be done in
    parallel.
1. ``domain_counter.py`: for a given Ising system configuration,
    identify and count the domains.
1. `ising_demo.py`: driver script to do various experiments such as
    doing a single run to produce the magnetization and the energy as
    a function of time, creating a movie of the system as a function of
    time, creating a heatmap of the activity, i.e., the rate of spin
    flips per unit of time, or running until equilibrium is reached.
1. `ising_linear.py`: alternative implementation (inferior to the
    default Python) to be a more fair comparison with the C++
    implementation.
1. `ising.py`: pure Python implmentation of the 2D Ising system.
1. `ising_sim.py`: dirver for running simulations to cmopute relevant
    ensemble averages.  Can switch between implementation for timing
    comparisons.
1. `runner.py`: various runner implementation that execute s single run of
    the 2D Ising system for various purposes.
1. `util.py`: helper utilities.
1. `src`: C++ implementation of the 2D Ising system, as well as a SWIG
    file to generate Python wrapper code.
1. `build.sh`: build script that will run SWIG, build the shared
    library, and copy the library and the generated Python module to
    the working directory.

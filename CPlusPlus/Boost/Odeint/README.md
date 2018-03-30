# Odeint
Some illustrations of using the Boost Odeint C++ library solving a set
of ordinary differential equations).

## What is it?
1. `lorenz.cpp`: the Lorenz attractor implemented using the Boost
    ordinary differential equation solver.  Also illustrates
    currying (with std::bind) to avoid parameters as global
    variables.
1. `plot_lorentz.plt`: Gnuplot script to plot curve for Lorentz system.
1. `Makefile`: make file to build the code.

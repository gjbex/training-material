# Mpi
Sample code with various problems to explore using a parallel debugger
such as Allinea DDT.

## What is it?
1. `diffusion.f90`: (hopefully) correct version
1. `010_deadlock.f90`: illustrates a deadlock caused by one process not
    participating in a collective operation.
1. `020_no_allocate.f90`: illustrates a crash due to using non-allocated
    array.
1. `030_index_out_of_bounds.f90`: array index out of bounds problem, can
    be detected using memory checking (with, e.g., Allinea DDT).
1. `prototype.f90`: prototype to verify correctness of halo exchange.
1. `Makefile`: make file to build the executables.
1. `setup.sh`: source to set up the environment for build and run (works
    on VSC infrastructure).
1. `build.sh`: sets the environment to build the executables (works on VSC
    clusters).

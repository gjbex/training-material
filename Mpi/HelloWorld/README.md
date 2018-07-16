HelloWorld
==========

Simple Hello World example for MPI.

What is it?
-----------
1. `hello_world.f90`: print rank and size of `MPI_COMM_WORLD` for each
    process, and hello from rank 0.
1. `hello_world_f08.f90`: uses the Fortran 2008 interface, currently only
    implemented by OpenMPI 1.8+, compiled with at least GCC 4.9+.  This
    will only be built for target `f08`.

# OverlappingComputationCommunication
Using non-blocking communication it may be possible to overlap computation
and communication, i.e., initiate a communication, and proceed with a
computation while the communication proceeds in the background, and ending
by checking the completion of the communication at some point.
Note that the MPI implemention has to provide support for this to work.

## What is it?
1. `nonblocking_reduce.c`: an `MPI_Ireduce` call is issued, and a
    computation is performed while the former proceeds.  For benchmarking
    purposes, this is done mulitple times, and compared with the results of
    a similar `MPI_Reduce` call in each iteration.
1. `setup.sh`: source to ensure that the environment is setup correctly
    for build and run.
1. `build.sh`: script that builds the executable(s).
1. `Makefile`: make file for the build.
1. `nonblocking_reduce.pbs`: PBS script to run the `nonblocking_reduce.exe`
    application.

## Note
This works for Intel icc 16.x and Intel MPI 5.1.x.  This is a requirement
of the `setup.sh`.

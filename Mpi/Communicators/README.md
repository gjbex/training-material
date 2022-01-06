# Communicators

This directory has some example code specific to the use of communicators and groups
in MPI.


## What is it?

1. `multi_group.c`: application illustrating using multiple ranges when creating
   groups using `MPI_Group_range_incl`.
1. `intercomm.c`: illustration of an intercommunicator and broadcast and
    reduction operations on them.
1. `Makefile`: make file to build the applications.

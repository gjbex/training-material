# PointToPointFortran
Illustration of issues involving point-to-point MPI communication.

## What is it?
1. `deadlock.f90`: application that will deadlock.
1. `async_send.f90`: application which avoids deadlock by using
    asynchronous send.
1. `data_race.f90`: application that has a data race.
1. `data_race.f90`: application that avoids a data race by using
    `MPI_Wait`.
1. `async_test.f90`: application to check whether the Fortran compiler is
    TS-29113  compliant.
1. `Makefile`: make file to build the code.

## How to use it?
For simplicity these applications works with two processes only, so run
using:
```bash
$ mpirun -np <appl>
```

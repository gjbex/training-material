# Itac
Sample code to illustrate the use of ITAC (Intel Trace Analyzer and
Collector) for debugging purposes.

## What is it?
1. `deadlock.c`: C application that deadlocks due to inappropriate
    order of send/receive calls.
1. `deadlock.f90`: Fortran application that deadlocks due to a missing MPI
    collective call. This will not be compiled with tracing enabled.
1. `run_deadlock_f90.sh`: Bash script to show how to instrument code
    for tracing at runtime by pre-loading the appropriate fail-safe
    tracing library. 
1. `shift.c`: C application that is correct, but inefficient due to
    implicit serialization.
1. `Makefile`: make file to build the applications.
1. `setup.sh`: file to source to setup the environment for using Intel
    compilers and ITAC.
1. `Verification`: illustration of how to use the ITAC libraries for MPI
    verification.

## How to use?
First, check whether the file `setup.sh` has the correct defintions of
the `INTEL_ROOT` and `ITAC_VERSION` to match your environment, adapt as
required.

Source the setup file, i.e.,
```bash
$ source setup.sh`

Build as usual, using make.

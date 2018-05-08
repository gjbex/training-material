# Correctness
This sample code violates the MPI standard in a number of ways, and can
be used to experiment with
[Must](https://doc.itc.rwth-aachen.de/display/CCP/Project+MUST), a tool
to detect a number of issues in MPI code at runtime, or with Intel MPI,
that will report some of these issues by default, or through analyzers
provided by the Intel Trace Analyzer and Collector (ITAC).

## What is it?
1. `buffer_overlap.f90`: send and receive buffers overlap.
1. `buffer_size.f90`: buffer size in collectives doesn't match.
1. `message_init_size.f90`: data and message type differs, undetected by
    Must.
1. `message_size.f90`: send and receive buffers have different sizes in
    peer-to-peer communication.
1. `message_type.f90`: send and receive buffers have different types.
1. `Makefile`: make file to build the applications.
1. `intel_build.sh`: script to build with the Intel compilers and MPI
    implementation.
1. `setup.sh`: Bash code to set up the environment to do an MPI check using
    the Intel MPI and ITAC libraries.

## How to use?

### MUST
To build the applications for checking them with Must, use make:
```bash
$ make
```

To run with Must:
```bash
$ mustrun -np 2 <appl>
```
Use a web browser to view the HTML report.

### Intel MPI and ITAC
To build the application using the Intel tools, use the build script:
```bash
$ ./intel_build.sh
```

To run with ITAC analyzer:
```bash
$ source setup.sh
$ mpirun -check_mpi -np 2 <appl>
```

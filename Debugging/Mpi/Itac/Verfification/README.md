# verification

Sample code to illustrate the use of ITAC (Intel Trace Analyzer and
Collector) for debugging purposes.

## What is it?

1. `buffer_size.c`: C application that uses mismatched buffers for
    collective operation.
1. `Makefile`: make file to build the applications.
1. `setup.sh`: file to source to setup the environment for using Intel
    compilers and ITAC.
1. `run_buffer_size.sh`: Bash script to build and run the application
    to be verified.

## How to use?

First, check whether the file `setup.sh` has the correct defintions of
the `INTEL_ROOT` and `ITAC_VERSION` to match your environment, adapt as
required.

Source the setup file, i.e.,
```bash
$ source setup.sh`

Build as usual, using make, or use `run_buffer_size.sh`.

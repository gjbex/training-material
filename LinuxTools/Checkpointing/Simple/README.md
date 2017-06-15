# Simple
This is a relatively simple test for DMTCP.

## What is it?
1. `file_io.c`: application to checkpoint, I/O is deliberately chosen so
    that page cache may be dirty.
1. `file_io.pbs`: PBS script to start the application.
1. `file_io_restart.pbs`: PBS script to restart the checkpointed application.
1. `Makefile`: make file to build the applications.
1. `verify_io.c`: application to verify correctness of `file_io.exe` output.

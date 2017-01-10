# Pipeline
This is a scenario of a simple workflow with a pipeline.

## What is it?
1. `producer.c`: application that writes data to standard output
    infrequently so that page cache may be dirty.
1. `consumer.c`: application that reads characters from standard input,
    verifies they are the expected ones, and writes them to standard
    output.
1. `workflow.sh`: bash script that implements the pipeline.
1. `workflow.pbs`: PBS script to start the application.
1. `workflow_io_restart.pbs`: PBS script to restart the checkpointed application.
1. `Makefile`: make file to build the applications.
1. `verify_io.c`: application to verify correctness of `file_io.exe` output.

# Checkpointing
Checkpoininting computations can be useful in a number of scenarios.  Here,
some examples of using the DMTCP package is illustrated.

## What is it?
1. `checkpointing.pptx`: Powerpoint presentation on how to use DMTCP in a
    number of scenarios.
1. `Simple`: a simple application to test DMTCP, single-threaded application
    infrequently writing to a file.
1. `Pipeline`: a simple application with a data producers feeding a data
    consumer throught a pipe, while the consumer redirects output to a
    file.
1. `Hybrid`: a hybrid MPI/OpenMP application and PBS scripts to checkpoint
    it when running on a single node.

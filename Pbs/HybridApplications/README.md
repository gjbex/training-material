# HybridApplications
Running hybrid MPI + OpenMP applications requires some care to ensure
that resources are used optimally.  Especially thread pinning can be
an issue.

## What is it?
* `intel.pbs`: PBS script that runs an application with 2 MPI processes,
    each on a compute node, while each process has a parallel region of
    20 threads.  Tested with Intel MPI 5.1.3, icpc 16.0.3.
* `openmpi.pbs`: PBS script that runs an application with 2 MPI processes,
    each on a compute node, while each process has a parallel region of
    20 threads.  Tested with OpenMPI 1.10.2, g++ 4.9.3.

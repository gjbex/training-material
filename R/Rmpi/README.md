# Rmpi
Very simple `Rmpi` example, mostly to verify the package installation.

## What is it?
1. `rmpi.pbs`: PBS script for job submission.
1. `rmpi.R`: R script that spawns slaves, lets them compute and ID
    message to ensure they are running on the expected nodes, and
    has them perform a computation with a broadcasted function.

## Installation of Rmpi
On thinking, using the 2015a software stack, installation is succesful
using:
```
$ module load R/3.3.1-foss-2015a-tcl
$ R
> install.packages('Rmpi', configure.args='--with-Rmpi-type=OPENMPI --with-mpi=/apps/leuven/thinking/2015a/software/OpenMPI/1.8.4-GCC-4.9.2/')
```

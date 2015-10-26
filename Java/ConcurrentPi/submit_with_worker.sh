#!/bin/bash -l

source switch_to_2015a
module load worker/1.6.3-intel-2015a

# submit as worker job, use 4 nodes, compute each work item using 4
# threads, hence with 5 worker slaves per node
wsub -l nodes=4:ppn=20  -threaded 4  \
     -batch precision.pbs  -data precision.dat

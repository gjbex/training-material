#!/usr/bin/env bash
#PBS -A lp_sys
#PBS -l pmem=2gb
#PBS -l walltime=00:05:00
#PBS -j oe

cd $PBS_O_WORKDIR

source switch_to_2018a
module load foss

# verify that OpenMP environment variables have been passed
# using -v options
if [[ -z "$schedule" ]]
then
    (>&2 echo "### error: OpenMP schedule not set")
    exit 1
fi
if [[ -z "$chunk" ]]
then
    (>&2 echo "### error: OpenMP chunk not set")
    exit 1
fi

OMP_SCHEDULE="${schedule},${chunk}"
(>&2 echo "### info: OMP_SCHEDULE=\'${OMP_SCHEDULE}\'")

if [[ -z "$OMP_NUM_THREADS" ]]
then
    (>&2 echo "### error: OpenMP number of threads not set")
    exit 2
else
    (>&2 echo "### info: OMP_NUM_THREADS=\'${OMP_NUM_THREADS}\'")
fi

# ensure the executable is op to date
make all
if [[ $? -ne 0 ]]
then
    (>&2 echo "### error: make failed")
    exit 3
fi

# determine time file name
time_file="julia.pbs.time${PBS_JOBID/\.*/}"

# run application on a sufficiently large matrix, disregarding
# output, timing information is writting to a file
for i in $(seq 3)
do
    ./julia_omp.exe 4096 > /dev/null 2>> "${time_file}"
done

#!/bin/bash -l
#PBS -l nodes=3:ppn=20
#PBS -l walltime=00:30:00

cd $PBS_O_WORKDIR

scheduler_node=$(hostname)
scheduler_port=8786
worker_nodes=$(uniq $PBS_NODEFILE)
worker_launcher="$(pwd)/launch_worker.sh"

echo "launching scheduler: ${scheduler_node}:${scheduler_port}"
./launch_scheduler.sh

echo 'waitling till scheduler launched...'
sleep 15

echo 'starting workers...'
for worker in $worker_nodes;
do
    echo "launching worker on ${worker}"
    ssh $worker $worker_launcher "${scheduler_node}:${scheduler_port}" &
done

echo 'waiting for workers to start and connect'
sleep 15

source "$VSC_DATA/miniconda3/setenv.sh"
source activate science

which python

echo 'starting computation'
time python dask_sum_arrays.py --scheduler ${scheduler_node} \
                               --scheduler_port ${scheduler_port}

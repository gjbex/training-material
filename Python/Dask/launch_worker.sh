#!/bin/bash -l

source "${VSC_DATA}/miniconda3/setenv.sh"
source activate science

nohup dask-worker $1 &

#!/bin/bash

source "${VSC_DATA}/miniconda3/setenv.sh"
source activate science

nohup dask-scheduler &> scheduler.log &

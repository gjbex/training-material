#!/bin/bash -l
#PBS -A lpt2_pilot_2018
#PBS -l nodes=1:ppn=9:gpus=1
#PBS -l partition=gpu
#PBS -l walltime=00:30:00

module purge
module load conda
source activate machine_learning

cd $PBS_O_WORKDIR

jupyter nbconvert \
    --to=notebook \
    --ExecutePreprocessor.timeout=600 \
    --execute \
    mnist_cnn.ipynb

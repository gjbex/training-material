#!/usr/bin/env bash

source switch_to_2015a
module load Armadillo/7.400.2-foss-2015a-Python-2.7.9
module load K40c/2015a
module load CUDA/7.5.18

make CPPFLAGS="-I${EBROOTARMADILLO}/inlude" \
     LDFLAGS="-L${EBROOTARMADILLO}/lib -L${EBROOTCUDA}/lib64" 

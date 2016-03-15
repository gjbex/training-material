#!/bin/bash -l

module purge
module load HDF5/1.8.12-foss-2014a-serial

make HDF5=${EBROOTHDF5}


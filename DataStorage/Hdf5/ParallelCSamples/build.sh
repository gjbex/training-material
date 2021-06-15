#!/bin/bash -l

module purge
module load HDF5/1.10.1-intel-2018a-lustre

HDF5="${EBROOTHDF5}"

./configure \
    CC="mpiicc" \
    CPPFLAGS="-I${HDF5}/include" \
    LDFLAGS="-L${HDF5}/lib" \
    --prefix="${VSC_SCRATCH}/phdf5"

make install

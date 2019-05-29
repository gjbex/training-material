#!/usr/bin/env bash

module purge
module load intel

make CXX=icpc \
     CXXFLAGS="-std=c++14 -O2 -g -Wall -Wremarks"
     OMPFLAGS="-qopenmp" \
     CPPFLAGS="-I$INTEL_DIR/tbb/include" \
     LDFLAGS="-L$INTEL_DIR/tbb/lib/intel64/gcc4.4"

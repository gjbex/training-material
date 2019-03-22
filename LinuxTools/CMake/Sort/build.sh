#!/usr/bin/env bash

mkdir -p build
pushd build || exit 1
cmake -DCatch2_DIR=/usr/local/software/catch2/2.7.0/lib/cmake/Catch2 \
      -DCMAKE_BUILD_TYPE=Debug .. || exit 2
make || exit 3
./tdd_test.exe

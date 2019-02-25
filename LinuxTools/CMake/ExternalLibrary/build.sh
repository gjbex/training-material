#!/usr/bin/env bash

rm -rf build/
mkdir -p build
pushd build
cmake ..
if [[ $? -eq 0 ]]
then
    make
fi

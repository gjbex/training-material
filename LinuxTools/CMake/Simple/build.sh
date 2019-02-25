#!/usr/bin/env bash

mkdir -p build
pushd build
cmake ..
if [[ $? -eq 0 ]]
then
    make
fi

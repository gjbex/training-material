#!/usr/bin/env bash

mkdir -p build && cd build || exit 1
conan install .. || exit 2
cmake .. || exit 3
cmake --build . || exit 4

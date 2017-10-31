#!/usr/bin/env bash

DIST_DIR=$(pwd)
BUILD_DIR='build'

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

"${DIST_DIR}/configure" \
    CC=gcc CFLAGS='-O2 -g'

if [ $? -eq 0 ]
then
    make
fi

#!/usr/bin/env bash

DIST_DIR=$(pwd)
BUILD_DIR='build_debug'

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

"${DIST_DIR}/configure" \
    CC=gcc CFLAGS='-Wall -Wextra -g'

if [ $? -eq 0 ]
then
    make
fi

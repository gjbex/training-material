#!/usr/bin/env bash

SRC_DIR="$(pwd)/src"
REPO_DIR="$(pwd)/repo"

mkdir ${REPO_DIR}
cd ${REPO_DIR}
git init

cp $SRC_DIR/test.c .
cp $SRC_DIR/Makefile .
cp $SRC_DIR/gitignore .gitignore
git add test.c Makefile .gitignore
git commit -m 'Initial version'

for version_nr in $(seq -w 1 7)
do
    cp "$SRC_DIR/fac_0$version_nr.c" fac.c
    cp "$SRC_DIR/fac_0$version_nr.h" fac.h
    git add fac.[ch]
    git commit -m "version $version_nr"
done

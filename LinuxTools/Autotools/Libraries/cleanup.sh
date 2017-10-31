#!/bin/bash

ITEMS="aclocal.m4 autom4te.cache config.log config.status configure \
        compile depcomp install-sh Makefile Makefile.in missing \
        src/Makefile src/Makefile.in src/.deps"

make clean

for file in ${ITEMS}
do
    rm -rf "${file}"
done

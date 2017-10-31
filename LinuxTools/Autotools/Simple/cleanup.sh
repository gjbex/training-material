#!/bin/bash

ITEMS="aclocal.m4 autom4te.cache config.log config.status configure \
        depcomp install-sh Makefile Makefile.in missing \
        src/Makefile src/Makefile.in"

if [ -e Makefile ]
then
    make clean
fi

for file in ${ITEMS}
do
    rm -rf "${file}"
done

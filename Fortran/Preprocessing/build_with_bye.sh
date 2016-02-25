#!/bin/bash

if [ -n ${MODULEPATH+x} ]
then
    module purge
fi
if [ -n ${VSC_HOME+x} ]
then
    module load intel/2015a
fi

make "BYE=-DSAY_BYE" clean all

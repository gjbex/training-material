#!/usr/bin/env bash

source /opt/intel/bin/compilervars.sh intel64
make FC=ifort clean all

if [[ $? -eq 0 ]]
then
    ./side_effects.exe
fi

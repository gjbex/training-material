#!/usr/bin/env bash

make FC=gfortran clean all

if [[ $? -eq 0 ]]
then
    ./side_effects.exe
fi

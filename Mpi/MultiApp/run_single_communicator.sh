#!/bin/bash

module load foss/2015a
make

mpirun -np 3 ./appl1.exe : -np 2 ./appl2.exe

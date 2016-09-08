#!/bin/bash

module load foss/2015a
make

mpirun -np 3 ./server.exe &
echo "waiting a while to ensure port name file is written"
sleep 10
mpirun -np 2 ./client.exe

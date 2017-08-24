#!/bin/bash

ulimit -c 1000000
make clean all
./crash.exe

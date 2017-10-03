#!/usr/bin/env bash

rm *.o
make FFLAGS="-g -O2 -ffpe-trap=zero,overflow,underflow,invalid" \
    APPL=gauss_test_fpe.exe all

rm *.o
make FFLAGS="-g -O2" APPL=gauss_test.exe all

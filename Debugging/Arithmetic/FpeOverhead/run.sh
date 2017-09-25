#!/usr/bin/env bash

echo 'no FPE trapped:'
time ./gauss_test.exe 50000 0.0 1.0

echo '---------------'

echo 'FPE trapped:'
time ./gauss_test_fpe.exe 50000 0.0 1.0

#!/bin/bash -l

mprof run ./primes_lprof.py --n 1000 --quiet
mprof plot

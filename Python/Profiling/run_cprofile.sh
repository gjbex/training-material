#!/bin/bash -l

python -m cProfile -s time ./primes_cprof.py --n 1000 --quiet

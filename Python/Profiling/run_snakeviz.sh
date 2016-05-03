#!/bin/bash -l

python -m cProfile -s time -o primes.prof ./primes_cprof.py --n 1000 --quiet
snakeviz primes.prof

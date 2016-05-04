#!/bin/bash -l

python -m cProfile -s time ./run_quad.py --n 10000 --quiet \
                                         --version $1

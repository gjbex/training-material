#!/bin/bash -l

qsub -v "mean=0.7,stddev=2.0,size=5000" compute_parameterized.pbs

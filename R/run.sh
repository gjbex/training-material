#!/bin/bash -l

if [ -n "${VSC_INSTITUTE}" ]
then
    module load R/3.1.1-foss-2014a-default
fi

Rscript means.R 0.5 1.0 1000

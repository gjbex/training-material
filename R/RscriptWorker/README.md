RscriptWorker
=============

This are some simple R scripts to illustrate using Rscript, and
job scripts to run it in batch mode.  Also an example of using R from
the worker framework is provided.  For more information on worker,
see:
https://github.com/gjbex/worker

Contents
--------
* `means.R`: takes three parameters: the mean and standard deviation for
    a gaussian distribution, and the number of times to sample that
    distribution.  It prints the mean of the sample.
* `run.sh`: Bash script to illustrate how to run using Rscript on the
    command line.
* `compute.pbs`: PBS script to perform a single computation
* `submit.sh`: Bash script to illustrate how to submit a job for
    `compute.pbs`.
* `compute_parameterized.pbs`: parametrized PBS script, 
* `submit_parameterized.sh`: Bash script to illustrate how to submit a job
    for `compute_parameterized.pbs`.
* `data.csv`: parameter data in a CSV file format
* `submit_worker.sh`: Bash script that illustrates how to submit a worker
    job.

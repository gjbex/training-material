# JobChain
Illustration of how to submit a chain of jobs where the current job
submits its follow-up job, with a dependency on the current job.

**Note:** *ensure there is a termination condition!*

## What is it?
  * `count_down.pbs`: PBS script that, starting from a counter, submits
    follow-up jobs with the counter decremented, until the counter
    reaches 0.

## How to use it?
Submit the job with a positive value for the counter, e.g.,
```bash
$ qsub -v counter=2 count_down.pbs
```
Each job will take 20 seconds, and in the example above three jobs are
executed.

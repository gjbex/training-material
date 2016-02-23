# SparkR

## Set up
Load the R module for the version you want to use, e.g.,
```bash
$ module load R/3.1.2-foss-2015a-bare
```
Load the Java module to use, e.g.,
```bash
$ module load Java/1.8.0_31
```

These modules have to be loaded each time you want to run SparkR.

Now install the `rJava` R package the usual way, i.e., start R and
execute `install.packages('rJava')`.  This has to be done only once for
a given version of R.

## Starting SparkR
For simple experiments, one can simply run a Spark standalone instance.
However, for large parallel computations, resource management should be
handled by Yarn.

### Standalone SparkR
Start an interactive job on a compute node (this should really not be
done on a login node).
```bash
$ qsub -l nodes=1:ppn=20 -l walltime=4:00:00 -I
```
Once the interactive job has started, load the module for Spark, e.g.,
```bash
$ module load Spark/1.4.1
```
Change to the working directory, i.e.,
```bash
$ cd $PBS_O_WORKDIR
```
Start SparkR, i.e.,
```bash
$ sparkR
```

### SparkR on top of Yarn
Yarn is (one of) Apache's resource managers.  Using it to run SparkR allows
more fine grained control over the resources allocated to worker processes.

To start it, first load the approriate module:
```bash
$ module load hod/3.0.1-cli
```
Next, create a Hadoop cluster:
```bash
$ hod create --dist Hadoop-2.6.0-cdh5.4.5-native --label hod_hadoop -n 3
```
Here, `-n 3` denotes the number of nodes to use, and the label is used to
refer to the Hadoop job later on.  Note that these labels need to be
unique among active jobs.

Once a job is running, you can connect to the hadoop cluster by running:
```bash
$ hod connect hod_hadoop
```
This provides an interactive session on one of the compute nodes the hadoop
cluster has been instantiated on.  First load the spark and the R module:
```bash
$ module load Spark/1.4.1
$ module load R/3.1.2
```
Finally, start sparkR:
```bash
$ sparkR --master yarn
```

When done with your experiments, don't foget to stop the job using `qdel`,
simply quitting sparkR and login out of the interactive shell will not end
the job.

To list all jobs, use:
```bash
$ hod list
```

When finished, jobs can be removed by:
```bash
$ hod clean
```

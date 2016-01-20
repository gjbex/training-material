# SparkR

## Set up
Load the R module for the version you want to use, e.g.,
```bash
$ module load R/3.1.2-foss-2015a-bare
```
Load the Java module to use, e.g.,
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

## Doing computations


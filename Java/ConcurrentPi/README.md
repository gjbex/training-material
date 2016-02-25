ConcurrentPi
============

Example of using multiple threads for a computation through a
`ThreadPoolExecutor` and  tasks implementing the `Callable` interface.
Some PBS scripts are provided to illustrate how to use this
application with the worker framework.

What is it?
-----------
1. `src`: source code for the Java application.
  1. `PiDriver.java`: main method that handles command line arguments, if
        any, and starts and finishes the computation of pi.
  1. `gjb.demo.concurrentpi.PiComputer.java`: class that performs the
        multithreaded computation, using tasks implemented by
        `gjb.demo.concurrentpi.PartialPi.java`.
  1. `gjb.demo.concurrentpi.PartialPi.java`: computes a quadrature over
        a given interval, contributing to the overall result on the
        interval [0.0, 1.0].
1. `build.xml`: Ant build file to compile the code, and build two JAR
    files, the first one `pi_computer.jar` contains the code to
    compute pi using one or more threads, the second `pi_app.jar`
    contains a `main` method that handles command line arguments and
    output.
1. `scaling.pbs`: check scaling when running with 1, 2, 4, 8, and 16
    threads on a compute node with at least that many physical cores.
1. `submit.sh`: submits the `scaling.pbs` PBS file, simply for
    illustrating the `qsub` command.
1. `precision.pbs`: using a specified number of threads, compute pi using
    the given value of `delta_x`.
1. `precision.dat`: data file for `precision.pbs`
1. `submit_with_worker.sh`: submit `precision.pbs` as a PBS batch file
    with worker, using `precision.dat` as a data file.  This is added to
    document the submission process.

How to use it?
--------------
The java application can be build using ant, i.e.,
```bash
$ ant appjar
```
This will build two JAR files, one containing the actual implementation,
the second a driver program to execute the computation.
For a simple test, run it with
```bash
$ ant run
```

Prerequisites
-------------
* Java 1.7+
* ant

AutoCorrelation
===============

This project illustrates the concept of autocorrelation in a Markov
process.

What is it?
-----------
1. `functions.py`: module that contains the definition of the weight
    function, used by `process.py`, `bin_values.py`.
1. `process.py`: implements a Monte Carlo algorithm that uses the
    weight function, this can be used to examine the influence of the
    number of steps, the burn-in length, and the skip size.  The result
    will be written as a list of x-values to standard output, optionally
    with a time-step column.
1. `autocorrelation.py`: reads a list of x-values from standard input,
    and writes the autocorrelaiton up to a specified distance to standard
    output
1. `bin_values.py`: reads x-vales from standard input, and bins those
    in the specified number of bins (with given minimum and maximum
    values), the results are written to standard output, optionally
    with the weight function values added.
1. `bin_values.c`: C implementation of the binning utility.
1. `Makefile`: builds the C programs.

How to use?
-----------
First generate some sample values, e.g.,
```[bassh]
$ ./process.py --steps 1000 > values.txt
```
Next, copmute the autocorrelation, e.g.,
```[bash]
$ ./autocorrelation.py < values.txt
```
Compute the distribution of the values, e.g.,
```[bash]
$ ./bin_values --target < values.txt
```

All Python scripts are documented, e.g.,
```[bash]
$ ./process.py --help
```

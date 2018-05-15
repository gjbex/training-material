# Matlab
Examples of how to call MATLAB functions from Python.

## What is it?

### MATLAB from Python
1. `matlab_from_python.ipynb`: Jupyter notebook illustrating how to call MATLAB from
    Python.  Includes rudimentary installation instructions.
1. `linear_script.m`: simple MATLAB script to be executed from within the notebook.
1. `linear_funtion.m`: simple MATLAB function to be called from within the notebook.
1. `stats.m`: MATLAB class definition for objects that can do statistics on
    streaming data.
1. `fibonacci.m`: (naive) implementation of the Fibonacci function in MATLAB to
    illustrate asynchronous function calls.

### Python from MATLAB

Note that using MATLAB from Python (Anaconda distribution) under Windows only works
if the Windows `PATH` environment variable is set appropriately.  If `<ANACONDA>`
represents the location of your Anaconda installation, then you should add
all of the following paths to `PATH`:
  * `<ANAONDA>`
  * `<ANACONDA\Scripts`
  * `<ANACONDA\Library\bin`

Under Linux, using a standard Python distribution or conda, such shenanigans are
not required, only the Python executable's directory needs to be in the `PATH`.

1. `fib_sum.m`: MATLAB script to compute the sum of some Fibonacci numbers
    computed by a Python function.
1. `functions.py`: Python module implementing the Fibonacci function.
1. `data_structure.m`: illustration of using a Python `dict` from MATLAB.
1. `numpy_test.m`: illustration of using numpy from MATLAB.
1. `versioning.m`: MATLAB script to illustrate reloading modified Python modules.
1. `versioning_1.py`: initial version of a Python module.
1. `versioning_2.py`: modified version of a Python module.

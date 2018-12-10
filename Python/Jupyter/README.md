# Jupyter
A number of notebooks illustrating specific aspects of the features
offered by Jupyter notebooks.

## What is it?
1. `notebook_example.ipynb`: basic notebook features illustration.
1. `fortran_magic.ipynb`: illustration of the Fortran magic to define
    and use Fortran procedures in Python Jupyter notebooks.  It also
    illustrates how to use Fortran OpenMP code for multithreaded
    processing.
1. `r_python.ipynb`: illustration of how to use Python and R in the same
    notebook using `rpy2`.
1. `example.md`: MarkDown file to execute and produce a notebook using
    `notedown`.
1. `Makefile`: make file to run a Jupyter notebook in batch
    (`batch_run_notebook` target), convert a Jupyter notebook to a
    MarkDown file (`convert_to_md` target), and run a MarkDown file,
    producing a Jupyter notebook (`batch_run_md` target).

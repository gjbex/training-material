# DynamicModuleLoad
Python's `importlib` offers convenient mechanisms to dynamically load
modules, i.e., specified as strings at runtime.

## What is it?
1. `dynamic_module_load.ipynb`: Jupyter notebook illustrating
    dynamic loading of modules.
1. `my_local_module.py`: simple module that implements a function
    `hello`.
1. `my_package`: directory representing a Python package with a
    module at the root level, two subpackages, each with a module.
    All module implement the function `hello` which identifies the
    defining module.

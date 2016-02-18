#!/usr/bin/env python

from distutils.core import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize("ising_cython_01.pyx")
)

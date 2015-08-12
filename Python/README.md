Python
======

Python is an excellent programming language for data processing,
prototyping and writing glue code for C/C++/Fortran libraries.

This directory contains code samples that illustrate particular features
and programming techniques, or how to use Python iibraries.  Many of
these samples have been used for Python tutorials.

What is it?
-----------
1. `ArgParse`: illustration of how to use the argparse module to handle
    command line arguments.
1. `Autocorrelation`: illustration of autocorrelation in a Markov process,
    implements a Monte Carlo algorithm, and allows to show evolution over
    time, autocorrelation, and to compare with target distribution.
1. `Birdsong`: implements a FFT of WAV files, and shows the original signal
    (amplitude) and the frequency spectrum using Matplotlib.  Another
    script illustrates elementary signal processing using a highpass
    filter.
1. `CLibsFromPython`: illustrate how to use a C library from a Python
    script.
1. `CodeEvaluation`: illustrates how to evaluate a string containing
    Python code at runtime.
1. `CodeTesting`: illustration of how to use the `unittest` framework for
    setting up and executing unit tests
1. `ConfigParser`: illustrates how to use the ConfigParser module to handle
    configuration files.
1. `ContextManager`: illustrates the concept of a context manager, a
    mechanism to deal with resource setup/teardown.
1. `Coroutines`: illustrates coroutines, functions that preserve state
    between invocations.
1. `DataFormats`: illustrates how to deal with data formats such as CSV
    files, binary data and XML.
1. `DbAccess`: illustrates how to insert data into a relational database
    and query it, both with Python's sqlite3 module, and SQLAlchemy.
1. `Decorators`: illustrates how to create decorators to wrap functions.
1. `Descriptors`: illustrates the descriptor concept in Python
1. `Exec`: illustrates executing a shell command from a Python script
    using the `subprocess` module.
1. `Exercises`: example solutions to exercises to be found in the 
    Powerpoint presentation; this is part of the "Python as a data
    processing language" training session.
1. `FiniteStateParser`: illustrates how to parse a file that is structured
    as a regular language.  A `pyparsing` example is also given.
1. `Fundamentals`: code samples that where used to extract fragments
    in the part of the presentation on core Python features.
1. `Interfacing_C_C++_Fortran`: illustrates how to use Fortran code
    from Python using `f2py`, C code by using `ctype`, and C/C++ code
    using SWIG.
1. `Joblib`: illustrates the use of this library for easy task parallelism
1. `Jupyter`: A few notebooks to illustrate the Jupyter notebook GUI.
1. `Logging`: illustration of Python's logging facilities.
1. `Matplotlib`: a few illustrations of how to use the `pyplot` module.
1. `Matrices`: a few timings of matrix-matrix multiplications using
    LoL in Python, the numpy.dot function, a Fortran matmul and DGEMM, and
    a straightforward C implementation.
1. `Mixin`: illustrates the object-oriented programming technique of
    mix-ins.
1. `Mpi4py`: illustration of writing distributed applicationns using MPI
1. `Multiprocessing`: illustrates concurrent computations using the
   `multiprocessing` library.
1. `NetworkX`: illustration of the graph representation and algorithms
    library.
1. `Numpy`: a few illustratios of using numpy, scipy, and matplotlib
    (linear regression, optimization, solving ODEs, FFT).
1. `Pandas`: R dataframe-like data structures for Python, contains a
    Jupyter notebook to illustrate using pandas interactively.
1. `PhraseIndexer`: parses a text file to find the line number on which a
    given eet of phrases occurs.
1. `python-intro.pptx`: Powerpoint presentation on Python as a data
    processing language, exercises for the corresponding training session
    can be found in the `Exercsises` directory.
1. `SentenceCounter`: scripts to (naively) count sentences in natural
    language text, both serial and parallel implementations.
1. `style.md`: some style tips based on code reviews and observations in
    the field
1. `Vtk`: examples of using the KitWare VTK library.
1. `WxPython`: some illustrations of GUI developlement using the Python
    bindings for Wx.
1. `XmlGenerator`: code to generate a random XML documents.

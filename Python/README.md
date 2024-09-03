# Deprecation notice

This part of
the repository has in large part been superceeded by various training 
repositories dedicated to specific Python-related topics.
* Python for programmers
  * [repository](https://github.com/gjbex/Python-for-programmers)
* Scientific Python
  * [website](https://gjbex.github.io/Scientific-Python/)
  * [repository](https://github.com/gjbex/Scientific-Python)
* Python for data science
  * [website](https://gjbex.github.io/Python-for-data-science/)
  * [repository](https://github.com/gjbex/Python-for-data-science)
* Python for machine learning
  * [website](https://gjbex.github.io/Python-for-machine-learning/)
  * [repository](https://github.com/gjbex/Python-for-machine-learning)
* Python for HPC
  * [website](https://gjbex.github.io/Python-for-HPC/)
  * [repository](https://github.com/gjbex/Python-for-HPC)
* Python for systems programming
  * [website](https://gjbex.github.io/Python-for-systems-programming/)
  * [repository](https://github.com/gjbex/Python-for-systems-programming)
* Python software engineering
  * [website](https://gjbex.github.io/Python-software-engineering/)
  * [repository](https://github.com/gjbex/Python-software-engineering)


# Python
Python is an excellent programming language for data processing,
prototyping and writing glue code for C/C++/Fortran libraries.

This directory contains code samples that illustrate particular features
and programming techniques, or how to use Python iibraries.  Many of
these samples have been used for Python tutorials.


# What is it?
1. `Autocorrelation`: illustration of autocorrelation in a Markov process,
    implements a Monte Carlo algorithm, and allows to show evolution over
    time, autocorrelation, and to compare with target distribution.
1. `Biopython`: some Biopython examples.
1. `biopython.pptx`: Microsoft Powerpoint presentation on using BioPython
    for bioinformatics related tasks.
1. `Birdsong`: implements a FFT of WAV files, and shows the original signal
    (amplitude) and the frequency spectrum using Matplotlib.  Another
    script illustrates elementary signal processing using a highpass
    filter.
1. `Bokeh`: illustrations of how to use the Bokeh plotting library for,
    e.g., interactive graphs.
1. `CodeCoverage`: illustration f how to use a code coverage tool.
1. `CodeEvaluation`: illustrates how to evaluate a string containing
    Python code at runtime.
1. `CodeTesting`: illustration of how to use the `unittest` framework for
    setting up and executing unit tests
1. `CommandLineArgs`: illustration of how to use the argparse and the
    click module to handle command line arguments.
1. `ConfigParser`: illustrates how to use the ConfigParser module to handle
    configuration files.
1. `ContextManager`: illustrates the concept of a context manager, a
    mechanism to deal with resource setup/teardown.
1. `Coroutines`: illustrates coroutines, functions that preserve state
    between invocations.
1. `Cython`: Powerpoint presentation on Cython, as well as example code.
1. `DataFormats`: illustrates how to deal with data formats such as CSV
    files, binary data and XML.
1. `DataStructures`: illustration of some data types defined in Python's
    `collections` standard library module and other standard library
    packages.
1. `DbAccess`: illustrates how to insert data into a relational database
    and query it, both with Python's sqlite3 module, and SQLAlchemy.
1. `Debugging`: some code that is useful for debugging demos.
1. `Decorators`: illustrates how to create decorators to wrap functions.
1. `Descriptors`: illustrates the descriptor concept in Python
1. `DynamicModuleLoad`: illustrates how to load modules at runtime
    by name.
1. `Exercises`: example solutions to exercises to be found in the 
    Powerpoint presentation; this is part of the "Python as a data
    processing language" training session.
1. `FiniteStateParser`: illustrates how to parse a file that is structured
    as a regular language.  A `pyparsing` example is also given.
1. `Flask`: some illustrations of using the Flask web services framework.
1. `Functional`: some illustrations of functional programming style.
1. `Fundamentals`: code samples that where used to extract fragments
    in the part of the presentation on core Python features.
1. `Gis`: code samples for dealing with GIS data.
1. `Interfacing_C_C++_Fortran`: illustrates how to use Fortran code
    from Python using `f2py`, C code by using `ctype`, and C/C++ code
    using SWIG.
1. `HoloViews`: data visualization library examples, especially in the
    context of exploration in notebooks.
1. `Hydra`: Facebook Hydra application framework illustration.
1. `ImageProcessing`: some Scikit-Image sample code for image processing,
    as well as OpenCV for video analysis.
1. `Interfacing_C_C++_Fortran`: illustrations of how to interface with
    C, C++ and Fortran code using ctypes, SWIG or f2py.
1. `Introspection`: sample code of how to implement introspection as
    mix-in class.
1. `Ising`: Implementation of the 2D Ising system in pure Python, as well
    as in C++ using SWIG to wrap the implementation.  Mostly intended for
    visualization purposes.
1. `Joblib`: illustrates the use of this library for easy task parallelism
1. `Jupyter`: A few notebooks to illustrate the Jupyter notebook GUI.
1. `Keras`: illustration of using the Keras framework for machine learning
    tasks.
1. `Logging`: illustration of Python's logging facilities.
1. `Matlab`: illustrations of how to call MATLAB functions from Python.
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
1. `Nltk`: some initial Natural Language ToolKit experiments.
1. `Numpy`: a few illustratios of using numpy, scipy, and matplotlib
    (linear regression, optimization, solving ODEs, FFT).
1. `OperatorFunctools`: some illustrations of the functional programming
    options offered by `opeator` and `functools` packages.
1. `OsFileSystem`: illustrations of interacting with the operating system
    and the file system.
1. `Pandas`: R dataframe-like data structures for Python, contains a
    Jupyter notebook to illustrate using pandas interactively.
1. `Paramiko`: a few examples of using the Paramiko library for SSH
    to remote hosts.
1. `Pitfalls`: illusttrations of pitfalls when coding Python due to
    non-trivial semantics.
1. `PhraseIndexer`: parses a text file to find the line number on which a
    given eet of phrases occurs.
1. `PyCuda`: Jupyter notebooks illustrating PyCUDA.
1. `Profiling`: a few examples of how to use profilers for Python.
1. `python_development_practices.pptx`: Powerpoint presentation on some
    development good practices.
1. `python_hpc.pptx`: Powerpoint presentation on how to use Python for
    high performance computing, contains sections on Cython, using
    C/C++/Fortran libraries from Python, shared memory programming, MPI,
    and PySpark.
1. `python_intro.pptx`: Powerpoint presentation on Python as a data
    processing language, exercises for the corresponding training session
    can be found in the `Exercsises` directory.
1. `Sched`: scheduled execution of funcitons in Python.
1. `ScikitLearn`: examples using the scikit-learn machine learning
    library.
1. `Regexes`: some material related to using regular expressions in Python.
1. `Seaborn`: illustrations of the Seaborn plotting library.
1. `SentenceCounter`: scripts to (naively) count sentences in natural
    language text, both serial and parallel implementations.
1. `style.md`: some style tips based on code reviews and observations in
    the field
1. `SpaCy`: illustrations of using the spaCy natural language processing library.
1. `Subprocess`: illustrates executing a shell command from a Python script
    using the `subprocess` module.
1. `Typing`: Python type annotations can help to make code considerably
    more robust.
1. `Unittest`: illustration of how to use Python's standard library
    unit testing framework.
1. `Vtk`: examples of using the KitWare VTK library (No support for Python
    3 yet).
1. `WebScraping`: illustration of web scraping using Beautiful Soup.
1. `WxPython`: some illustrations of GUI developlement using the Python
    bindings for Wx (No support for Python 3 as yet).
1. `Xarray`: illustration of using xarray to represent numerical data.
1. `XmlGenerator`: code to generate a random XML documents.


## How to
* Instructions for [installing `conda` and hence Python package managenment
    on the VSC cluster are available](INSTALL_CONDA.md).
* Instructions on how to use a [Jupyter notebook server that runs on a
compute node on the VSC cluster](HOWTO_REMOTE_JUPYTER.md).

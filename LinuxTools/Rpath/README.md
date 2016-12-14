# Rpath
The `rpath` linker option allows to embed paths to shared libraries into
an executable, eliminating the need to set the `LD_LIBRARY_PATH`
environment variable.

However, if the latter is set, it will have priority over the RPATH
data, hence offering the flexibility expected from shared libraries.

## What is it?
1. `Library`: contains `hello.c`, `hello.h`, and a `Makefile` to create `libhello.so`.
1. `Library_alt`: contains `hello.c`, `hello.h`, and a `Makefile` to create `libhello.so`.
    This is almost identical to the versions in `Library` except for some extra exclamation
    marks.  The `Makefile` also produces `libhello.so`.
1. `Application`: contains `appl.c` and a `Makefile` that links against the `libhello.so`
    in `Library` using the `-rpath` option.
1. `build.sh`: Bash script to build the two versions of the shared library, as well as the
    application.
1. `run.sh`: run the application using the library in `Library`.
1. `run_alt.sh`: run the application using the library in `Library_alt` after setting the
    `LD_LIBRARY_PATH` variable appropriately.

## How to use?
Build the shared libraries in `Library` and `Library_alt`, i.e.,
```
$ ./build.sh
```

The executable can be moved to any location, when it is run, it will use the `libhello.so`
in `Library`.  It can be run in the currect directory using
```
$ ./run.sh
hello gjb!
```

If the `LD_LIBRARY_PATH` environment variable is set to contain the `Library_alt`
directory, then that version of the shared library is used, i.e.,
```
$ ./run_alt.sh
hello gjb!!!
```
This illustrates that `LD_LIBRARY_PATH` overrides the RPATH information in the executable
so it is still possible to use another version of the shared library when desired.

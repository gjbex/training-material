# PostMortem
The application implemented here will crash with a segmentation fault.
The core file can be used for post-mortem analysis.

## What is it?
1. `crash.c`: application that will crash with a segmentation fault.
1. `Makefile`: make file to build the application.

## How to use it?
Build the application
```bash
$ make
```
The core file can be analysed using gdb
```bash
$ gdb ./crash.exe core
```
(Note: the core file may have a different name, e.g., core.<pid>.)

You may have to set the core size to an appropriate value using ulimit,
e.g.,
```
$ ulimit -u 100000
```

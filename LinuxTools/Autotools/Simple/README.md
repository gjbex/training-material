# Simple
A very simple example of how to use Gnu Autotools to generate a `configure`
and make files.

## Contents
1. `configure.ac`: sets meta information about the project, options for
    Automake, and the make files to be generated.
1. `Makefile.am`: top-level make file, indicates which subdirectories
    should be processed.
1. `src`: directory containing the source code, and the `Makefile.am`
    that describes how to build it.
1. `prepare.sh`: Bash script to generate the `configure` and make files,
    this should not be redistributed, since one would typically bundle
    the result of this for distribution.
1. `cleanup.sh`: Bash script to remove all autotools artefacts, this is
    only useful for illustrating how autotools works.

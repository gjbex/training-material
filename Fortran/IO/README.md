Fortran I/O
===========

Modern Fortran has some nice I/O functionality, although the code tends
to be pretty verbose.

What is it?
-----------
1. `formtatted_read_writes_test`: writes formatted records to an external
    file, reads the contents back in, and validates the input.
1. `unformtatted_read_writes_test`: writes unformatted records to an
    external file, reads the contents back in, and validates te input.
1. `stream_read_write_test`: writes unformatted records to an
    external file, and reads the data back in for verification using the
    file position in stream mode.
1. `read_test`: C program to illustrate that data written by a Fortran
    program using unformatted stream I/O can be read correctly.

How to build?
-------------
A make file is provided.

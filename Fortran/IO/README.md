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
1. `write_stream_test`: illustrates stream write of a complete array at
    once.
1. `read_stream_test`: illustrates how to stream read a file of unknown
    length using the iostat value to detect end of file.
1. `read_stream`: C program that reads the binary file produce by
    `write_stream_test`.
1. `inquire_test`: illustrates some uses of the inquire statement, as well
    as sequential, non-advancing I/).
1. `append_test`: illustrates the rewind statement, and positioning for
    stream I/O.

How to build?
-------------
A make file is provided.

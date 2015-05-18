BinaryIO
========

Example code of how to do binary I/O with R.

What is it?
-----------
1. `read_binary.R`: script that takes three arguments, a file name of a
    text file, a starting position, and a read length.  The script will
    read the specified number of bytes from the given start position ,
    and print them as a character string to standard output, delimited
    by '|' characters.
1. `index.txt`: input file to test with.
1. `index.csv`: CSV file containing the start position and line length
    of all lines in `index.txt`.

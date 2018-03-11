# Classes
Code illustrations for chapter 8, I/O streams in Stroustrup's
"A tour of C++".

# What is it?
1. `sum.cpp`: compute the sum of all double precision numbers in
    standard input.
1. `data.txt`: text data file containing double precision floating point
    numbers.
1. `serialization.cpp`: sample implementation of the `<<` and `>>`
    operators to serialize/deserialize a struct to a string representation.
1. formatting.cpp`: examples of I/O formatting for floating point numbers,
    width and fill for integers.
1. `csv2tsv.cpp`: convert files from CSV to TSV format, using file and
    string methods.
1. `aggregate.cpp`: compute the sum of each row of a CSV file, and write
    that in the output CSV file as the first column. String streams are
    used to parse the data.
1. `Makefile`: make file to build the code.

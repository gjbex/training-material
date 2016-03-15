# C client

Client code in C for the Redis data structure server using the hiredis
library.

## What is it?
1. `append.c`: appends a value specified on the command line to a list
    on a Redis server.
1. `Makefile`: make file to build the example.

## Remarks
1. The client assumes that the server is running on localhost, and
    listening to the default port.
1. The client reads a password from the command line (first argument), this
    is of course not recommended from a security point of view.

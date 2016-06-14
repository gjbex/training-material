# Gallery of processor cache effects
C implementations of the code examples given in Igor Ostrovsky's
interesting blog post on effects the various caching mechanisms in a
modern CPU can have on performance.  See the following URL for his
original post:
http://igoro.com/archive/gallery-of-processor-cache-effects/

## What is it?
1. Example 2: `cache_lines.c`
1. Example 3: `cache_hierarchy.c`
1. Example 4: `instruction_parallelism.c`
1. Example 5: `cache_associativity.c`

Each C file is accompagnied by a PBS script to run it in batch, and a
make file is provided for building the software.  Some sample output is
included as well.

## Build instructions
Load the appropriate module for the Intel compiler, and simply use `make`.


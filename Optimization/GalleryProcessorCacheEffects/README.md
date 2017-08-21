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
1. False sharing:
  * `false_sharing_01.c`: array that fits in L1 is accessed from two
    threads, with and without false sharing.
  * `false_sharing_02.c`: counters stored in an array are updated from
    each thread, either with or without padding to avoid false sharing.
  * `alignment.c`: illustration of using variable attributes to align
    on cache line boundaries.
  * `alignment.f90`: illustration of using variable attributes to align
    on cache line boundaries (Intel only).

Each C file is accompagnied by a PBS script to run it in batch, and a
make file is provided for building the software.  Some sample output is
included as well.


## Build instructions
To build with the GCC compiler suite, load the appropriate module, and use
```bash
make
```

To build with the Intel compiler suite, load the appropriate module, and use
```bash
make -f Makefile.intel
```

# Fortran object-oriented programming

Fortran 2003 adds features to enable object-oriented programming.

## What is it?
1. `node_mod.f90`: module defining a class representing a node in a
    binary tree.  A node has a left and a right child, and a single
    precision real value.  These attributes are private, but can be
    accessed by calling the corresponding getters and setters.  A
    constructor is implemented as well, but note it can only be called
    on an non-null class instance.  To avoid memory leaks, a finalizer
    method is implemented as well.  For convenience, there is a method
    to print a tree, showing levels by indentation.
    The `init_random` method creates a new, random tree from a given root
    node.  The `count_nodes` method computes the total number of nodes in
    the tree, while the `leaf_distance` method copmutes the longest
    distance between the root and any leaf node (node values are
    interpreted as distances between that node and its parent, hence
    the root has value 0.0).
1. `random_mod.f90`: implements a somewhat naive method to seed the
    random number generator.  Note that this method should not be used
    for production code, and certainly not for parallel runs.
1. `tree_test.f90`: creates a random tree, prints it to the screen,
    computes the number of nodes, and the longest distance from root to
    any leaf.
1. `avg_path_test.f90`: creates a given number of trees, and computes
    the average node count and leaf distance.
1. `id_node_mod.f90`: class dervied from `node_type` that adds an ID
    atribute to nodes.  Upon calling `new` it is automatically incremented.
    A getter is available, but no setter so that the ID can not be modified.
    An apropriate implementation of the `show` method is added.
1. `id_tree_test.f90`: creates a random tree, prints it to the screen,
    computes the number of nodes, and the longest distance from root to
    any leaf.  This program uses `id_node_type` rather tha `node_type`.
1. `rationals_mod.f90`: simple implementation of rational numbers,
    illstrates operator overloading, and default constrctor overriding.
1. `rationals.f90`: main program to illustrate usage of `rationals_mod`,
    computes sum of rational numbers.
1. `stats_mod.f90`: user defined type to store statistical data.
1. `stats.f90`: main program to test the `stats_mod`.

## How to build?
Simply use the make file provided.

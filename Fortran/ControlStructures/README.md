Fortran control structures
==========================

Modern Fortran has a number of succinct control structures.

What is it?
-----------
1. `forall_test`: illustrates the `forall` construct that can be used
   to initialize array elements by index, but selectively, i.e., based
   on conditions on those indices.  Here, a matrix is constructed that
   has all elements equal to zero, except the first diagonals.
2. `select_test`: illustrates the `select case` construct that allows
   branching based on the values of scalar variables (`integer` and
   `character(len=*)`).  This program implements a very simple command
   line calculator that will either add or multiply two given numbers.
   ```
   $ ./select_test 5 + 3
   $ ./select_test 17 * 4
   ```
3. `where_test`: illustrates the use of `where` to initialize an matrix
   in one operation based on conditions imposed on another's elements.
   Here, a matrix `A` is initialized with random real numbers between
   -1.0 and 1.0, and two matrices `Pos` and `Neg` are constructed, the
   latter's elements having the value one where `A`'s elements are
   positive, 0 elsewhere, and similar for `Neg`.

   How to build?
   -------------
   A make file is provided.


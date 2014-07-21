Parallel processing with joblib
===============================

JoblIb is a library that helps to implement task parallelism easily.
Note that joblib is not a standard library, and that the task below
can be accomplished by the `multiprocessing` module in the standard
library.

What is it?
-----------
1. `pi.py`: script to compute pi by drawing a sequence of points in
   the unit square, and counting those that lie in the unit circle.
2. `pi_joblib.py`: since the points are independent, they can be
   selected in parallel. by using joblib's Parallel construct and
   delayed function calls.


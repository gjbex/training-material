Coroutines
==========

Coroutines provide a powerful programming paradigm for functions that
preserve state between invocations.

What is it?
-----------
1. `coroutine.py`: implements a coroutine `my_printer` that can can be
    "created" by invocating the function, "started" using the `next()`
    method, "invoked" using the `send()` method, and terminated using
    the `close()` method.
1. `longest_run.py`: stateful streaming parser implemented using a
    coroutine.  It keeps track of the longest run of characters in
    a string that is presented one batch at the time.
1. `stats.py`: coroutine implementation for collecting statistics (mean,
    standard deviation).
1. `data.txt`: data file to compute statistical measures from.

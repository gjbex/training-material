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
1. `stats.py`: coroutine implementation for collecting statistics (mean,
    standard deviation).
1. `data.txt`: data file to compute statistical measures from.

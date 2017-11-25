# Threading
Illustration of using the `threading` module for parallel computations.

## What is it?
1. `pi.py`: illustration of using threads and locks, however, threads
    are implicitly serialized due to access of random number generator.
1. `array_samples.py`:  illustration of how Python's GIL serializes
    threaded code due to accessing a common object (numpy array).

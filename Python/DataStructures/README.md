# DataStructures
Although Python has many useful data types built-in, the `collections`,
part of its standard library, module contains a number of quite useful
additional ones.  Also other modules in the standard library define some
useful data structures.

## What is it?
1. `counter.py`: counts characters from stardard input, but uses a
    `Counter` to store the results.  The three most common characters are
    listed using the `most_common` method.
1. `ordered_dict.py`: counts characters from standard input, and stores
    counts in an `OrderedDict` so that the output reflects the order of
    the first occurence in the text.
1. `points.py`: illustration of the use of `namedtuple`, a data type that
    represents a tuple that has elements that can be addressed by names,
    in addition to index.  This example also shows how to use `itertools`
    `combinations` iterator, as well as an interesting string format.
1. `points_modern_namedtuples.py`: illustration of the use of `NamedTuple`,
    a data type that represents a tuple that has elements that can be
    addressed by names,  This script is the same as `point.py`, but uses
    the more modern and flexible `NamedTuple` class in the `typing`
    module (Python 3.5+).
1. `priority_queue.py`: illustrates the use of two priority queue
    implementations, `queue.PriorityQueue` and `heapq`.  Note that the
    former may be overkill since it can be used from multiple processes
    simultaneously.
1. `sets.ipynb`: jupyter notebook showing the operations defined on sets
    through methods, and the overloaded operator counterparts.
1. `text.txt`: text file to experiment with.
1. `performance.ipynb`: jupyter notebook with some timings to test
    performance of operations on data structures.

#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
from threading import Thread, Lock
import time

def compute_pi(thread_nr, seed, lock, partial, done_by, nr_tries,
               verbose=False):
    if verbose:
        print(f'thread {thread_nr} started')
    np.random.seed(seed)
    while True:
        nr_hits = 0
        for _ in range(nr_tries):
            x, y = np.random.uniform(0.0, 1.0, 2)
            if x**2 + y**2 < 1.0:
                nr_hits += 1
        with lock:
            if verbose:
                print(f'thread {thread_nr} grabs lock')
            for i in range(partial.size):
                if partial[i] < 0.0:
                    partial[i] = nr_hits/nr_tries
                    done_by[i] = thread_nr
                    break
            else:
                if verbose:
                    print(f'thread {thread_nr} ended')
                return
            if verbose:
                print(f'thread {thread_nr} releases lock')


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi using multiple '
                                            'threads')
    arg_parser.add_argument('--nr-threads', type=int, default=2,
                            help='number of threads to use')
    arg_parser.add_argument('--nr-values', type=int, default=10,
                            help='number of intermediate values to use')
    arg_parser.add_argument('--nr-tries', type=int, default=100_000,
                            help='number of tries for each value')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show verbose output')
    options = arg_parser.parse_args()
    done_by = np.empty(options.nr_values, dtype=np.int32)
    done_by.fill(-1)
    partial = np.empty(options.nr_values)
    partial.fill(-1.0)
    seeds = np.random.randint(1_000_000_000, size=options.nr_values)
    lock = Lock()
    threads = []
    for thread_nr in range(options.nr_threads):
        threads.append(Thread(target=compute_pi,
                              args=(thread_nr, seeds[thread_nr],
                                    lock, partial, done_by,
                                    options.nr_tries, options.verbose)))
        threads[-1].start()
    for thread in threads:
        thread.join()
    pi = 4*np.mean(partial)
    print(f'pi = {pi}')
    if options.verbose:
        for i, thread_nr in enumerate(done_by):
            print(f'{i}: thread {thread_nr}')

#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
from threading import Thread, Lock
import time

def compute_sample_sum(thread_nr, nr_threads, lock, values, nr_iters,
                       nr_reps, sums, verbose=False):
    if verbose:
        print(f'thread {thread_nr} started')
    for iter_nr in range(nr_iters):
        weight = sum(values)
        sample_sum = 0.0
        for k in range(nr_reps):
            for i in range(thread_nr + k, len(values), thread_nr + 1):
                sample_sum += values[i]
            sample_sum /= weight
        with lock:
            if verbose:
                print(f'thread {thread_nr} grabs lock')
            sums[thread_nr + nr_threads*iter_nr] = sample_sum
            if verbose:
                print(f'thread {thread_nr} releases lock')
    if verbose:
        print(f'thread {thread_nr} ended')


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute pi using multiple '
                                            'threads')
    arg_parser.add_argument('--nr-threads', type=int, default=2,
                            help='number of threads to use')
    arg_parser.add_argument('--nr-values', type=int, default=1_000_000,
                            help='array length to use')
    arg_parser.add_argument('--nr-iters', type=int, default=10,
                            help='number of times each thread computes')
    arg_parser.add_argument('--nr-reps', type=int, default=1_000,
                            help='number of iterations per computation')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show verbose output')
    options = arg_parser.parse_args()
    values = np.random.uniform(0.0, 1.0, options.nr_values)
    sums = np.empty(options.nr_iters*options.nr_threads)
    sums.fill(-1.0)
    lock = Lock()
    threads = []
    for thread_nr in range(options.nr_threads):
        threads.append(Thread(target=compute_sample_sum,
                              args=(thread_nr, options.nr_threads,
                                    lock, values, options.nr_iters,
                                    options.nr_reps, sums,
                                    options.verbose)))
        threads[-1].start()
    for thread in threads:
        thread.join()
    value = np.mean(sums)
    print(f'value = {value}')

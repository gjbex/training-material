#!/usr/bin/env python

from argparse import ArgumentParser
import dask.array as da
from datetime import datetime
from distributed import Executor
import time


def get_hostname(i):
    import socket
    time.sleep(5)
    return '{0} on {1}'.format(i, socket.gethostname())

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute and check SVD')
    arg_parser.add_argument('--scheduler', help='scheduler host')
    arg_parser.add_argument('--scheduler_port', default='8786',
                            help='scheduler port to use')
    options = arg_parser.parse_args()
    executor = Executor('{0}:{1}'.format(options.scheduler,
                                         options.scheduler_port))
    futures = executor.map(get_hostname, range(100))
    for future in futures:
        print(future.result())

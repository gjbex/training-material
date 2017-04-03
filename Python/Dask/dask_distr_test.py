#!/usr/bin/env python

from argparse import ArgumentParser
import dask.array as da
from datetime import datetime
from distributed import Client
import time


def square(x):
    return x**2

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
    client = Client('{0}:{1}'.format(options.scheduler,
                                     options.scheduler_port))
    print(str(client), flush=True)
    futures = client.map(square, range(100))
    total = client.submit(sum, futures)
    print(total.result())
    futures = client.map(get_hostname, range(500))
    output = client.gather(futures)
    print('\n'.join(output))

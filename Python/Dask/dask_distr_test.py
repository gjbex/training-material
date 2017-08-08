#!/usr/bin/env python

from argparse import ArgumentParser
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
    arg_parser = ArgumentParser(description='compute sum of squares and check '
                                            'task placement')
    arg_parser.add_argument('--scheduler', help='scheduler host')
    arg_parser.add_argument('--scheduler_port', default='8786',
                            help='scheduler port to use')
    arg_parser.add_argument('--n', type=int, default=100,
                            help='number of terms in sum')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='give verbose output')
    options = arg_parser.parse_args()
    client = Client('{0}:{1}'.format(options.scheduler,
                                     options.scheduler_port))
    if options.verbose:
        print('Client: {0}'.format(str(client)), flush=True)
    futures = client.map(square, range(options.n))
    total = client.submit(sum, futures)
    expected_total = (options.n - 1)*options.n*(2*options.n - 1)//6
    print('sum_i=0..99 i^2 = {0:d}, expected {1:d}'.format(total.result(),
                                                           expected_total))
    futures = client.map(get_hostname, range(options.n))
    process_locations = client.gather(futures)
    if options.verbose:
        print('task placement:')
        print('\t' + '\n\t'.join(process_locations))
    count = dict()
    for process_location in process_locations:
        _, _, hostname = process_location.split()
        if hostname not in count:
            count[hostname] = 0
        count[hostname] += 1
    for hostname, nr_tasks in count.items():
        print('{0:d} tasks on {1}'.format(nr_tasks, hostname))

#!/usr/bin/env python

from argparse import ArgumentParser
from concurrent.futures import ProcessPoolExecutor
import csv
from datetime import datetime, timedelta
import random
import sys


def write_file(args):
    file_name, rows, curr_time, delta_time, curr_vals, delta_val = args
    fieldnames = [
        'timestamp',
        *['C{0:d}'.format(i + 1) for i in range(len(curr_vals))],
    ]
    with open(file_name, 'w', newline='') as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        values = []
        for _ in range(rows//2):
            data = {'C{0:d}'.format(i + 1): curr_vals[i]
                    for i in range(len(curr_vals))}
            data['timestamp'] = curr_time
            writer.writerow(data)
            values.append(data)
            curr_time += delta_time
            curr_vals = [x + random.uniform(-delta_val, delta_val)
                         for x in curr_vals]
        while values:
            data = values.pop()
            data['timestamp'] = curr_time
            writer.writerow(data)
            curr_time += delta_time
    return file_name

            
if __name__ == '__main__':
    arg_parser = ArgumentParser(description='create a set of CSV files')
    arg_parser.add_argument('--files', type=int, default=1,
                            help='number of files to create')
    arg_parser.add_argument('base_name', help='base file name to use')
    arg_parser.add_argument('--cols', type=int, default=1,
                            help='number of columns to generate')
    arg_parser.add_argument('--rows', type=int, default=100,
                            help='number of rows to generate per file')
    arg_parser.add_argument('--workers', type=int, default=None,
                            help='number of workersto use')
    options = arg_parser.parse_args()
    curr_time = datetime.now()
    delta_time = timedelta(seconds=1)
    curr_vals = [1.0]*options.cols
    delta_val = 0.01
    with ProcessPoolExecutor(max_workers=options.workers) as executor:
        args = [('{0}_{1:04d}.csv'.format(options.base_name, i + 1),
                 options.rows, curr_time + i*options.rows*delta_time,
                 delta_time, curr_vals, delta_val) for i in range(options.files)]
        for file_name in executor.map(write_file, args):
            print('{0} done'.format(file_name))

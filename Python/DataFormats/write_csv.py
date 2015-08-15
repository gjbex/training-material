#!/usr/bin/env python

from argparse import ArgumentParser, FileType
import csv
import random
import sys


def main():
    arg_parser = ArgumentParser(description='write random data to CSV file')
    arg_parser.add_argument('file', type=FileType('w'),
                            help='file to write to')
    options = arg_parser.parse_args()
    col_names = ['label', 'index', 'temperature', 'pressure']
    labels = ['alpha', 'beta', 'gamma', 'delta', 'epsilon']
    indices = list(range(1, 6))
    temperatures = [273.15 + 20*random.random() for _ in range(len(labels))]
    pressures = [101000 + 2000*random.random() for _ in range(len(labels))]
    csv_writer = csv.writer(options.file)
    csv_writer.writerow(col_names)
    for row in zip(labels, indices, temperatures, pressures):
        csv_writer.writerow(row)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

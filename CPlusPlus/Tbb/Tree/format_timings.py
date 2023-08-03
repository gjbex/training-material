#!/usr/bin/env python

from argparse import ArgumentParser
import re

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='format timing info '
                                            'from PBS ouput files')
    arg_parser.add_argument('files', nargs='+', help='files to parse')
    options = arg_parser.parse_args()
    print('cores time')
    for file_name in options.files:
        time_avg = 0.0
        nr_timings = 0
        nr_procs = 0
        with open(file_name, 'r') as file:
            for line in file:
                match = re.match(r'^time: ([^s]+)\s+s$', line)
                if match is not None:
                    time_avg = float(match[1])
                    nr_timings += 1
                    continue
                match = re.match('^procs: (\d+)$', line)
                if match is not None:
                    nr_procs = int(match[1])
            print('{0:d} {1:.6f}'.format(nr_procs, time_avg/nr_timings))

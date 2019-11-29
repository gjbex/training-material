#!/usr/bin/env python

from argparse import ArgumentParser
from itertools import chain
import shlex
import sys


def parse_job_script(file_name):
    args = list()
    with open(file_name) as file:
        for line in file:
            if line.lstrip().startswith('#PBS '):
                _, options = line.split(' ', 1)
                args.extend(shlex.split(options.strip()))
    return args


def main():
    file_parser = ArgumentParser(add_help=False)
    file_parser.add_argument('-l', action='append', dest='resource_specs',
                             help='resources can be specified with multiple '
                                  '-l instances')
    arg_parser = ArgumentParser(description='Experiment with two stage '
                                            'command line argument parsing',
                                parents=[file_parser])
    arg_parser.add_argument('jobscript', help='job script file')
    options, unparsed = arg_parser.parse_known_args()
    file_args = parse_job_script(options.jobscript)
    _, file_unparsed = file_parser.parse_known_args(file_args,
                                                    namespace=options)
    if options.resource_specs:
        specs = chain.from_iterable(map(lambda x: x.split(','),
                                        options.resource_specs))
        print('resources: ' + ', '.join(specs))
    print('unparsed command line args: ' + ', '.join(unparsed))
    print('unparsed file line args: ' + ', '.join(file_unparsed))
    return 0


if __name__ == '__main__':
    STATUS = main()
    sys.exit(STATUS)

#!/usr/bin/env python

from argparse import ArgumentParser
from itertools import chain


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='illustration of how to '
                                            'use options that can occur '
                                            'multiple times, and not '
                                            'handling all')
    arg_parser.add_argument('-l', action='append', dest='resoure_specs',
                            help='resources can be specified with '
                                 'multiple -l options')
    arg_parser.add_argument('-A', dest='account', help='credit account')
    options, unparsed = arg_parser.parse_known_args()
    if options.resoure_specs:
        specs = chain.from_iterable(map(lambda x: x.split(','),
                                        options.resoure_specs))
        print('resources: ' + ', '.join(specs))
    if options.account:
        print('account: ' + options.account)
    print('unparsed: ' + ', '.join(unparsed))

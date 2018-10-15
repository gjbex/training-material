#!/usr/bin/env python

from argparse import ArgumentParser


if __name__ == '__main__':
    arg_parser = ArgumentParser()
    arg_parser.add_argument('-l', action='append', dest='resoure_specs')
    options, unparsed = arg_parser.parse_known_args()
    for resoure_spec in options.resoure_specs:
        print(resoure_spec)
    print('unparsed: ', ', '.join(unparsed))

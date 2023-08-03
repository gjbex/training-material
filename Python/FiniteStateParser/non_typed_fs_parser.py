#!/usr/bin/env python
'''script to parse block structured data file and transform the data'''

import argparse
from parser import BlockParser
import parser_errors as err


def main():
    '''function to be executed when this module is used as an executable'''
    arg_parser = argparse.ArgumentParser(
        description='parse and reformat block structured data file')
    arg_parser.add_argument('file', action='store', nargs=1,
                            help='file to parse and reformat')
    arg_parser.add_argument('-v', action='store', dest='verbosity',
                            default=0,
                            help='verbosity level')
    args = arg_parser.parse_args()
    parser = BlockParser()
    parser.set_verbosity(args.verbosity)
    print('verbosity: {0}'.format(parser._verbose))
    try:
        with open(args.file[0], 'r') as block_file:
            blocks = parser.parse(block_file)
    except IOError as exception:
        print('### error: {0}'.format(exception))
        exit(2)
    except err.ParseError as exception:
        print('### error on {0}'.format(exception))
        exit(3)
    except err.UnknownStateError as exception:
        print('### interal parser error: {0}'.format(exception))
        exit(4)
    for data_block in blocks:
        data_block.sort_data()
        for value in data_block.get_data():
            print('{0}: "{1}""'.format(data_block.get_name(), value))

if __name__ == '__main__':
    main()

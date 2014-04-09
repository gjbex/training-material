#!/usr/bin/env python

from argparse import ArgumentParser
import logging, math, os, sys

def do_stuff(n):
    if n < 0:
        logging.error('can not do stuff for {0}'.format(n))
        return 1
    for i in xrange(n):
        logging.info('doing stuff {0}'.format(str(i)))
        print 'doing {0}: {1:.4f}'.format(i, math.sqrt(i))
        logging.info('done stuff {0}'.format(str(i)))
    return 0

def main():
    arg_parser = ArgumentParser(description='example for logging facility')
    arg_parser.add_argument('-log', dest='log_file',
                            help='name of log file')
    arg_parser.add_argument('-info', action='store_true',
                            help='set log level to info')
    arg_parser.add_argument('-new_log', action='store_true',
                            help='overwrite existing log file')
    arg_parser.add_argument('-n', type=int, default=1,
                            help='number of times to do stuff')
    options = arg_parser.parse_args()
    format_str = '%(asctime)s:%(levelname)s:%(message)s'
    if options.info:
        level = logging.INFO
    else:
        level = logging.WARNING
    if options.log_file:
        filename = options.log_file
        exists = os.path.exists(filename)
    else:
        filename = None
        exists = False
    if options.new_log:
        filemode = 'w'
    else:
        filemode = 'a'
    logging.basicConfig(level=level, filename=filename, filemode=filemode,
                        format=format_str)
    if exists:
        logging.warn('overwriting existing log file')
    logging.info('application started')
    logging.info('logger initialized')
    status = do_stuff(options.n)
    logging.info('application ended')
    return status

if __name__ == '__main__':
    status = main()
    sys.exit(status)


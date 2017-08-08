#!/usr/bin/env python

from argparse import ArgumentParser
import dask.dataframe as dd
from distributed import Client
import sys

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute statistical measures '
                                            'over CSV file columns')
    arg_parser.add_argument('dir', help='directory with data files')
    arg_parser.add_argument('--scheduler', help='scheduler host')
    arg_parser.add_argument('--scheduler_port', default='8786',
                            help='scheduler port to use')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='generate verbose output')
    options = arg_parser.parse_args()
    client = Client('{0}:{1}'.format(options.scheduler,
                                     options.scheduler_port))
    if options.verbose:
        print('Client: {0}'.format(str(client)), flush=True, file=sys.stderr)
    df = dd.read_csv('{0}/time_series_*.csv'.format(options.dir), parse_dates=['timestamp'])
    result = df.groupby(df.timestamp.dt.month).mean().compute()
    result.to_csv('{0}/result.csv'.format(options.dir))

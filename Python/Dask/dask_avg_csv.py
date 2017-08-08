#!/usr/bin/env python

from argparse import ArgumentParser
import dask.dataframe as dd

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute statistical measures '
                                            'over CSV file columns')
    arg_parser.add_argument('dir', help='directory with data files')
    options = arg_parser.parse_args()
    df = dd.read_csv('{0}/time_series_*.csv'.format(options.dir), parse_dates=['timestamp'])
    result = df.groupby(df.timestamp.dt.month).mean().compute()
    result.to_csv('{0}/result.csv'.format(options.dir))

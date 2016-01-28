#!/usr/bin/env python

options_fmt = '{prefix:s}{key:s} = {value:s}\n'


def print_options(file, options, prefix='# '):
    for key, value in options.__dict__.items():
        file.write(options_fmt.format(prefix=prefix, key=key,
                                      value=str(value)))

#!/usr/bin/env python

from argparse import ArgumentParser
import subprocess
import os

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='experiment with subprocess '
                                            'enrironments')
    arg_parser.add_argument('value', nargs='?',
                            help='value to set VALUE to, if not '
                                 'given, the environment variable '
                                 'will be used')
    options = arg_parser.parse_args()
    if options.value:
        os.environ['VALUE'] = options.value
    cmd = subprocess.run(['echo $VALUE'], shell=True,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    if cmd.returncode == 0:
        print(cmd.stdout.decode('utf-8'))
    else:
        print(cmd.stderr.decode('utf-8'))

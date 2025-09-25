#!/usr/bin/env python

from argparse import ArgumentParser
from configparser import ConfigParser
from pathlib import Path

def dump_options(settings):
    for key, value in settings.items():
        print(f'{key} = {value}')

if __name__ == '__main__':
    config_parser  = ConfigParser()
    sys_conf_path = Path('system.conf')
    if sys_conf_path.exists():
        config_parser.read('system.conf')
        options = dict(config_parser.items('DEFAULT'))
    else:
        options = {}
    arg_parser = ArgumentParser(description='experiment with '
                                            'configuration files and '
                                            'command line arguments')
    arg_parser.add_argument('--conf', help='configuration file')
    argv, remaining_argv = arg_parser.parse_known_args()
    if argv.conf:
        config_parser = ConfigParser()
        config_parser.read(argv.conf)
        options |= dict(config_parser.items('DEFAULT'))
    arg_parser.set_defaults(**options)
    arg_parser.add_argument('--action', help='action to do')
    arg_parser.add_argument('--name', help='name for action')
    options = arg_parser.parse_args(remaining_argv)
    dump_options(options.__dict__)

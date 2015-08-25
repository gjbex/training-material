#!/usr/bin/env python

from configparser import SafeConfigParser
import sys


def main():
    if len(sys.argv) > 1:
        cfg_file = sys.argv[1]
    else:
        cfg_file = 'defaults.conf'
    cfg_parser = SafeConfigParser()
    cfg_parser.read(cfg_file)
    print('Sections:')
    for section in cfg_parser.sections():
        print('\t{0}:'.format(section))
        for item in cfg_parser.items(section):
            print('\t\t{0}: "{1}"'.format(item[0], item[1]))
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

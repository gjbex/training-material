#!/usr/bin/env python

import re
import sys


def main():
    if len(sys.argv) < 2:
        sys.stderr.write('### error: no file specified\n')
        return 1
    out_file_name_prefix = sys.argv[1]
    out_file = None
    for line in sys.stdin:
        if line.strip().startswith('#') or len(line.strip()) == 0:
            continue
        match = re.match(r'\s*size\s*=\s*(\d+)', line)
        if match is not None:
            out_file = open('{0}_{1}.txt'.format(out_file_name_prefix, match[1]), 'w')
            continue
        if out_file is None:
            sys.stderr.write('### error: no size in file before first data\n')
            return 2
        else:
            out_file.write(line)
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)

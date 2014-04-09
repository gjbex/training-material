#!/usr/bin/env python

import re, sys

def convert2seconds(time_str):
    hours, minutes, seconds = 0, 0, 0
    h_expr = r'(?:(\d+)\s*h(?:ours)?)?'
    m_expr = r'(?:(\d+)\s*m(?:inutes)?)?'
    s_expr = r'(?:(\d+)\s*s(?:econds)?)?'
    match = re.match(h_expr + r'\s*' + m_expr + r'\s*' + s_expr + r'\s*$',
                     time_str, re.I)
    if match is not None:
        if match.group(1) is not None:
            hours = int(match.group(1))
        if match.group(2) is not None:
            minutes = int(match.group(2))
        if match.group(3) is not None:
            seconds = int(match.group(3))
    else:
        sys.stderr.write('### error: invalid time string\n')
        sys.exit(2)
    return hours*3600 + minutes*60 + seconds

def main():
    if len(sys.argv) < 2:
        sys.stderr.write('### error: no time string given\n')
        return 1
    time_str = sys.argv[1]
    seconds = convert2seconds(time_str)
    print seconds
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)


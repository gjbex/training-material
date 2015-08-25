#!/usr/bin/env python

import re, sys

def main():
    phone_number = sys.argv[1]
    regex_str = r'''0            # area code starts with 0
                    [1-9]\d?     # area code has 1 or 2 digits
                    /            # separator
                    [1-9]\d{5,6} # 6 or 7 digit number'''
    if re.match(regex_str, phone_number, re.VERBOSE):
        print 'ok'
    else:
        print 'not ok'
    return 0

if __name__ == '__main__':
    status = main()
    sys.exit(status)


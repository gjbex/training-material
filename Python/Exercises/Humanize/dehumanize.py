#!/usr/bin/env python


def dehumanize(str_value, base=10, digits=1):
    '''convert a human readable value to a floating point number

    Parameters
    ----------
    str_value : str
        value to convert
    base : int
        base to use, either 2 or 10, default is 10
    digits : int
        decimal digits to use in format string, default is 1

    Returns
    -------
    float
        floating point value

    Raises
    ------
    ValueError
        raised when base is neither 2 nor 10

    Examples
    --------
    >>> dehumanize('12.3 K')
    '12300.0'
    >>> dehumanize('.23 K')
    '230.0'
    >>> dehumanize('12. K')
    '12000.0'
    >>> dehumanize('12 K')
    '12000.0'
    >>> dehumanize('-12 K')
    '-12000.0'
    >>> dehumanize('1240')
    '1240.0'
    >>> dehumanize('123.45 Kb')
    '123450.0 b'
    >>> dehumanize('1 K', digits=2, base=2)
    '1024.00'
    '''
    import re
    if base not in [2, 10]:
        raise ValueError('base should be 2 or 10, not {:d}'.format(base))
    thousands = 10**3 if base == 10 else 2**10
    if not (
        match := re.match(
            r'^\s*((?:\+|-)?(?:\d+\.?\d*)|(?:\d*\.\d+))\s*([ \w]*)$', str_value
        )
    ):
        raise ValueError("'{0:s}' is not a valid quantity".format(str_value))
    n = float(match.group(1))
    if match.group(2):
        order = match.group(2)[0].lower()
        units = match.group(2)[1:] if len(match.group(2)) > 1 else ''
        if units and not units.startswith(' '):
            units = f' {units}'
    else:
        order, units = '', ''
    fmt_str = '{{0:.{}f}}{{1:s}}'.format(digits)
    orders = {
        '': 0,
        'k': 1,
        'm': 2,
        'g': 3,
        't': 4,
        'p': 5,
    }
    return fmt_str.format(n*thousands**orders[order], units)


if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    arg_parser = ArgumentParser(description='convert numbers to '
                                            'human-readable format')
    arg_parser.add_argument('str_value', nargs='?',
                            help='human readable value to convert')
    arg_parser.add_argument('-d', type=int, default=0,
                            help='number of significant digits')
    arg_parser.add_argument('-b', action='store_true',
                            help='use base 2')
    arg_parser.add_argument('-u', default='', help='unit to display')
    options = arg_parser.parse_args()
    base = 2 if options.b else 10
    if options.str_value:
        print('{0:s}'.format(dehumanize(options.str_value, base=base,
                                        digits=options.d)))
    else:
        for line in sys.stdin:
            print('{0:s}'.format(dehumanize(line.strip(), base=base,
                                            digits=options.d)))

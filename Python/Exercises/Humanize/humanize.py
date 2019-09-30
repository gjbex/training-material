#!/usr/bin/env python


def humanize(n, base=10, digits=1, unit=''):
    '''convert a floating point number to a human-readable format

    Parameters
    ----------
    n : float or str
        number to convert, it can a string representation of
        a floating point number
    base : int
        base to use, either 2 or 10, default is 10
    digits : int
        decimal digits to use in format string, default is 1
    unit : str
        unit to use in format string, default is ''

    Returns
    -------
    str
        formatted string

    Raises
    ------
    ValueError
        raised when base is neither 2 nor 10

    Examples
    --------
    >>> humanize(1234)
    '1.2 K'
    >>> humanize(1234, digits=2)
    '1.23 K'
    >>> humanize(1234, base=2, digits=2)
    '1.21 K'
    >>> humanize(1234, unit='B')
    '1.2 KB'
    >>> humanize('1234.56', digits=4, unit='B')
    '1.2346 KB'
    >>> humanize(0.0123)
    '12.3 m'
    '''
    import math
    if base != 2 and base != 10:
        raise ValueError('base should be 2 or 10, not {:d}'.format(base))
    thousands = 3 if base == 10 else 10
    orders = {
        -3: 'n',
        -2: 'u',
        -1: 'm',
        0: '',
        1: 'K',
        2: 'M',
        3: 'G',
        4: 'T',
        5: 'P',
    }
    fmt_str = '{{0:.{}f}} {{1:s}}{{2:s}}'.format(digits)
    exp = math.log(math.fabs(float(n)), base**thousands)
    exp = int(exp - (1 if exp < 0 else 0))
    number = float(n)/base**(exp*thousands)
    return fmt_str.format(number, orders[exp], unit)


def check_line(line):
    try:
        _ = float(line)
        return True
    except:
        return False


if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    arg_parser = ArgumentParser(description='convert numbers to '
                                            'human-readable format')
    arg_parser.add_argument('n', type=float, nargs='?',
                            help='number to convert')
    arg_parser.add_argument('-d', type=int, default=1,
                            help='number of significant digits')
    arg_parser.add_argument('-b', action='store_true',
                            help='use base 2')
    arg_parser.add_argument('-u', default='', help='unit to display')
    options = arg_parser.parse_args()
    base = 2 if options.b else 10
    if options.n:
        print('{0:s}'.format(humanize(options.n, base=base, digits=options.d,
                                      unit=options.u)))
    else:
        for line in sys.stdin:
            if check_line(line):
                print('{0:s}'.format(humanize(line.strip(), base=base,
                                              digits=options.d,
                                              unit=options.u)))

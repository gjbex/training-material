#!/usr/bin/env python


def colorize(text, style='OKGREEN'):
    '''apply a style to a string

    Parameters
    ----------
    text : str
        string to apply the style to
    style : str
        style to use, one of HEADER, OKBLUE, OKGREEN, WARNING,
        FAIL, BOLD, UNDERLINE

    Returns
    -------
    str
        string with terminal style info if the terminal supports
        colors, the unmodified string otherwise

    Raises
    ------
    ValueError
        raised if an unknown style is used
    '''
    import os
    terminals = ['xterm', 'rxvt', 'color']
    if any(map(lambda x: x in os.environ['TERM'], terminals)):
        styles = {
            'HEADER': '\033[95m',
            'OKBLUE': '\033[94m',
            'OKGREEN': '\033[92m',
            'WARNING': '\033[93m',
            'FAIL': '\033[91m',
            'ENDC': '\033[0m',
            'BOLD': '\033[1m',
            'UNDERLINE': '\033[4m',
        }
        if style not in styles:
            raise ValueError('unknown style {}'.format(style))
        return styles[style] + text + styles['ENDC']
    else:
        return text


if __name__ == '__main__':
    from argparse import ArgumentParser
    import sys
    arg_parser = ArgumentParser(description='colorize text')
    arg_parser.add_argument('string', help='string to colorize')
    arg_parser.add_argument('-e', action='store_true',
                            help='embed colored text for demo')
    arg_parser.add_argument('-s', help='style to use')
    options = arg_parser.parse_args()
    colorized = colorize(options.string, options.s)
    if options.e:
        sys.stdout.write('before ')
    sys.stdout.write(colorized)
    if options.e:
        sys.stdout.write(' after\n')

#!/usr/bin/env python

from argparse import ArgumentParser
from math import pi, sin
from quad import integrate, sin2

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='compute quadratures')
    arg_parser.add_argument('--n', type=int, default=1000,
                            help='number of integration points')
    arg_parser.add_argument('--version', default='quad',
                            choices=['quad', 'quad_prof', 'quad_prof_indiv',
                                     'quad_pure'],
                            help='version to run')
    options = arg_parser.parse_args()
    if options.version == 'quad':
        from quad import integrate, sin2
    elif options.version == 'quad_prof':
        from quad_prof import integrate, sin2
    elif options.version == 'quad_prof_indiv':
        from quad_prof_indiv import integrate, sin2
    elif options.version == 'quad_pure':
        from quad_pure import integrate, sin2
    print(integrate(sin2, 0.0, 3.2*pi, options.n))
    print(integrate(sin, 0.0, 3.2*pi, options.n))

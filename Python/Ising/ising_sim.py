#!/usr/bin/env python

if __name__ == '__main__':
    from argparse import ArgumentParser
    import importlib
    import random
    import sys
    from runner import DomainSizeRunner
    from averager import Averager
    from util import print_options

    arg_parser = ArgumentParser(description='2D ising system simulaation')
    arg_parser.add_argument('--N', type=int, default=10,
                            help='system size, i.e., N x N')
    arg_parser.add_argument('--J', type=float, default=1.0,
                            help='spin-spin interactino energy')
    arg_parser.add_argument('--H', type=float, default=0.0,
                            help='magnetic field')
    arg_parser.add_argument('--T', default='1.5',
                            help='temerature in units k_b, can be '
                                 'a comma-separated list')
    arg_parser.add_argument('--steps', type=int, default=1000,
                            help='number of simulation steps')
    arg_parser.add_argument('--burn_in', type=int, default=100,
                            help='burn in for averages')
    arg_parser.add_argument('--sample_period', type=int, default=10,
                            help='sample period for averages')
    arg_parser.add_argument('--window', type=int, default=20,
                            help='window size for convergence test')
    arg_parser.add_argument('--max_slope', type=float, default=1e-4,
                            help='maximum slope as convergence criterion')
    arg_parser.add_argument('--runs', type=int, default=10,
                            help='number of independent runs')
    arg_parser.add_argument('--file', default='result',
                            help='output file base name')
    arg_parser.add_argument('--verbose', type=int, default=1,
                            help='show progress information, the '
                                 'higher the value, the more detail')
    arg_parser.add_argument('--seed', type=int,
                            help='seed for random number generator, '
                                 'only needed for development')
    arg_parser.add_argument('--python', action='store_true',
                            help='use pure Python implementation')
    options = arg_parser.parse_args()
    magn_file = open('{0}-magn.txt'.format(options.file), 'w')
    domain_file = open('{0}-domains.txt'.format(options.file), 'w')
    if options.seed is None:
        seed = random.randint(0, 1000000000)
    else:
        seed = options.seed
    if options.python:
        ising_module = importlib.import_module('ising')
    else:
        ising_module = importlib.import_module('ising_cxx')
    hdr_line_fmt = 'T {M:s} {E:s} {deltaE2:s}\n'
    hdr_fmt = '{0:s} {0:s}_std {0:s}_min {0:s}_max'
    val_line_fmt = '{T:.4f} {M:s} {E:s} {deltaE2:s}\n'
    val_fmt = '{mean:.5e} {std:.5e} {min:.5e} {max:.5e}'
    M_hdr = hdr_fmt.format('M')
    E_hdr = hdr_fmt.format('E')
    deltaE2_hdr = hdr_fmt.format('deltaE^2')
    magn_file.write(hdr_line_fmt.format(M=M_hdr, E=E_hdr,
                                        deltaE2=deltaE2_hdr))
    print_options(magn_file, options)
    domain_file.write('T domain_sizes\n')
    print_options(domain_file, options)
    for T in (float(T_str) for T_str in options.T.split(',')):
        if options.verbose > 0:
            sys.stderr.write('# computing T = {0:.4f}\n'.format(T))
        ising = ising_module.IsingSystem(options.N, options.J, options.H, T)
        ising.init_random(seed)
        runner = DomainSizeRunner(ising=None, steps=options.steps,
                                  is_verbose=options.verbose - 2,
                                  burn_in=options.burn_in,
                                  sample_period=options.sample_period,
                                  window=options.window)
        averager = Averager(runner, ising, is_verbose=options.verbose - 1)
        averager.average(options.runs)
        M_values = averager.get('M mean')
        M_str = val_fmt.format(**M_values)
        E_values = averager.get('E mean')
        E_str = val_fmt.format(**E_values)
        deltaE2_values = averager.get('deltaE^2')
        deltaE2_str = val_fmt.format(**deltaE2_values)
        magn_file.write(val_line_fmt.format(T=T, M=M_str, E=E_str,
                                            deltaE2=deltaE2_str))
        magn_file.flush()
        domains = averager.get('domains')
        distrubtion = ','.join(['{0:d}:{1:.8e}'.format(k, v)
                                for k, v in domains.items()])
        domain_file.write('{0:.4f} {1:s}\n'.format(T, distrubtion))
        domain_file.flush()
    magn_file.close()
    domain_file.close()

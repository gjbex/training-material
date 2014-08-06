#!/usr/bin/env python


if __name__ == '__main__':

    from argparse import ArgumentParser
    import importlib, random, sys

    from ising import IsingSystem
    from runner import EquilibriumRunner
    from averager import Averager

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
    arg_parser.add_argument('--steps', type=int, default=10,
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
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show progress information')
    arg_parser.add_argument('--seed', type=int,
                            help='seed for random number generator, '
                                 'only needed for development')
    arg_parser.add_argument('--python', action='store_true',
                            help='use pure Python implementation')
    options = arg_parser.parse_args()
    if options.seed is None:
        seed = random.randint(0, 1000000000)
    else:
        seed = options.seed
    if options.python:
        ising_module = importlib.import_module('ising')
    else:
        ising_module = importlib.import_module('ising_cxx')
    print 'T,M,M_std,M_min,M_max'
    for T in (float(T_str) for T_str in options.T.split(',')):
        if options.verbose:
            sys.stderr.write('# computing T = {0:.4f}\n'.format(T))
        ising = ising_module.IsingSystem(options.N, options.J, options.H, T)
        ising.init_random(seed)
        runner = EquilibriumRunner(ising=None, steps=options.steps,
                                   is_verbose=options.verbose,
                                   burn_in=options.burn_in,
                                   sample_period=options.sample_period,
                                   window=options.window)
        averager = Averager(runner, ising, is_verbose=options.verbose)
        averager.average(options.runs)
        M_values = averager.get('M mean')
        M_fmt = '{T:.4f},{mean:.3f},{std:.3e},{min:.3f},{max:.3f}'
        print M_fmt.format(T=T, **M_values)
        sys.stdout.flush()


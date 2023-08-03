#!/usr/bin/env python


if __name__ == '__main__':
    from argparse import ArgumentParser
    import random
    import sys
    import numpy as np
    from ising_cxx import IsingSystem
    from runner import (SingleRunner, MovieRunner, ActivityHeatmapRunner,
                        EquilibriumRunner)

    arg_parser = ArgumentParser(description='2D ising system simulaation')
    arg_parser.add_argument('--N', type=int, default=10,
                            help='system size, i.e., N x N')
    arg_parser.add_argument('--J', type=float, default=1.0,
                            help='spin-spin interactino energy')
    arg_parser.add_argument('--H', type=float, default=0.0,
                            help='magnetic field')
    arg_parser.add_argument('--T', type=float, default=1.5,
                            help='temerature in units k_b')
    arg_parser.add_argument('--steps', type=int, default=10,
                            help='number of simulation steps')
    arg_parser.add_argument('--burn_in', type=int, default=100,
                            help='burn in for averages')
    arg_parser.add_argument('--sample_period', type=int, default=10,
                            help='sample period for averages')
    arg_parser.add_argument('--window', type=int, default=20,
                            help='window size for convergence test')
    arg_parser.add_argument('--mode', choices=['single_run',
                                               'movie',
                                               'equilibrium',
                                               'heatmap'],
                            required=True, help='run mode')
    arg_parser.add_argument('--seed', type=int,
                            help='random number generator seed')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show progress information')
    options = arg_parser.parse_args()
    ising = IsingSystem(options.N, options.J, options.H, options.T)
    seed = options.seed if options.seed else random.randint(0, 1000000000)
    ising.init_random(seed)
    if options.mode == 'single_run':
        runner = SingleRunner(ising, is_verbose=options.verbose)
    elif options.mode == 'movie':
        runner = MovieRunner(ising)
    elif options.mode == 'heatmap':
        runner = ActivityHeatmapRunner(ising, is_verbose=options.verbose,
                                       burn_in=options.burn_in)
    elif options.mode == 'equilibrium':
        runner = EquilibriumRunner(ising, is_verbose=options.verbose,
                                   burn_in=options.burn_in,
                                   sample_period=options.sample_period,
                                   window=options.window)
    else:
        sys.stderr.write('# error: unknown mode\n')
        sys.exit(1)
    runner.run(options.steps)
    if options.mode == 'heatmap':
        np.savetxt(sys.stdout, runner.get('heatmap'))
    elif options.mode == 'equilibrium':
        for quantity in runner.quantities():
            print('{0:s} = {1:.4e}'.format(quantity, runner.get(quantity)))

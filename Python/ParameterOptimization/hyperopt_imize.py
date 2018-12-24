#!/usr/bin/env python

from argparse import ArgumentParser
from hyperopt import fmin, hp, STATUS_OK, tpe, Trials
import subprocess
import sys
import time


def function(params):
    x, y = params
    cmd = ['./continuous_process.py', '--x', str(x),
           '--y', str(y)]
    process = subprocess.run(cmd, stdout=subprocess.PIPE,
                             encoding='utf8')
    return {
        'loss': float(process.stdout), 'time': time.time(),
        'x': x, 'y': y, 'status': STATUS_OK,
    }


def optimize(max_evals):
    space = (hp.uniform('x', -3.0, 3.0),
             hp.uniform('y', -3.0, 3.0))
    trials = Trials()
    best = fmin(function, space=space, algo=tpe.suggest,
                max_evals=max_evals, trials=trials)
    return best, trials


def main():
    arg_parser = ArgumentParser(description='optimize external '
                                            'process')
    arg_parser.add_argument('--max-evals', type=int,
                            default=100, help='maximum evals')
    arg_parser.add_argument('--trials', action='store_true',
                            help='display trials')
    options = arg_parser.parse_args()
    best, trials = optimize(options.max_evals)
    if options.trials:
        print('x y value')
        for trial in trials:
            x = trial['result']['x']
            y = trial['result']['y']
            value = -trial['result']['loss']
            print(f'{x:6.3f} {y:6.3f} {value:10.3e}')
    x, y = best['x'], best['y']
    value = function((x, y))['loss']
    print(f'# best: f({x:6.3f}, {y:6.3f}) = {-value:10.3e}')
    return 0


if __name__ == '__main__':
    sys.exit(main())

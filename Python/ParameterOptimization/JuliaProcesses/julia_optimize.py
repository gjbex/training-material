#!/usr/bin/env python

from argparse import ArgumentParser
import os
import subprocess
import sys
import time
from hyperopt import fmin, hp, STATUS_OK, tpe, Trials


def function(params):
    schedule, chunk, ppn = params
    # chunk is given as a floating point number
    chunk = int(chunk)
    # ppn ranges from 0 to 35 (inclusive)
    ppn = 1 + int(ppn)
    environ = os.environ.copy()
    environ['OMP_SCHEDULE'] = f'{schedule},{chunk}'
    environ['OMP_NUM_THREADS'] = f'{ppn}'
    cmd = ['./julia_omp.exe 4096']
    runtimes = list()
    for _ in range(3):
        process = subprocess.run(cmd, stderr=subprocess.PIPE,
                                 stdout=subprocess.PIPE,
                                 env=environ, shell=True,
                                 encoding='utf8')
        runtimes.append(float(process.stderr))
    runtime = sum(runtimes)/len(runtimes)
    return {
        'loss': runtime, 'schedule': schedule, 'chunk': chunk,
        'ppn': ppn, 'status': STATUS_OK,
        'time': time.strftime('%Y-%m-%d %H:%M:%S'),
    }


def optimize(max_evals, max_ppn):
    space = hp.choice('schedule', [
        ('static', hp.qloguniform('chunk_s', 2, 11, 10),
         hp.randint('ppn_s', max_ppn)),
        ('dynamic', hp.qloguniform('chunk_d', 2, 11, 10),
         hp.randint('ppn_d', max_ppn)),
        ('guided', hp.qloguniform('chunk_g', 2, 11, 10),
         hp.randint('ppn_g', max_ppn)),
    ])
    trials = Trials()
    best = fmin(function, space=space, algo=tpe.suggest,
                max_evals=max_evals, trials=trials)
    return best, trials


def main():
    arg_parser = ArgumentParser(description='optimize external '
                                            'process')
    arg_parser.add_argument('--max-ppn', type=int, default=20,
                            help='maximum number of cores to use')
    arg_parser.add_argument('--max-evals', type=int,
                            default=100, help='maximum evals')
    arg_parser.add_argument('--trials', required=True,
                            help='file to save trials')
    options = arg_parser.parse_args()
    _, trials = optimize(options.max_evals, options.max_ppn)
    with open(options.trials, 'w') as trials_file:
        print('schedule,chunk,ppn,runtime', file=trials_file)
        for trial in trials.results:
            schedule = trial['schedule']
            chunk = trial['chunk']
            ppn = trial['ppn']
            runtime = trial['loss']
            print(f'{schedule},{chunk:d},{ppn:d},{runtime}',
                  file=trials_file)


if __name__ == '__main__':
    sys.exit(main())

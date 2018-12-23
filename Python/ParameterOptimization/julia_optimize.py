#!/usr/bin/env python

from argparse import ArgumentParser
from pathlib import Path
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
    omp_env = (f'schedule={schedule},chunk={int(chunk)},' +
               f'OMP_NUM_THREADS={ppn}')
    cmd = ['qsub', '-l', f'nodes=1:ppn={ppn}:haswell',
           '-v', omp_env, 'julia.pbs']
    process = subprocess.run(cmd, stdout=subprocess.PIPE,
                             encoding='utf8')
    job_id, *_ = process.stdout.split('.')
    print(f'### info: submitted job {job_id}', file=sys.stderr)
    output_file = Path(f'julia.pbs.o{job_id}')
    while not output_file.exists():
        time.sleep(3)
    print(f'### info: job {job_id} finished', file=sys.stderr)
    with open(f'julia.pbs.time{job_id}', 'r') as time_file:
        runtime = float(time_file.readline())
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
    arg_parser.add_argument('--trials', action='store_true',
                            help='display trials')
    options = arg_parser.parse_args()
    best, trials = optimize(options.max_evals, options.max_ppn)
    if options.trials:
        print('x y value')
        for trial in trials.results:
            schedule = trial['schedule']
            chunk = int(trial['chunk'])
            ppn = 1 + int(trial['ppn'])
            runtime = trial['loss']
            print(f'{schedule},{chunk:d} with {ppn:d} threads: '
                  f'{runtime}')
    schedule = best['schedule']
    chunk = int(best['chunk'])
    ppn = 1 + int(best['ppn'])
    print(f'{schedule},{chunk:d} with {ppn:d} threads')


if __name__ == '__main__':
    sys.exit(main())

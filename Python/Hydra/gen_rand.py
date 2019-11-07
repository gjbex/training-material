#!/usr/bin/env python

import hydra
import logging
import numpy as np
import sys

LOG = logging.getLogger(sys.argv[0])

@hydra.main(config_path='conf/config.yaml')
def gen_rand(cfg):
    if cfg.verbose:
        print(cfg.pretty(), file=sys.stderr)
    if cfg.n <= 0:
        LOG.error(f'negative number to generate {cfg.n}')
        return 1
    LOG.info(f'genrating {cfg.n} random numbers')
    LOG.info(f'using {cfg.distr.name} distribution')
    if cfg.distr.name == 'gauss':
        LOG.info(f'mu={cfg.distr.mu}, sigma={cfg.distr.sigma}')
        if cfg.distr.sigma <= 0:
            LOG.error(f'negative standard deviation {cfg.distr.sigma}')
            return 1
        numbers = np.random.normal(loc=cfg.distr.mu, scale=cfg.distr.sigma,
                                   size=(cfg.n,))
    elif cfg.distr.name == 'uniform':
        LOG.info(f'a={cfg.distr.a}, b={cfg.distr.b}')
        if cfg.distr.a >= cfg.distr.b:
            LOG.warning(f'lower bound exceed upper bound, '
                        f'{cfg.distr.a} >= {cfg.distr.b}')
        numbers = np.random.uniform(cfg.distr.a, cfg.distr.b, size=(cfg.n,))
    LOG.info('starting output')
    for number in numbers:
        print(number)
    LOG.info('output done')
    return 0

if __name__ == '__main__':
    status = gen_rand()
    sys.exit(status)

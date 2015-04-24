#!/usr/bin/env python

import itertools, math

def autocorrelation(iterator, max_distance):
    x_hist = [x for x in itertools.islice(iterator, max_distance + 1)]
    x_hist.reverse()
    prod_sum = [0.0 for _ in xrange(max_distance + 1)]
    n = 0
    sum_value = 0.0
    sum2_value = 0.0
    for x in iterator:
        n += 1
        x_hist.pop()
        x_hist.insert(0, x)
#        print x_hist
        sum_value += x
        sum2_value += x**2
        for l in xrange(max_distance + 1):
            prod_sum[l] += x*x_hist[l]
    assert math.fabs(sum2_value - prod_sum[0]) < 1e-6
    mean = sum_value/n
    mean_corr = [x/n for x in prod_sum]
    return [(x - mean**2)/(mean_corr[0] - mean**2) for x in mean_corr]

if __name__ == '__main__':

    from argparse import ArgumentParser
    import sys

    def main():
        arg_parser = ArgumentParser(description='compute autocorrelations')
        arg_parser.add_argument('--max-dist', type=int, default=10,
                                dest='max_dist', help='maximum distance')
        options = arg_parser.parse_args()
        data = (float(x) for x in sys.stdin)
        corr = autocorrelation(data, options.max_dist)
        print '\n'.join(['{0}\t{1:.3f}'.format(i, x)
                             for i, x in enumerate(corr)])
        return 0

    status = main()
    sys.exit(status)

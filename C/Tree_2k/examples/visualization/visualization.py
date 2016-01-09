#!/usr/bin/env python

from argparse import ArgumentParser
import collections
import matplotlib.pyplot as plt
import sys

Points = collections.namedtuple('Points', ['x', 'y'])


def compute_segments(line):
    data = [float(x) for x in line.strip().split()]
    if len(data) != 4:
        print("### error: can only plot 2D data", file=sys.stderr)
        sys.exit(1)
    center = data[0:2]
    extent = data[2:4]
    ur = (center[0] + extent[0], center[1] + extent[1])
    ul = (center[0] - extent[0], center[1] + extent[1])
    ll = (center[0] - extent[0], center[1] - extent[1])
    lr = (center[0] + extent[0], center[1] - extent[1])
    return [(ur, lr), (lr, ll), (ll, ul), (ul, ur)]


def parse_file(file_name):
    rectangles = []
    points = Points(x=[], y=[])
    with open(file_name) as in_file:
        state = 'init'
        for line in in_file:
            if line.startswith('# tree structure'):
                state = 'tree'
            elif line.startswith('# points'):
                state = 'points'
            elif line.startswith('#') or not line.strip():
                continue
            elif state == 'tree':
                rectangles.append(compute_segments(line))
            elif state == 'points':
                coords = [float(x) for x in line.strip().split()]
                points.x.append(coords[0])
                points.y.append(coords[1])
    return rectangles, points


def plot_tree(rectangles, points, center=[0.0, 0.0], limits=[1.2, 1.2],
              file_name=None):
    plt.xlim((center[0] - limits[0], center[0] + limits[0]))
    plt.ylim((center[1] - limits[1], center[1] + limits[1]))
    plt.plot(points.x, points.y, 'o')
    for rectangle in rectangles:
        for segment in rectangle:
            plt.plot((segment[0][0], segment[1][0]),
                     (segment[0][1], segment[1][1]), 'r-')
    if file_name:
        plt.savefig(file_name)
    else:
        plt.show()


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='visualize a tree_2k data '
                                            'structure')
    arg_parser.add_argument('input', help='file representing the tree_2k')
    arg_parser.add_argument('--output', help='image file name to create')
    arg_parser.add_argument('--center', nargs=2, type=float,
                            default=[0.0, 0.0], help='plot center')
    arg_parser.add_argument('--limits', nargs=2, type=float,
                            default=[1.2, 1.2], help='plot axis limits')
    options = arg_parser.parse_args()
    rect_segments, points = parse_file(options.input)
    plot_tree(rect_segments, points, options.center, options.limits,
              options.output)

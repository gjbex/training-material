#!/usr/bin/env python

from argparse import ArgumentParser
from bokeh.plotting import figure, output_file, show
import numpy as np

arg_parser = ArgumentParser(description='plots damped pendulum amplitude')
arg_parser.add_argument('--mu', type=float, default=0.2,
                        help='damping coefficient')
arg_parser.add_argument('--alpha', type=float, default=0.8,
                        help='alpha factor for envelope curves')
arg_parser.add_argument('--width', type=float, default=1.0,
                        help='line width for envelope curves')
arg_parser.add_argument('file', nargs='?', help='output file name')
options = arg_parser.parse_args()

# create function data
x = np.linspace(0.0, 20.0, 500)
y = np.exp(-options.mu*x)*np.cos(2.0*np.pi*x)
y_plus = np.exp(-options.mu*x)
y_min = -np.exp(-options.mu*x)

output_file(options.file, title='damped pendulum')
plot = figure(title='damped pendulum',
              x_axis_label='t', y_axis_label='theta')
plot.line(x, y)
plot.line(x, y_min, line_color='red', line_width=0.6, line_dash='2 2')
plot.line(x, y_plus, line_color='red', line_width=0.6, line_dash='2 2')
show(plot)

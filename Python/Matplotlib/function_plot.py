#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import matplotlib.pyplot as plt

arg_parser = ArgumentParser(description='plots damped pendulum amplitude')
arg_parser.add_argument('--mu', type=float, default=0.2,
                        help='damping coefficient')
arg_parser.add_argument('--alpha', type=float, default=0.8,
                        help='alpha factor for envelope curves')
arg_parser.add_argument('--width', type=float, default=1.0,
                        help='line width for envelope curves')
arg_parser.add_argument('file', nargs='?', help='output file name')
options = arg_parser.parse_args()

eq = (r'$\frac{d^2 \theta}{dt^2} = - \frac{g}{l} \theta ' +
      r'- \mu \frac{d\theta}{dt}$')
x = np.linspace(0.0, 20.0, 500)
y = np.exp(-options.mu*x)*np.cos(2.0*np.pi*x)
y_plus = np.exp(-options.mu*x)
y_min = -np.exp(-options.mu*x)

plt.plot(x, y)
plt.plot(x, y_plus, ':', alpha=options.alpha, color='red',
         linewidth=options.width)
plt.plot(x, y_min, ':', alpha=options.alpha, color='red',
         linewidth=options.width)
plt.xlabel(r'$t$', fontsize=14)
plt.ylabel(r'$\theta(t)$', fontsize=14)
plt.title('Damped pendulum')
plt.text(10.0, 0.65, eq, fontsize=18)

if options.file:
    plt.savefig(options.file)
else:
    plt.show()

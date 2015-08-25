#!/usr/bin/env python

import numpy as np
from scipy.integrate import ode


#
# f[0] = d theta1/dt = omega1
# f[1] = d theata2/dt = omega2
# f[2] = d omega1/dt = -(g/l1)*theta1 - k*(theta1 - theta2)
# f[3] = d omega2/dt = -(g/l2)*theta2 - k*(theta2 - theta1)
#
# y[0] = theta1
# y[1] = theta2
# y[2] = omega1
# y[3] = omega2
#
def functions(t, y, l1, l2, k):
    g = 9.81
    return [
        y[2],
        y[3],
        -(g/l1)*y[0] - k*(y[0] - y[1]),
        -(g/l2)*y[1] - k*(y[1] - y[0])
    ]


def jacobian(t, y, l1, l2, k):
    g = 9.81
    return [
        [0.0,                  0.0,  1.0,   0.0],
        [0.0,                  0.0,  0.0,   1.0],
        [-(g/l1) - k,            k,  0.0,   0.0],
        [k,            -(g/l2) - k,  0.0,   0.0]
    ]


def init_integrator(theta0_1, theta0_2, t0=0.0, l1=1.0, l2=1.0, k=0.1):
    integrator = ode(functions, jacobian).set_integrator('dopri5',
                                                         atol=1.0e-6,
                                                         rtol=0.0)
    integrator.set_initial_value([theta0_1, theta0_2, 0.0, 0.0], t0)
    integrator.set_f_params(l1, l2, k)
    integrator.set_jac_params(l1, l2, k)
    return integrator

if __name__ == '__main__':
    from argparse import ArgumentParser
    arg_parser = ArgumentParser(description='solved coupled pendulums')
    arg_parser.add_argument('--theta0_1', type=float, default=0.0,
                            help='initial theta of first pendulum')
    arg_parser.add_argument('--theta0_2', type=float, default=0.0,
                            help='initial theta of second pendulum')
    arg_parser.add_argument('--l1', type=float, default=1.0,
                            help='length of first pendulum')
    arg_parser.add_argument('--l2', type=float, default=1.0,
                            help='length of second pendulum')
    arg_parser.add_argument('--k', type=float, default=0.5,
                            help="Hooke's constant")
    arg_parser.add_argument('--t_max', type=float, default=10*2*np.pi,
                            help='maximum time')
    arg_parser.add_argument('--delta_t', type=float, default=0.01,
                            help='delta t')
    options = arg_parser.parse_args()
    integrator = init_integrator(options.theta0_1, options.theta0_2, t0=0.0,
                                 l1=options.l1, l2=options.l2, k=options.k)
    while integrator.successful() and integrator.t < options.t_max:
        integrator.integrate(integrator.t + options.delta_t)
        print('{0:.3f}\t{1:.5f}\t{2:.5f}'.format(integrator.t,
                                                 integrator.y[0],
                                                 integrator.y[1]))

#!/usr/bin/env python

from math import exp, sqrt, cos, pi

def f(x, y, x0=0.0, f=1.0, beta=0.5):
    r = sqrt((x - x0)**2 + y**2)
    return exp(-beta*r)*cos(2.0*pi*f*r)

if __name__ == '__main__':
    import numpy as np
    import matplotlib.pyplot as plt

    nr_point = 200
    x_min = -5.0
    x_max = 5.0
    y_min = -5.0
    y_max = 5.0
    x = np.linspace(-3.0, 3.0, nr_point)
    y = np.linspace(-3.0, 3.0, nr_point)
    v1 = np.reshape(np.array([f(i, j, x0=-1.0) for j in y for i in x]),
                    (nr_point, nr_point))
    v2 = np.reshape(np.array([f(i, j, x0=1.0, f=0.5) for j in y for i in x]),
                    (nr_point, nr_point))
    plt.imshow(v1 + v2, extent=[x_min, x_max, y_min, y_max])
    plt.grid(True)
    plt.show()



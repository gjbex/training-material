#!/usr/bin/env python

import numpy as np

def f(x, y, x0=0.0, freq=1.0, beta=0.5):
    r = np.sqrt((x - x0)**2 + y**2)
    return np.exp(-beta*r)*np.cos(2.0*np.pi*freq*r)

if __name__ == '__main__':
    import matplotlib.pyplot as plt

    nr_points = 200
    x_min = -5.0
    x_max = 5.0
    y_min = -5.0
    y_max = 5.0
    x = np.linspace(-3.0, 3.0, nr_points)
    y = np.linspace(-3.0, 3.0, nr_points)
    xx, yy = np.meshgrid(x, y)
    v1 = f(xx, yy, x0=-1.0)
    v2 = f(xx, yy, x0=1.0, freq=0.5)
    plt.imshow(v1 + v2, extent=[x_min, x_max, y_min, y_max])
    plt.grid(True)
    plt.show()


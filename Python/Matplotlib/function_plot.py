#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

eq = (r'$\frac{d^2 \theta}{dt^2} = - \frac{g}{l} \theta ' +
      r'- \mu \frac{d\theta}{dt}$')
x = np.linspace(0.0, 20.0, 500)
y = np.exp(-0.2*x)*np.cos(2.0*np.pi*x)
y_plus = np.exp(-0.2*x)
y_min = -np.exp(-0.2*x)

plt.plot(x, y)
plt.plot(x, y_plus, ':', alpha=0.7, color='red', linewidth=0.5)
plt.plot(x, y_min, ':', alpha=0.7, color='red', linewidth=0.5)
plt.xlabel(r'$t$', fontsize=14)
plt.ylabel(r'$\theta(t)$', fontsize=14)
plt.title('Damped pendulum')
plt.text(10.0, 0.65, eq, fontsize=18)
plt.show()
# plt.savefig('function.png')


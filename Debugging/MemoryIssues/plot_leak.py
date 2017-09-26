#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('leak.txt', skiprows=1)
print(data.shape)
plt.plot(data[:, 0], data[:, 1])
plt.xlabel('time (s)')
plt.ylabel('memory (kB)')
plt.show()

#!/usr/bin/env python

import numpy as np

nr_data = 100
gaussian = np.random.normal(loc=1.5, scale=2.0, size=nr_data)
poisson = np.random.poisson(lam=5.0, size=nr_data)
labels = np.random.choice(['A', 'B', 'C', 'D'], size=nr_data)
x = np.linspace(0.0, 100.0, nr_data)
y = 1.3*x + 2.0 + np.random.normal(scale=8, size=nr_data)
x1 = np.random.choice(np.arange(1, 10, 1), size=nr_data)
y1 = 1.3*x1 + 2.0 + np.random.normal(scale=1.5, size=nr_data)
x2 = np.sort(np.random.gamma(3, scale=4, size=nr_data))
y2 = 1.3*x2 + 2.0 + np.random.normal(scale=1.5, size=nr_data)
binary = np.random.choice(np.array(['yes', 'no']), size=nr_data)
x3 = x2.copy()
y3 = np.where(binary == 'yes', 1.3, 1.9)*x3 + \
     np.where(binary == 'yes', 2.0, -1.0) + \
     np.random.normal(size=nr_data)
with open('Data/data.txt', 'w') as file:
    print('gaussian,poisson,label,x,y,x1,y1,x2,y2,binary,x3,y3',file=file)
    for i in range(nr_data):
        print(f'{gaussian[i]},{poisson[i]},{labels[i]},{x[i]},{y[i]},'
              f'{x1[i]},{y1[i]},{x2[i]},{y2[i]},{binary[i]},'
              f'{x3[i]},{y3[i]}',
              file=file)

#!/usr/bin/env python

import numpy as np
from stats import Statistics, compute_stats

n = 10
data = np.empty(n)
my_stats = Statistics()
for i in range(n):
    value = 0.3*i
    my_stats.add(value)
    data[i] = value
print(my_stats.mean())
my_stats = compute_stats(data)
print(my_stats.mean())

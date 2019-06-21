#!/usr/bin/env python

from stats import Statistics

my_stats = Statistics()
for i in range(10):
    my_stats.add(0.3*i)
print(my_stats.n())

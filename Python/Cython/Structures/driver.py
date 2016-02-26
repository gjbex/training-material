#!/usr/bin/env python

import point

p = point.create(1.0, -2.0, 1)
print(p)
print('radius = {0}'.format(point.radius(p)))
point.project(p)
print(p)

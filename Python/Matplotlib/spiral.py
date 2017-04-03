#!/usr/bin/env python
# borrowed from John D. Cook, posted on
# https://www.johndcook.com/blog/2017/02/14/recreating-the-vertigo-poster/
# ------------------------------------------------------------------------

import matplotlib.pyplot as plt
from numpy import arange, sin, cos, exp

i  = arange(5000)
x1 = 1.0*cos(i/10.0)*exp(-i/2500.0)
y1 = 1.4*sin(i/10.0)*exp(-i/2500.0)
d  = 450.0
vx = cos(i/d)*x1 - sin(i/d)*y1
vy = sin(i/d)*x1 + cos(i/d)*y1

plt.plot(vx, vy, "k")

h = max(vy) - min(vy)
w = max(vx) - min(vx)
plt.axes().set_aspect(w/h)
plt.show()

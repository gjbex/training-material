cimport cython
from math import sin

def integrate(f, a, b, n=1000):
    dx = (b - a)/n
    total = 0.0
    for i in range(n):
        total += f(a + i*dx)
    return total*dx

@cython.profile(True)
def sin2(x):
    return sin(x)**2

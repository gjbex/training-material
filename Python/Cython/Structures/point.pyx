import math

cdef struct Point:
    double x, y
    int id

def create(double x, double y, int id):
    cdef Point point
    point.x = x
    point.y = y
    point.id = id
    return point

def radius(Point point):
    return math.sqrt(point.x**2 + point.y**2)

def azimuth(Point point):
    return math.atan2(point.y, point.x)

def project(Point point):
    cdef double r = radius(point)
    point.x /= r
    point.y /= r
    print(point)

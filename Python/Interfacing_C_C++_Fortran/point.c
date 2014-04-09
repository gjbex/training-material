#include <math.h>

#include "point.h"

Point create_point(double x, double y) {
    Point p = {x, y};
    return p;
}

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}


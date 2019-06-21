#include <math.h>

#include "point_class.h"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

double Point::distance(Point q) {
    return sqrt((this->x - q.x)*(this->x - q.x) +
                (this->y - q.y)*(this->y - q.y));
}


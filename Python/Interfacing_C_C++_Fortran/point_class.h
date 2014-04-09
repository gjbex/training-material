#ifndef POINT_CLASS_HDR
#define POINT_CLASS_HDR

class Point {
    double x, y;

public:
    Point(double x, double y);
    double distance(Point q);
};

#endif


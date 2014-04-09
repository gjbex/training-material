#ifndef POINT_HDR
#define POINT_HDR

typedef struct {
    double x, y;
} Point;

Point create_point(double x, double y);
double distance(Point p1, Point p2);

#endif


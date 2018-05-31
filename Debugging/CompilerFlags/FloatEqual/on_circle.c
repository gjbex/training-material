#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point center;
    double radius;
} Circle;

int is_on_circle(Point *p, Circle *c);

int main(int argc, char* argv[]) {
    Circle c;
    Point p;
    if (argc != 6)
        errx(1, "expecting center_x center_y radius p_x p_y");
    c.center.x = atof(argv[1]);
    c.center.y = atof(argv[2]);
    c.radius = atof(argv[3]);
    p.x = atof(argv[4]);
    p.y = atof(argv[5]);
    if (is_on_circle(&p, &c))
        printf("points on circle\n");
    else
        printf("points not on circle\n");
    return 0;
}

#define SQR(x) ((x)*(x))

double distance(Point *p, Point *q) {
    return sqrt(SQR(p->x - q->x) + SQR(p->y - q->y));
}

int is_on_circle(Point *p, Circle *c) {
    return distance(p, &(c->center)) == c->radius;
}

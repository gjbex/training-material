#include <stdio.h>
#include <stdlib.h>

#include "point.h"

int main(int argc, char *argv[]) {
    Point p1 = {3.0, 4.0}, p2 = {-1.0, 5.0};
    double d = distance(p1, p2);
    printf("(%.1lf,%.1lf) <-> (%.1lf,%.1lf) = %.5lf\n",
           p1.x, p1.y, p2.x, p2.y, d);
    return EXIT_SUCCESS;
}


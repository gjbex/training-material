#include <err.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int charge;
    double x, y;
    int count;
} Point;

int main(int argc, char *argv[]) {
    if (argc != 4)
        errx(EXIT_FAILURE, "expected 2 reals and 1 int");
    Point p = {
        .x = atof(argv[1]),
        .y = atof(argv[2]),
        .charge = atoi(argv[3])
    };
    printf("(%.2f, %.2f): %d, %d\n", p.x, p.y, p.charge, p.count);
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

#include "logistic_map.h"

int main(int argc, char *argv[]) {
    double x0 = 0.5, r = 3.2, x;
    if (argc > 1) {
        x0 = atof(argv[1]);
    }
    if (argc > 2) {
        r = atof(argv[2]);
    }
    x = log_map(x0, r, 1000);
    printf("lm(%lf, %lf) = %lf\n", x0, r, x);
    return EXIT_SUCCESS;
}


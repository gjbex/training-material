#include <stdio.h>
#include <stdlib.h>

#include "stats.h"

int main(int argc, char *argv[]) {
    const int n = 5;
    double data[] = {1.0, 2.5, 2.0, 3.0, 3.5};
    Stats s = stats(data, n);
    printf("mean = %lf, stddev = %lf, n = %d\n", s.mean, s.stddev, s.n);
    return EXIT_SUCCESS;
}


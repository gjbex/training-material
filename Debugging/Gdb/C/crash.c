#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double *a = (double *) calloc(10, sizeof(double));
    free(a);
    free(a);
    return EXIT_SUCCESS;
}


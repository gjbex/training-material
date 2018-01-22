#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const long n = 100000000000;
    long i;
    double *x = (double *) malloc(n*sizeof(double));
    double sum = 0.0;
    for (i = 0; i < n; i++)
        x[i] = sqrt(i);
    for (i = 0; i < n; i++)
        sum += x[i];
    printf("sum = %le\n", sum);
    free(x);
    return EXIT_SUCCESS;
}

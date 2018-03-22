#include <stdio.h>
#include <stdlib.h>

double *init_vector(int n);

int main() {
    const int n = 5;
    double *x;
    double sum = 0.0;
    int i;
    x = init_vector(n);
    for (i = 0; i < n; i++)
        sum += x[i];
    printf("sum = %lf\n", sum);
    return EXIT_SUCCESS;
}

double *init_vector(int n) {
    double x[n];
    int i;
    for (i = 0; i < n; i++)
        x[i] = rand()/RAND_MAX;
    return x;
}

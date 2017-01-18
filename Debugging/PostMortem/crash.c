#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void init_array(double *a, int n, int nr_iters);
double compute(int i);

int main(int argc, char *argv[]) {
    const int n = 10;
    int nr_iters = 100000;
    double a[n];
    init_array(a, n, nr_iters);
    for (int i = 0; i < n; i++)
        printf("%d: %.4lf\n", i, a[i]);
    return EXIT_SUCCESS;
}

void init_array(double *a, int n, int nr_iters) {
    for (int iter_nr = 0; iter_nr < nr_iters; iter_nr++)
        a[iter_nr/n] += compute(iter_nr);
}

double compute(int i) {
    return log((double) i);
}

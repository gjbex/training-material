#include <err.h>
#include <stdio.h>
#include <stdlib.h>

double *create_vector(int n);
double compute_avg(double *x, int n);

int main() {
    const int n = 100000;
    const int nr_iters = 200000;
    double sum = 0.0;
    int i;
    for (i = 0; i < nr_iters; i++) {
        double *x = create_vector(n);
        sum += compute_avg(x, n);
    }
    printf("sum = %le\n", sum);
    return EXIT_SUCCESS;
}

double *create_vector(int n) {
    double *x;
    int i;
    if ((x = (double *) malloc(n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate array");
    for (i = 0; i < n; i++)
        x[i] = ((double) rand())/RAND_MAX;
    return x;
}

double compute_avg(double *x, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++)
        sum += x[i];
    return sum/n;
}

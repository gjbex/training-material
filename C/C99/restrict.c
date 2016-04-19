#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

double *v_alloc(int n);
void v_init(double *x, int n, bool invert);
void daxpy_r(double * restrict z, double a, double *x, double *y, int n);
void daxpy(double *z, double a, double *x, double *y, int n);
double v_norm(double *x, int n);

int main(int argc, char *argv[]) {
    int n = 10;
    bool is_restricted = true;
    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        is_restricted = (strcmp(argv[2], "restrict") == 0);
    double *z = v_alloc(n), *x = v_alloc(n), *y = v_alloc(n);
    v_init(x, n, false);
    v_init(y, n, true);
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    if (is_restricted)
        daxpy_r(z, 2.0, x, y, n);
    else
        daxpy(z, 2.0, x, y, n);
    gettimeofday(&end_time, NULL);
    printf("daxpy%s time for n = %d: %ld.%06ld (s)\n",
           is_restricted ? "_r" : "",  n,
           end_time.tv_sec - start_time.tv_sec,
           end_time.tv_usec - start_time.tv_usec);
    printf("result = %le\n", v_norm(z, n));
    free(x);
    free(y);
    free(z);
    return EXIT_SUCCESS;
}

double *v_alloc(int n) {
    double *v = (double *) malloc(n*sizeof(double));
    if (v == NULL)
        errx(EXIT_FAILURE, "can not allocate %d-vector", n);
    return v;
}

void v_init(double *x, int n, bool invert) {
    if (invert)
        for (int i = 0; i < n; i++)
            x[i] = 1.0/(1.0 + i);
    else
        for (int i = 0; i < n; i++)
            x[i] = 1.0 + i;
}

void daxpy_r(double * restrict z, double a, double *x, double *y, int n) {
    for (int i = 0; i < n; i++)
        z[i] = a*x[i] + y[i];
}

void daxpy(double *z, double a, double *x, double *y, int n) {
    for (int i = 0; i < n; i++)
        z[i] = a*x[i] + y[i];
}

double v_norm(double *x, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += x[i]*x[i];
    return sum;
}

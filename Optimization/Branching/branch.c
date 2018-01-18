#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double *init(int n) {
    int i;
    double *a = (double *) malloc(n*sizeof(double));
    if (a == NULL)
        errx(EXIT_FAILURE, "### error: can allocate %d double array", n);
    for (i = 0; i < n; i++)
        a[i] = ((double) rand())/RAND_MAX;
    return a;
}

double *init_cont(int n, int count) {
    int i;
    double *a = (double *) malloc(n*sizeof(double));
    if (a == NULL)
        errx(EXIT_FAILURE, "### error: can allocate %d double array", n);
    for (i = 0; i < count; i++)
        a[i] = 0.1;
    for (i = count; i < n; i++)
        a[i] = 0.9;
    return a;
}

long count_if(double *x, int n, int k) {
    long total = 0;
    int i, j;
    for (j = 0; j < k; j++)
        for (i = 0; i < n; i++)
            if (x[i] < 0.5)
                total++;
    return total;
}

long count_cond_expr(double *x, int n, int k) {
    long total = 0;
    int i, j;
    for (j = 0; j < k; j++)
        for (i = 0; i < n; i++)
            total += x[i] < 0.5 ? 1 : 0;
    return total;
}

int main(int argc, char *argv[]) {
    int n = 100;
    int k = 100;
    double *x;
    struct timeval tv1, tv2;
    long counter;
    if (argc > 1)
        n = atoi(argv[1]);
    if (argc > 2)
        k = atoi(argv[2]);
    x = init(n);
    gettimeofday(&tv1, NULL);
    counter = count_if(x, n, k);
    gettimeofday(&tv2, NULL);
    printf("if condition:         %.6lf (%ld)\n",
            tv2.tv_sec - tv1.tv_sec + 1.0e-6*(tv2.tv_usec - tv1.tv_usec),
            counter);
    gettimeofday(&tv1, NULL);
    counter = count_cond_expr(x, n, k);
    gettimeofday(&tv2, NULL);
    printf("condition expression: %.6lf (%ld)\n",
            tv2.tv_sec - tv1.tv_sec + 1.0e-6*(tv2.tv_usec - tv1.tv_usec),
            counter);
    free(x);
    x = init_cont(n, counter/k);
    gettimeofday(&tv1, NULL);
    counter = count_if(x, n, k);
    gettimeofday(&tv2, NULL);
    printf("if condition:         %.6lf (%ld)\n",
            tv2.tv_sec - tv1.tv_sec + 1.0e-6*(tv2.tv_usec - tv1.tv_usec),
            counter);
    gettimeofday(&tv1, NULL);
    counter = count_cond_expr(x, n, k);
    gettimeofday(&tv2, NULL);
    printf("condition expression: %.6lf (%ld)\n",
            tv2.tv_sec - tv1.tv_sec + 1.0e-6*(tv2.tv_usec - tv1.tv_usec),
            counter);
    free(x);
    return EXIT_SUCCESS;
} 

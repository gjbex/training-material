#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "memdump.h"

double compute_sum(double b[], int n) {
    int i;
    double f_sum = 0.0;
    DUMP(f_sum);
    for (i = 0; i < n; i++)
        f_sum += b[i];
    return f_sum;
}

int *init_array(int n) {
    return (int *) malloc(n*sizeof(int));
}

int main() {
    const int n = 16;
    double b[n], avg = 0.0;
    double *c = (double *) malloc(sizeof(double));
    int a[n], sum = 0;
    int *d = init_array(n);
    int *e = init_array(n);
    int i;
    for (i = 0; i < n; i++)
        b[i] = (double) i;
    for (i = n; i >= 0; i--) {
        a[i] = i*i*i;
        avg += b[i];
    }
    for (i = 0; i < n; i++)
        sum += a[i];
    DUMP(n);
    DUMP(i);
    DUMP(sum);
    DUMP(avg);
    DUMP_ARRAY(a, n);
    DUMP_ARRAY(b, n);
    DUMP_PTR(c);
    DUMP_PTR_ARRAY(d, n);
    DUMP_PTR_ARRAY(e, n);
    printf("sum = %d\n", sum);
    printf("avg = %lf\n", avg/n);
    printf("f_sum = %lf\n", compute_sum(b, n));
    return 0;
}

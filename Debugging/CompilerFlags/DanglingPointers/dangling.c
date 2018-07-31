#include <stdio.h>
#include <stdlib.h>

int main() {
    const int n = 5;
    double *a, *b;
    a = (double *) malloc(n*sizeof(double));
    b = a;
    for (int i = 0; i < n; i++)
        a[i] = 1.0 + i;
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    printf("sum = %lf\n", sum);
    free(a);
    sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += b[i]*b[i];
    printf("sum2 = %lf\n", sum);
    free(b);
    return 0;
}

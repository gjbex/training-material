#include <err.h>
#include <stdio.h>
#include <stdlib.h>

static double __arg__;
#define SQR(a) ((__arg__ = (a)) == 0.0 ? 0.0 : __arg__*__arg__)

int main(int argc, char *argv[]) {
    double *a, *b, *c, sum;
    int n = 1000000, i;
    if ((a = (double *) malloc(n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate a[%d]", n);
    if ((b = (double *) malloc(n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate b[%d]", n);
    if ((c = (double *) malloc(n*sizeof(double))) == NULL)
        errx(EXIT_FAILURE, "can't allocate c[%d]", n);
    sum = 0.0;
    for (i = 0; i < n; i++) {
        b[i] = (rand() % 2) ? 0.01*i : 0.0;
        c[i] = (rand() % 2) ? 0.03*i : 0.0;
        sum += b[i]*b[i] + c[i]*c[i];
    }
    printf("sum = %.2lf\n", sum);
    for (i = 0; i < n; i++)
        a[i] = SQR(b[i]) + SQR(c[i]);
    sum = 0.0;
    for (i = 0; i < n; i++)
        sum += a[i];
    printf("sum = %.2lf\n", sum);
    free(a);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}

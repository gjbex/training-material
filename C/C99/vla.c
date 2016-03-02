#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sqr(double a[], int n);

int main(int argc, char *argv[]) {
    int n = 10;
    if (argc > 1)
        n = atoi(argv[1]);
    double data[n];
    for (int i = 0; i < n; i++)
        data[i] = (double) i;
    for (int i = 0; i < n; i++)
        printf("sqrt(%lf) = %lf\n", data[i], sqrt(data[i]));
    sqr(data, n);
    for (int i = 0; i < n; i++)
        printf("%d: %lf\n", i, data[i]);
    return EXIT_SUCCESS;
}

void sqr(double a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = a[i]*a[i];
}

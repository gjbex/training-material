#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double x = 1.454094e06;
    int n = (int) round(x);
    printf("%.5le -> %d\n", x, n);
    x = 1.454094e10;
    n = (int) round(x);
    printf("%.5le -> %d\n", x, n);
    return EXIT_SUCCESS;
}

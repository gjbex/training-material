#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double x = 1.454094e06;
    long n = lround(x);
    if (fetestexcept(FE_INVALID)) {
        fprintf(stderr, "Floating point exception caught\n");
         feclearexcept(FE_ALL_EXCEPT);
    }
    printf("%.5le -> %ld\n", x, n);
    x = 1.454094e100;
    n = lround(x);
    if (fetestexcept(FE_INVALID)) {
        fprintf(stderr, "Floating point exception caught\n");
        feclearexcept(FE_ALL_EXCEPT);
    }
    printf("%.5le -> %ld\n", x, n);
    return EXIT_SUCCESS;
}

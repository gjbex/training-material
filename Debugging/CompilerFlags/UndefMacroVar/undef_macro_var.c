#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char fmt[80];
#if PREC == 32
    float x = 2.0f;
    strcpy(fmt, "sqrt(%.7f) = %.7f\n");
#else
    double x = 2.0;
    strcpy(fmt, "sqrt(%.15lf) = %.15lf\n");
#endif
    printf(fmt, x, sqrt(x));
    return EXIT_SUCCESS;
}

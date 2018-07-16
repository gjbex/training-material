#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char fmt[80] = "This is nonsense\n";
    float x = 0.0f;
    {
#if PREC == 32
        float x = 2.0f;
        strcpy(fmt, "sqrt(%.7f) = %.7f\n");
        printf("single precision\n");
#elif PREC == 64
        double x = 2.0;
        strcpy(fmt, "sqrt(%.15lf) = %.15lf\n");
        printf("double precision\n");
#endif
        printf(fmt, x, sqrt(x));
    }
    return EXIT_SUCCESS;
}

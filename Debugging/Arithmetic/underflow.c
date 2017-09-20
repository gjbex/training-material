#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    float x[] = {
        1.0e-31f,
        1.0e-31f,
        5.0f,
        1.0e31f,
        1.0e31f
    };
    int i;
    float prod = 1.0f;
    float log_prod = 0.0f;
    double dprod = 1.0;
    for (i = 0; i < 5; i++) {
        prod *= x[i];
        dprod *= x[i];
        log_prod += log(x[i]);
    }
    printf("float product = %e\n", prod);
    printf("double product = %le\n", dprod);
    printf("log float product = %e\n", exp(log_prod));
    prod = 1.0f;
    for (i = 4; i >= 0; i--)
        prod *= x[i];
    printf("float product (reverse) = %e\n", prod);
    return EXIT_SUCCESS;
}

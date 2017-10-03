#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("exp(1.0e10) = %le\n", exp(1.0e10));
    printf("pow(-1.0e10, 51.0) = %le\n", pow(-1.0e10, 51.0));
    printf("sqrt(-1.0) = %le\n", sqrt(-1.0));
    printf("1.0/0.0 = %le\n", 1.0/0.0);
    printf("-1.0/0.0 = %le\n", -1.0/0.0);
    printf("0.0/0.0 = %le\n", 0.0/0.0);
    return EXIT_SUCCESS;
}

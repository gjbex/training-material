#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    double result = 1.0*(0.5 - 0.4 - 0.1);
    printf("1.0*(0.5 - 0.4 - 0.1) = %le\n", result);
    if (result == 0.0)
        printf("1.0*(0.5 - 0.4 - 0.1) == 0.0\n");
    else
        printf("1.0*(0.5 - 0.4 - 0.1) != 0.0\n");
    return EXIT_SUCCESS;
}

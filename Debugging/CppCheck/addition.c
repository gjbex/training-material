#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long n = 1000000, i;
    double result1 = 1.0, result2 = 0.0, number;
    if (argc > 1)
        n = atol(argv[1]);
    for (i = 0; i < n; i++) {
        number = (1.0e-17*rand())/RAND_MAX;
        result1 += number;
        result2 += number;
    }
    result2 += 1.0;
    printf("1 + sum(x) = %.15le\n", result1);
    printf("sum(x) + 1 = %.15le\n", result2);
    printf("relative error = %.3le\n", (result2 - result1)/result1);
    return EXIT_SUCCESS;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    double sum = 0.0;
    double a[11];
    int i = 12;
    do {
        a[--i] = sqrt(i);
    } while (i >= 0);
    for (i = 0; i < 11; i++) {
        sum += a[i];
    }
    printf("sum = %lf\n", sum);
    return EXIT_SUCCESS;
}

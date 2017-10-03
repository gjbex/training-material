#include <stdio.h>
#include <stdlib.h>

int main() {
    const int n = 10;
    int i;
    float incr = 5.0e37;
    float sum = 0.0;
    for (i = 0; i < n; i++) {
        sum += incr;
        printf("sum = %e\n", sum);
    }
    return EXIT_SUCCESS;
}


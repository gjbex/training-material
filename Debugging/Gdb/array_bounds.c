#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "show.h"

int main(int argc, char *argv[]) {
    double sum = 0.0, a[11];
    int i = 12;
    do {
        a[--i] = sqrt(i);
    } while (i >= 0);
    for (i = 0; i < 11; i++)
        sum += a[i];
    printResult("sum     ", sum);
    printResult("expected", 22.468278);
    return EXIT_SUCCESS;
}

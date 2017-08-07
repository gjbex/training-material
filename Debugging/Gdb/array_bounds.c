#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "show.h"

int main(int argc, char *argv[]) {
    double sum, a[11];
    int i;
    for (i = 0; i <= 11; i++)
        a[i] = sqrt(i);
    i = 11;
    do {
        sum += a[--i];
    } while (i >= 0);
    printResult("sum     ", sum);
    printResult("expected", 22.468278);
    return EXIT_SUCCESS;
}

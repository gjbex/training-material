#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"

int main(int argc, char *argv[]) {
    int i;
    int max_n = 5;
    if (argc > 1)
        max_n = atoi(argv[1]);
    for (i = 0; i <= max_n; i++)
        printf("fac(%d) = %d\n", i, fac(i));
    return EXIT_SUCCESS;
}

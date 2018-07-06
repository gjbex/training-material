#include <stdio.h>
#include <stdlib.h>

#include "fib.h"

int main(int argc, char *argv[]) {
    long n = atol(argv[1]);
    printf("fib(%ld) = %ld\n", n, fib(n));
    return EXIT_SUCCESS;
}

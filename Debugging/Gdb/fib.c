#include <stdio.h>
#include <stdlib.h>

long fib(long n) {
    if (n < 2)
        return 1;
    else {
        long a = fib(n-1);
        long b = fib(n-2);
        return a + b;
    }
}

int main(int argc, char *argv[]) {
    long n = atol(argv[1]);
    printf("fib(%ld) = %ld\n", n, fib(n));
    return EXIT_SUCCESS;
}


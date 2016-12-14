#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int fib(int n);

int main(int argc, char *argv[]) {
    int i, sum = 0, n, max;
    if (argc != 3)
        errx(EXIT_FAILURE, "expecting n and max");
    n = atoi(argv[1]);
    max = atoi(argv[2]);
    for (i = 0; i < n; i++) {
#pragma omp parallel
#pragma omp single
        {
            int x, result;
            x = rand() % max;
            printf("%d: fib(%d) = ", i, x);
            result = fib(x);
            printf("%d\n", result);
        }
    }
    return EXIT_SUCCESS;
}

int fib(int n) {
    int result;
    if (n <= 1) {
        result = 1;
    } else {
        int f1, f2;
        if (n > 10) {
#pragma omp task shared(f1)
            f1 = fib(n-1);
            f2 = fib(n-2);
#pragma omp taskwait
            result = f1 + f2;
        } else {
            f1 = fib(n-1);
            f2 = fib(n-2);
            result = f1 + f2;
        }
    }
    return result;
}


#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1)
        errx(EXIT_FAILURE, "expected positive integer number");
    int n = atof(argv[1]);
    bool is_prime;
    if (n < 2)
        is_prime = false;
    else
        is_prime = true;
    int i = 2;
    while (i < n && is_prime)
        if (n % i++ == 0)
            is_prime = false;
    printf("%sprime\n", is_prime ? "" : "not ");
    return EXIT_SUCCESS;
}

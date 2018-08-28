#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define ARG_ERR 1

int fac(int n);

int main(int argc, char *argv[]) {
    if (argc == 1)
        errx(ARG_ERR, "no argument given");
    int n;
    char *end_ptr = argv[1];
    n = (int) strtol(argv[1], &end_ptr, 10);
    if (*end_ptr != '\0')
        errx(ARG_ERR, "'%s' can not be converted in int", argv[1]);
    printf("fac(%d) = %d\n", n, fac(n));
    return 0;
}

int fac(int n) {
    assert(n >= 0);
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        assert(result > 1);
    }
    return result;
}

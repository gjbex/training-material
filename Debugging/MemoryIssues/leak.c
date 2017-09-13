#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *a, i, n = 5;
    if (argc > 1)
        n = atoi(argv[1]);
    if (!(a = (int *) malloc(n*sizeof(int))))
        errx(EXIT_FAILURE, "### error: can't allocate %d int array", n);
    for (i = 0; i < n; i++)
        a[i] = i;
    for (i = 0; i < n; i++)
        a[i] *= i;
    for (i = 0; i < n; i++)
        printf("%d: %d\n", i, a[i]);
    return EXIT_SUCCESS;
}

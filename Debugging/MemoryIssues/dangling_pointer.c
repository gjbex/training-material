#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1, *p2;
    if (!(p1 = (int *) malloc(sizeof(int))))
        errx(EXIT_FAILURE, "can't allocate int");
    *p1 = 15;
    p2 = p1;
    free(p1);
    *p2 = 17;
    printf("%p -> %d\n", p2, *p2);
    return EXIT_SUCCESS;
}

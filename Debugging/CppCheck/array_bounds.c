#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char *argv[] __attribute__((unused))) {
    const int old_val = 15;
    const int new_val = 42;
    int i, b, a[N];
    long shift = &b - &(a[0]);
    b = old_val;
    if (argc > 1) {
        printf("b:    %p\n", &b);
        printf("a[0]: %p\n", &(a[0]));
        if (&b < &(a[0])) {
            printf("b <- a[0]: %ld\n", &(a[0]) - &b);
        } else {
            printf("a[N-1] -> b: %ld\n", &b - &(a[N-1]));
        }
        if (&i == &(a[N])) {
            printf("overlap\n");
        } else {
            printf("no overlap\n");
        }
    }
    printf("b = %d\n", b);
    for (i = 0; i < N; i++)
        a[i] = i;
    a[shift] = new_val;
    printf("setting a[%ld] = %d\n", shift, new_val);
    printf("a[%ld] = %d\n", shift, a[shift]);
    printf("b = %d\n", b);
    return EXIT_SUCCESS;
}

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

int main() {
    int i, a[N];
    for (i = 0; i < N; i++)
        a[i] = i;
    for (i = N - 1; i >= 0; i--) {
        a[i-1] += 101;
        printf("%d: %d\n", i, a[i]);
    }
    printf("i = %d\n", i);
    return EXIT_SUCCESS;
}

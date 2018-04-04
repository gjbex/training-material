#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = (int *) malloc(5*sizeof(int));
    int n = 5;
    int m;
    if (m > n) {
        printf("in if-statement\n");
        for (int i = 0; i <= 5; ++i)
            a[i] = i;
    }
    printf("a[5] = %d\n", a[n]);
    return 0;
}

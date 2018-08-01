#include <stdio.h>
#include <stdlib.h>

int main() {
    const int n = 5;
    int a[] = {1, 2, 3, 4, 5, 6};
    double *b = (double *) malloc(n*sizeof(double));
    for (int i = 0; i <= n; i++)
        b[i] = a[i] - 1.0;
    for (int i = 0; i < n; i++)
        printf("%lf\n", b[i]);
    free(b);
    return 0;
}

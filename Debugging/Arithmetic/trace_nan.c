#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4

int main() {
    double a[N] = { 1.0, 3.0, -3.0, 5.3  };
    double b[N];
    int i;
#ifdef FPE_TRAP
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
#endif
    for (i = 0; i < N; i++)
        b[i] = sqrt(a[i]);
    for (i = 0; i < N; i++)
        printf("%10.3f%10.3f\n", a[i], b[i]);
    return EXIT_SUCCESS;
}

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void print_complex(double complex z);

int main(int argc, char *argv[]) {
    double complex z = 1.0 + 2.0*I;
    printf("z = "); print_complex(z); printf("\n");
    double complex z_c = conj(z);
    printf("z' = "); print_complex(z_c); printf("\n");
    double complex z_sqrt = csqrt(z);
    printf("sqrt(z) = "); print_complex(z_sqrt); printf("\n");
    double complex z_sqr = z_sqrt*z_sqrt;
    printf("sqrt(z)^2 = "); print_complex(z_sqr); printf("\n");
    return EXIT_SUCCESS;
}

void print_complex(double complex z) {
    printf("%lf %c %lfi", creal(z), cimag(z) < 0.0 ? '-' : '+',
           fabs(cimag(z)));

}

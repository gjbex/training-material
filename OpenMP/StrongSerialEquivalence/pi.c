#include <err.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int n = 1000;
    double x, dx = 1.0/n, pi = 0.0;
    int i;
    FILE *fp;
    if (argc < 2)
        errx(EXIT_FAILURE, "no file name specified");
#pragma omp parallel for reduction(+:pi), default(none), \
                         shared(dx), private(x)
    for (i = 0; i < n; i++) {
        x = i*dx;
        pi += 4.0/(1.0 + x*x);
    }
    printf("%.15f\n", pi*dx);
    if ((fp = fopen(argv[1], "wb")) == NULL)
        err(EXIT_FAILURE, "can not open file");
    fwrite(&pi, sizeof(double), 1, fp);
    fclose(fp);
    return 0;
}

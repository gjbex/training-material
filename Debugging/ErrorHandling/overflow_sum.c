#include <err.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sum(int n);

int main(int argc, char *argv[]) {
    int status;
    int n = 10;
    if (argc == 2)
        n = atoi(argv[1]);
    double result = sum(n);
    if ((status = fetestexcept(FE_INVALID | FE_OVERFLOW))) {
        if (status & FE_INVALID)
            warnx("invalid operation detected");
        else if (status & FE_OVERFLOW)
            warnx("overflow detected");
    }
    printf("sum = %le\n", result);
    return 0;
}

double sum(int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++)
        result += pow(10.0, i);
    return result;
}

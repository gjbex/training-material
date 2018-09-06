#include <err.h>
#include <math.h>
#include <stdio.h>

double product();

int main() {
    double result;

    result = 1.0/0.0;
    printf("1.0/0.0 = %lf (%d)\n", result, isnormal(result));

    result = 1.0*log(0.0);
    printf("1.0*log(0.0) = %lf (%d)\n", result, isnormal(result));

    result = 1.0e-300*1.0e-300;
    printf("1.0e-300*1.0e-300 = %lf (%d)\n", result, isnormal(result));

    result = 1.0e-200/1.0e200;
    printf("1.0e-300/1.0e300 = %lf (%d)\n", result, isnormal(result));

    result = exp(-700.0);
    printf("exp(-700.0) = %lf (%d)\n", result, isnormal(result));

    result = 1.0e200*1.0e200;
    printf("1.0e200*1.0e200 = %lf (%d)\n", result, isnormal(result));

    result = product();
    printf("product = %le (%d)\n", result, isnormal(result));

    result = exp(7000.0);
    printf("exp(7000.0) = %lf (%d)\n", result, isnormal(result));

    result = sqrt(-1.0);
    printf("sqrt(-1.0) = %lf (%d)\n", result, isnormal(result));

    result = log(-1.0);
    printf("log(-1.0) = %lf (%d)\n", result, isnormal(result));

    result = 2.0/3.0;
    printf("2.0/3.0 = %lf (%d)\n", result, isnormal(result));

    return 0;
}

double product() {
    double x[] = {1.0e-300, 1.0e-300, 5.0, 1.0e300, 1.0e300};
    double result = 1.0;
    for (int i = 0; i < 5; i++) {
        result *= x[i];
        printf("\tresult = %le (%d)\n", result, isnormal(result));
    }
    return result;
}


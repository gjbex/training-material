#include <err.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>

void report_ieee_exception();
double product();

int main() {
    double result;

    printf("1.0/0.0 = \n");
    result = 1.0/0.0;
    report_ieee_exception();
    printf("1.0/0.0 = %lf\n", result);

    printf("1.0*log(0.0) = \n");
    result = 1.0*log(0.0);
    report_ieee_exception();
    printf("1.0*log(0.0) = %lf\n", result);

    printf("1.0e-300*1.0e-300 = \n");
    result = 1.0e-300*1.0e-300;
    report_ieee_exception();
    printf("1.0e-300*1.0e-300 = %lf\n", result);

    printf("1.0e-300/1.0e300 = \n");
    result = 1.0e-200/1.0e200;
    report_ieee_exception();
    printf("1.0e-300/1.0e300 = %lf\n", result);

    printf("exp(-700.0) = \n");
    result = exp(-700.0);
    report_ieee_exception();
    printf("exp(-700.0) = %lf\n", result);

    printf("1.0e200*1.0e200 = \n");
    result = 1.0e200*1.0e200;
    report_ieee_exception();
    printf("1.0e200*1.0e200 = %lf\n", result);

    printf("product = \n");
    result = product();
    report_ieee_exception();
    printf("product = %le\n", result);

    printf("exp(7000.0) = \n");
    result = exp(7000.0);
    report_ieee_exception();
    printf("exp(7000.0) = %lf\n", result);

    printf("sqrt(-1.0) = \n");
    result = sqrt(-1.0);
    report_ieee_exception();
    printf("sqrt(-1.0) = %lf\n", result);

    printf("log(-1.0) = \n");
    result = log(-1.0);
    report_ieee_exception();
    printf("log(-1.0) = %lf\n", result);

    printf("2.0/3.0 = \n");
    result = 2.0/3.0;
    report_ieee_exception();
    printf("2.0/3.0 = %lf\n", result);

    printf("collecting exceptions?\n");
    printf("\texp(7000.0) = %lf\n", exp(7000.0));
    printf("\tlog(-1.0) = %lf\n", log(-1.0));
    printf("\t1.0/0.0 = %lf\n", 1.0/0.0);
    report_ieee_exception();

    return 0;
}

void report_ieee_exception() {
    int exception = fetestexcept(FE_ALL_EXCEPT);
    if (exception & FE_INEXACT)
        warnx("IEEE floating point exception inexact");
    if (exception & FE_DIVBYZERO)
        warnx("IEEE floating point exception divide-by-zero");
    if (exception & FE_UNDERFLOW)
        warnx("IEEE floating point exception underflow");
    if (exception & FE_OVERFLOW)
        warnx("IEEE floating point exception overflow");
    if (exception & FE_INVALID)
        warnx("IEEE floating point exception invalid");
    feclearexcept(FE_ALL_EXCEPT);
}

double product() {
    double x[] = {1.0e-300, 1.0e-300, 5.0, 1.0e300, 1.0e300};
    double result = 1.0;
    for (int i = 0; i < 5; i++) {
        result *= x[i];
        printf("\tresult = %le\n", result);
        report_ieee_exception();
    }
    return result;
}


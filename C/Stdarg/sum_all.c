#include <stdarg.h>
#include <stdio.h>

double sum(double value, int n, ...) {
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++)
        value += va_arg(args, double);
    va_end(args);
    return value;
}

int main() {
    printf("sum = %lf\n", sum(0.0, 3, 1.2, 2.3, 3.4));
    printf("sum = %lf\n", sum(10.0, 2, 1.2, 2.3));
    return 0;
}

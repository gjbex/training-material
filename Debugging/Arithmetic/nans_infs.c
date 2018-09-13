#include <math.h>
#include <stdio.h>

int main() {
    printf("0.0/0.0 = %lf\n", 0.0/0.0);
    printf("1.0/0.0 = %lf\n", 1.0/0.0);
    printf("3.0*log(0.0) = %lf\n", 3.0*log(0.0));
    printf("sqrt(-1.0) = %lf\n", sqrt(-1.0));
    printf("log(-1.0) = %lf\n", log(-1.0));
    return 0;
}

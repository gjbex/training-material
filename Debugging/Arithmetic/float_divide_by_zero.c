#include <stdio.h>

int main() {
    double x[] = {-2.0, -1.0, 0.0, 1.0, 2.0};
    double y = 10.0;
    for (int i = 0; i < 5; i++)
        printf("%lf/%lf = %lf\n", y, x[i], y/x[i]);
    return 0;
}

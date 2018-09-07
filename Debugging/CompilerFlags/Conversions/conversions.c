#include <stdio.h>

int main() {
    long a = 94850485030;
    long b = 495849853000;
    int c = a + b;
    printf("c = %d\n", c);
    double x = 1.435e67;
    double y = 4.394e89;
    float z = x + y;
    printf("z = %e\n", z);
    int d = x;
    printf("d = %d\n", d);
    return 0;
}

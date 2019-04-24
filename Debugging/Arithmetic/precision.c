#include <stdio.h>

int main(int argc, char *argv[]) {
    float sum = 0.0f;
    const float value = 132.00005f;
    const int n = 1000000;
    for (int i = 0; i < n; i++)
        sum += value;
    printf("%.6f vs. %.6f\n", value, sum/n);
    return 0;
}

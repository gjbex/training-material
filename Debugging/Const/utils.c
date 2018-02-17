#include "utils.h"

void print_array(const char* prefix, const double *v, int n) {
    int i;
    printf("%s", prefix);
    if (n > 0)
        printf("%.2f", v[0]);
    for (i = 1; i < n; i++)
        printf(" %.2f", v[i]);
    printf("\n");
}

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("int\n"
           "  range = %d .. %d\n"
           "  bytes = %ld\n",
           INT_MIN, INT_MAX, sizeof(int));
    printf("long\n"
           "  range = %ld .. %ld\n"
           "  bytes = %ld\n",
           LONG_MIN, LONG_MAX, sizeof(long));
    printf("float\n"
           "  range = %e .. %e\n"
           "  digits = %d\n"
           "  epsilon = %e\n"
           "  min. pos. = %e\n"
           "  bytes = %ld\n",
           FLT_MIN, FLT_MAX, FLT_DIG, FLT_EPSILON, FLT_TRUE_MIN,
           sizeof(float));
    printf("double\n"
           "  range = %e .. %e\n"
           "  digits = %d\n"
           "  epsilon = %e\n"
           "  min. pos. = %e\n"
           "  bytes = %ld\n",
           DBL_MIN, DBL_MAX, DBL_DIG, DBL_EPSILON, DBL_TRUE_MIN,
           sizeof(double));
    return EXIT_SUCCESS;
}

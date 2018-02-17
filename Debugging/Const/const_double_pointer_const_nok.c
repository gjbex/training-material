#include <err.h>
#include <stdlib.h>

#include "utils.h"

void make_new_array(const double * const v, int n);

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    const int n = 3;
    double v[] = {3.0, 5.0, 7.0};
    print_array("In main: ", v, n);
    make_new_array(v, n);
    print_array("In main: ", v, n);
    return 0;
}

void make_new_array(const double * const v, int n) {
    int i;
    if (!(v = (double *) malloc(n*sizeof(double))))
        errx(EXIT_FAILURE, "can not allocate memory");
    for (i = 0; i < n; i++)
        v[i] = 13.0;
    print_array("In function: ", v, n);
}

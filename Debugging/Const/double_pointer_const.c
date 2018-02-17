#include <err.h>
#include <stdlib.h>

#include "utils.h"

void modify_const_array(double * const v, int n);

int main(int argc __attribute__((unused)),
         char *argv[] __attribute__((unused))) {
    const int n = 3;
    double v[] = {3.0, 5.0, 7.0};
    print_array("In main: ", v, n);
    modify_const_array(v, n);
    print_array("In main: ", v, n);
    return 0;
}

void modify_const_array(double * const v, int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] *=  0.5;
}

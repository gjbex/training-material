#include "fac.h"

int fac(int n) {
    int f = 1;
    while (n > 1)
        f *= --n;
    return f;
}

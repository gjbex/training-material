#include "fac.h"

long fac(long n) {
    long f = 1;
    while (n > 1)
        f *= --n;
    return f;
}


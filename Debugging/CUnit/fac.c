#include "fac.h"

long fac(long n) {
    long f = 1;
    for ( ; n > 1; n--)
        f *= n;
    return f;
}


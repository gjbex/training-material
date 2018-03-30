#include <assert.h>
#include <stdio.h>

#include "fac.h"

int main() {
    assert(fac(0) == 1);
    assert(fac(1) == 1);
    assert(fac(2) == 2);
    assert(fac(3) == 6);
    assert(fac(5) == 120);
    return 0;
}

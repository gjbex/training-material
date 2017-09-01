#include <err.h>
#include "funcs.h"

int fac(int n) {
    if (n < 0) {
        errx(1, "### error: negative argument to fac");
    } else if (n == 0 || n == 1) {
        return 1;
    } else {
        return n*fac(n - 1);
    }
}

int fac2(int n) {
    int i;
    int result = 1;
    for (i = 2; i <= n; i++)
        result *= i;
    return result;
}

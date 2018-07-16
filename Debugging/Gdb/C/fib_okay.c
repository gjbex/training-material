#include "fib.h"

long fib(long n) {
    if (n < 2)
        return 1;
    else {
        long a = fib(n-1);
        long b = fib(n-2);
        return a + b;
    }
}

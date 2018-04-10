#include "fib.h"

long fib(long n) {
    long a = fib(n-1);
    long b = fib(n-2);
    return a + b;
}

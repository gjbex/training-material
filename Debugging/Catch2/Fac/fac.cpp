#include <stdexcept>

#include "fac.h"

long fac(long n) {
    if (n < 0)
        throw std::invalid_argument(std::string("argument msut be positive"));
    long result {1};
    for (long i = 2; i <= n; i++)
        result *= i;
    return result;
}

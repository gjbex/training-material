#include <limits>
#include <stdexcept>

#include "fac.h"

int fac(int n) {
    if (n < 0)
        throw std::domain_error {"argument must be positive"};
    int result {1};
    const int max_int {std::numeric_limits<int>::max()};
    for (int i = 2; i <= n; i++)
        if (result < max_int/i)
            result *= i;
        else
            throw std::overflow_error {"argument too large"};
    return result;
}

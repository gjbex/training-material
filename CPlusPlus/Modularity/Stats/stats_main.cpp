#include <iostream>

#include "stats.h"

int main() {
    const int n {5};
    double data[n] {1.2, 2.3, 3.4, 4.5, 5.6};
    Stats stats;
    for (int i = 0; i < n; i++)
        stats.add(data[i]);
    std::cout << "average = " << stats.avg() << " for "
              << stats.n() << " data points" << std::endl;
    return 0;
}

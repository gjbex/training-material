#include <iostream>

#include "stats.h"

int main() {
    double value;
    Stats stats;
    while (std::cin >> value) {
        stats.add(value);
    }
    try {
        std::cout << "mean: " << stats.mean() << std::endl;
        std::cout << "stddev: " << stats.stddev() << std::endl;
        std::cout << "min: " << stats.min() << std::endl;
        std::cout << "max: " << stats.max() << std::endl;
        std::cout << "median: " << stats.median() << std::endl;
        std::cout << "n: " << stats.nr_values() << std::endl;
    } catch (std::out_of_range& e) {
        std::cerr << "### error: " << e.what() << std::endl;
        std::exit(1);
    }
    return 0;
}

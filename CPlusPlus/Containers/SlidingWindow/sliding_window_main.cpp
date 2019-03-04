#include <iostream>

#include "sliding_window.h"

int main(int argc, char* argv[]) {
    size_t size = 10;
    if (argc > 1)
        size = std::stoul(argv[1]);
    SlidingWindow<double> window(size);
    double value;
    while (std::cin >> value) {
        window.add(value);
        std::cout << "mean: " << window.mean() << std::endl;
    }
    return 0;
}

#include <iostream>

#include "circle_factory.h"

int main(int argc, char *argv[]) {
    int nr_circles {10};
    if (argc >= 2)
        nr_circles = std::stoi(argv[1]);
    double radius {0.1};
    if (argc >= 3)
        radius = std::stof(argv[2]);
    int seed {1234};
    if (argc >= 4)
        seed = std::stoi(argv[3]);
    CircleFactory factory(radius, seed);
    for (int i = 0; i < nr_circles; ++i) {
        Circle circle {factory.create()};
        std::cout << circle << std::endl;
    }
    return 0;
}

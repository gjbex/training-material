#include <iomanip>
#include <iostream>

#include "terrain.h"

int main(int argc, char* argv[]) {
    size_t n {20};
    if (argc > 1)
        n = std::stoul(argv[1]);
    double distance {30.0};
    if (argc > 2)
        distance = std::stof(argv[2]);
    double delta_mean {0.02};
    if (argc > 3)
        delta_mean = std::stof(argv[3]);
    double delta_stddev {0.05};
    if (argc > 4)
        delta_stddev = std::stof(argv[4]);
    double flat_fraction {0.2};
    if (argc > 5)
        flat_fraction = std::stof(argv[5]);
    Seed_t seed {1234};
    if (argc > 6)
        seed = std::stoul(argv[6]);
    Terrain terrain(n, distance, delta_mean, delta_stddev, flat_fraction, seed);
    std::cout << terrain;
    return 0;
}

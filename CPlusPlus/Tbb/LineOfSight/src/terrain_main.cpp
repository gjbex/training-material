#include <iostream>

#include "terrain.h"

int main(int argc, char* argv[]) {
    size_t n {20};
    if (argc > 1)
        n = std::stoul(argv[1]);
    double distance {30.0};
    if (argc > 2)
        distance = std::stof(argv[2]);

    return 0;
}

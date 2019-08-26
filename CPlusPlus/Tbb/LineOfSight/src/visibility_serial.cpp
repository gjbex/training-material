#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "terrain.h"

auto compute_visibility(const Terrain& terrain) {
    std::vector<bool> is_visible;
    double max_angle = -std::numeric_limits<double>::max();
    for (size_t i = 0; i < terrain.n(); ++i) {
        double angle {atan2(terrain.altitude(i), terrain.distance(i))};
        if (angle > max_angle) {
            max_angle = angle;
            is_visible.push_back(true);
        } else {
            is_visible.push_back(false);
        }
    }
    return is_visible;
}

int main() {
    Terrain terrain(std::cin);
    auto is_visible = compute_visibility(terrain);
    std::cout << std::setprecision(5) << std::fixed;
    for (size_t i = 0; i < terrain.n(); ++i)
        std::cout << terrain.distance(i) << " " << is_visible[i] << "\n";
    return 0;
}

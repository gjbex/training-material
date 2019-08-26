#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "terrain.h"

auto compute_line_of_sight(const Terrain& terrain) {
    std::vector<double> los;
    double max_angle {-std::numeric_limits<double>::max()};
    double max_altitude {0.0};
    double max_distance {0.0};
    los.push_back(0.0);
    for (size_t i = 1; i < terrain.n(); ++i) {
        double angle {atan2(terrain.altitude(i), terrain.distance(i))};
        if (angle > max_angle) {
            max_angle = angle;
            max_distance = terrain.distance(i);
            max_altitude = terrain.altitude(i);
            los.push_back(terrain.altitude(i));
        } else if (abs(max_distance) < 1e-7) {
            los.push_back(0.0);
        } else {
            los.push_back(max_altitude*terrain.distance(i)/max_distance);
        }
    }
    return los;
}

int main() {
    Terrain terrain(std::cin);
    auto los = compute_line_of_sight(terrain);
    std::cout << std::setprecision(5) << std::fixed;
    for (size_t i = 0; i < terrain.n(); ++i)
        std::cout << terrain.distance(i) << " " << los[i] << "\n";
    return 0;
}

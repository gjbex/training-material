#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "terrain.h"

using my_time_t = std::chrono::nanoseconds;

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
    auto start_time = std::chrono::steady_clock::now();
    auto is_visible = compute_visibility(terrain);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time = " << duration.count()*1e-9 << " s" << std::endl;
    std::cout << std::setprecision(5) << std::fixed;
    for (size_t i = 0; i < terrain.n(); ++i)
        std::cout << terrain.distance(i) << " " << is_visible[i] << "\n";
    return 0;
}

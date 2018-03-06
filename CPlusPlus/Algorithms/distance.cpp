#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<double> x_coords;
    std::vector<double> y_coords;
    double x, y;
    while (std::cin >> x >> y) {
        x_coords.push_back(x);
        y_coords.push_back(y);
    }
    std::vector<double> distances;
    std::transform(x_coords.cbegin(), x_coords.cend(), y_coords.cbegin(),
                   std::back_inserter(distances),
                   [] (double x, double y) { return sqrt(x*x + y*y); });
    for (const auto& distance: distances)
        std::cout << distance << std::endl;
    double sum = {std::accumulate(distances.cbegin(), distances.cend(),
                                  0.0)};
    std::cout << "average distance = " << sum/x_coords.size() << std::endl;
    return 0;
}

#include <array>
#include <cmath>
#include <iostream>

using Position = std::array<double, 3>;

inline double sqr(double x) { return x*x; }

double distance(const Position& p1, const Position& p2) {
    double dist {0.0};
    for (size_t i = 0; i < p1.size(); i++)
        dist += sqr(p1[i] - p2[i]);
    return std::sqrt(dist);
}

int main() {
    Position p1 {{1.0, 2.0, 3.0}};
    Position p2 {{0.0, 1.0, 2.0}};
    std::cout << distance(p1, p2) << std::endl;
    return 0;
}

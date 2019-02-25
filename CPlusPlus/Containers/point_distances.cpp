#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using Vector3d = std::array<double,3>;

Vector3d create_point(std::function<double()> distr);
double compute_max_distance(const std::vector<Vector3d>& points);

int main(int argc, char *argv[]) {
    size_t nr_points {10};
    if (argc > 1)
        nr_points = std::stoi(std::string(argv[1]));
    auto engine {std::mt19937_64(1234)};
    auto point_distr = std::bind(std::normal_distribution<double>(0.0, 1.0),
                                 std::ref(engine));
    std::vector<Vector3d> points;
    for (size_t i = 0; i < nr_points; i++)
        points.push_back(create_point(point_distr));
    std::cout << compute_max_distance(points) << std::endl;
    return 0;
}

Vector3d create_point(std::function<double()> distr) {
    Vector3d point;
    for (auto& comp: point)
        comp = distr();
    return point;
}

inline double sqr(double x) {
    return x*x;
}

double distance(Vector3d p1, Vector3d p2) {
    using std::sqrt;
    double dist {0.0};
    for (size_t i = 0; i < p1.size(); i++)
        dist += sqr(p1[i] - p2[i]);
    return sqrt(dist);
}

double compute_max_distance(const std::vector<Vector3d>& points) {
    double max_dist {0.0};
    for (const auto& p1: points)
        for (const auto& p2: points) {
            auto dist = distance(p1, p2);
            if (dist > max_dist)
                max_dist = dist;
        }
    return max_dist;
}

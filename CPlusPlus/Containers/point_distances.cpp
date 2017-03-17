#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

using vector3d = array<double,3>;

vector3d create_point(function<double()> distr);
double compute_max_distance(const vector<vector3d>& points);

int main(int argc, char *argv[]) {
    size_t nr_points {10};
    if (argc > 1)
        nr_points = stoi(string(argv[1]));
    auto engine {mt19937_64(1234)};
    auto point_distr = bind(normal_distribution<double>(0.0, 1.0),
                            ref(engine));
    vector<vector3d> points;
    for (size_t i = 0; i < nr_points; i++)
        points.push_back(create_point(point_distr));
    cout << compute_max_distance(points) << endl;
    return 0;
}

vector3d create_point(function<double()> distr) {
    vector3d point;
    for (size_t i = 0; i < point.size(); i++)
        point[i] = distr();
    return point;
}

inline double sqr(double x) {
    return x*x;
}

double distance(vector3d p1, vector3d p2) {
    double dist {0.0};
    for (size_t i = 0; i < p1.size(); i++)
        dist += sqr(p1[i] - p2[i]);
    return sqrt(dist);
}

double compute_max_distance(const vector<vector3d>& points) {
    double max_dist {0.0};
    for (auto it1 = points.begin(); it1 != points.end(); it1++)
        for (auto it2 = points.begin(); it2 != it1; it2++) {
            auto dist = distance(*it1, *it2);
            if (dist > max_dist)
                max_dist = dist;
        }
    return max_dist;
}

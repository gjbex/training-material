#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

struct Point {
    double x;
    double y;
    Point();
    static void reset() { engine_.seed(1234); }
    private:
    static std::mt19937_64 engine_;
    static std::normal_distribution<double> distr_;
};

std::mt19937_64 Point::engine_(1234);
std::normal_distribution<double> Point::distr_(0.0, 1.0);

Point::Point() {
    x = distr_(engine_);
    y = distr_(engine_);
}

using my_time_t = std::chrono::nanoseconds;

using Vector = std::valarray<double>;
int main() {
    const std::size_t i_max {10000000};
    double dist {0.0};
    Point::reset();
    auto start_time = std::chrono::steady_clock::now();
    Point* point_ptr {(Point*) malloc(sizeof(Point))};
    for (std::size_t i = 0; i < i_max; ++i) {
        Point* p = new(point_ptr) Point();
        dist += std::sqrt(p->x*p->x + p->y*p->y);
    }
    free(point_ptr);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    std::cout << "mean distance = " << dist << std::endl;
    Point::reset();
    dist = 0.0;
    start_time = std::chrono::steady_clock::now();
    for (std::size_t i = 0; i < i_max; ++i) {
        Point* p = new Point();
        dist += std::sqrt(p->x*p->x + p->y*p->y);
    }
    end_time = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    std::cout << "mean distance = " << dist << std::endl;
    return 0;
}

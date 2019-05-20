#include <cmath>
#include <iostream>
#include <vector>

struct Stats {
    double mean;
    double stddev;
    int n;
};

Stats compute_stats(std::vector<double> data) {
    double sum {0.0};
    double sum2 {0.0};
    int n {0};
    for (auto value: data) {
        ++n;
        sum += value;
        sum2 += value*value;
    }
    Stats stats { sum/n, sqrt((sum2 - sum*sum/n)/(n - 1)), n };
    return stats;
}

int main() {
    std::vector<double> data {1.0, 2.0, 3.0};
    auto [mean, stddev, n] = compute_stats(data);
    std::cout << "mean = " << mean << std::endl;
    std::cout << "stddev = " << stddev << std::endl;
    std::cout << "n = " << n << std::endl;
    return 0;
}

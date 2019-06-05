#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> x_vals;
    for (double x = -3.0; x <= 3.0; x += 0.2)
        x_vals.push_back(x);
    double a {-11.0};
    double b {3.0};
    double c {1.5};
    std::vector<double> y_vals;
    std::transform(x_vals.begin(), x_vals.end(), std::back_inserter(y_vals),
                   [a, b, c] (double& x) { return (a*x + b)*x + c; });
    for (std::size_t i = 0; i < x_vals.size(); ++i)
        std::cout << x_vals[i] << " " << y_vals[i] << "\n";
    return 0;
}


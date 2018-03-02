#include <functional>
#include <iostream>
#include <vector>

double aggregate(const std::vector<double> data,
                 std::function<void(double&, const double)> reductor,
                 double init_val) {
    double x {init_val};
    for (auto y: data) {
        reductor(x, y);
    }
    return x;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "### error: expecting either 'sum' or 'prod'"
                  << std::endl;
        return 1;
    }
    std::vector<double> data;
    double x {0.0};
    while (std::cin >> x) {
        data.push_back(x);
    }
    std::string operation(argv[1]);
    if (operation == "sum") {
        std::cout << aggregate(data,
                               [] (double& x, const double y) { x += y; },
                               0.0);
    } else if (operation == "prod") {
        std::cout << aggregate(data,
                               [] (double& x, const double y) { x *= y; },
                               1.0);
    } else {
        std::cerr << "### invalid operation '" << operation << "'" 
                  << std::endl;
        return 2;
    }
    return 0;
}

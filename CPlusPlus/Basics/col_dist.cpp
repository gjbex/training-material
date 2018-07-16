#include <iostream>
#include <cmath>

double dist(double x, double y);

int main() {
    double a, b;
    while (cin >> a >> b) {
        std::cout << dist(a, b) << std::endl;
    }
    return 0;
}

double dist(double x, double y) {
    using std::sqrt;
    return sqrt(x*x + y*y);
}

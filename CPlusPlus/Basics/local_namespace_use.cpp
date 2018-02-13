#include <iostream>
#include <cmath>

double distance(double x, double y);

int main(int argc, char *argv[]) {
    double x {0.0};
    double y {0.0};
    while (std::cin >> x >> y) {
        std::cout << distance(x, y) << std::endl;
    }
    return 0;
}

double distance(double x, double y) {
    using namespace std;
    return sqrt(x*x + y*y);
}

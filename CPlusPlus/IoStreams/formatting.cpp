#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    const double PI {acos(-1.0)};
    std::cout << "default format: " << PI << std::endl;
    std::cout << "scientific format: " << std::scientific
              <<  PI << std::endl;
    std::cout << "fixed format: " << std::fixed << PI << std::endl;
    std::cout << "default format: " << std::defaultfloat
              << PI << std::endl;
    auto orig_prec = std::cout.precision();
    for (int prec = 1; prec < 16; prec++)
        std::cout << "prec " << prec << ": '" << std::setprecision(prec)
                  << PI << "'" << std::endl;
    std::cout.precision(orig_prec);
    for (int width = 10; width < 15; width++) {
        std::cout << "width " << width << ": '";
        auto orig_width = std::cout.width();
        std::cout.width(width);
        std::cout << PI;
        std::cout.width(orig_width);
        std::cout << "'" << std::endl;
    }
    const int data {123};
    auto orig_width = std::cout.width();
    auto orig_fill = std::cout.fill();
    for (int width = 3; width < 6; width++) {
        std::cout.fill('0');
        std::cout.width(width);
        std::cout << data << std::endl;
    }
    std::cout.fill(orig_fill);
    std::cout.width(5);
    std::cout << data << std::endl;
    std::cout.width(orig_width);
    return 0;
}

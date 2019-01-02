#include <iostream>

inline double quad(double x) {
    return (3.14*x - 2.4)*x + 1.9;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "### error: expecting floating point argument"
                  << std::endl;
        return 1;
    }
    double x {std::stod(argv[1])};
    std::cout << quad(x) << std::endl;
    return 0;
}


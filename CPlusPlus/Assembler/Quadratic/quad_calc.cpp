#include <iostream>

extern "C" double quad_(double);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "### error: expecting floating point argument"
                  << std::endl;
        return 1;
    }
    double x {std::stod(argv[1])};
    std::cout << quad_(x) << std::endl;
    return 0;
}

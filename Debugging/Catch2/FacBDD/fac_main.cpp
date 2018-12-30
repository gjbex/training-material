#include <iostream>

#include "fac.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "### error: expect 1 argument" << std::endl;
        return 1;
    }
    int n {0};
    try {
        n = std::stoi(argv[1]);
    } catch(std::domain_error&) {
        std::cerr << "### error: argument must be integer" << std::endl;
        return 2;
    }
    int result {0};
    try {
        result = fac(n);
    } catch(std::invalid_argument&) {
        std::cerr << "### error: argument must be positive" << std::endl;
        return 3;
    }
    std::cout << "fac(" << n << ") = " << result << std::endl;
    return 0;
}

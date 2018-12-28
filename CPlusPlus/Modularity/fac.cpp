#include <iostream>
#include <limits>
#include <stdexcept>

const int EXIT_MISSING_ARG = 1;
const int EXIT_ARG_TYPE = 2;
const int EXIT_OUT_OF_RANGE = 3;
const int EXIT_NEG_ARG = 4;
const int EXIT_OVERLOW = 5;

int fac(int n);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "# error: expecting an argument" << std::endl;
        return EXIT_MISSING_ARG;
    }
    int n = 0;
    try {
        n = std::stoi(argv[1]);
    } catch (std::invalid_argument&) {
        std::cerr << "# error: '" << argv[1] << "' can not be converted to int"
             << std::endl;
        return EXIT_ARG_TYPE;
    } catch (std::out_of_range&) {
        std::cerr << "# error: " << argv[1]  << " is out of range" << std::endl;
        return EXIT_OUT_OF_RANGE;
    }
    try {
        std::cout << fac(n) << std::endl;
    } catch (std::domain_error& e) {
        std::cerr << "# error: domain error, " << e.what() << std::endl;
        return EXIT_NEG_ARG;
    } catch (std::overflow_error& e) {
        std::cerr << "# error: overflow error, " << e.what() << std::endl;
        return EXIT_OVERLOW;
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        std::string msg {"fac argument "};
        msg += std::to_string(n) + ", must be positive";
        throw std::domain_error {msg};
    } else {
        const int max_int {std::numeric_limits<int>::max()};
        int result = 1;
        for (int i = 2; i <= n; i++) {
            if (result < max_int/i) {
                result *= i;
            } else {
                std::string msg {"fac argument "};
                msg += std::to_string(n) + " causes overflow";
                throw std::overflow_error {msg};
            }
        }
        return result;
    }
}

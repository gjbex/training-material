#include <iostream>
#include <stdexcept>

const int EXIT_MISSING_ARG = 1;
const int EXIT_ARG_TYPE = 2;
const int EXIT_NEG_ARG = 3;

int fac(int n);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "# error: expecting an argument" << std::endl;
        return EXIT_MISSING_ARG;
    }
    int n = 0;
    try {
        n = std::stoi(argv[1]);
    } catch(std::invalid_argument) {
        std::cerr << "# error: '" << argv[1] << "' can not be converted to int"
             << std::endl;
        return EXIT_ARG_TYPE;
    } catch(std::logic_error) {
        std::cerr << "# error: expecting one argument to fac.exe" << std::endl;
        return EXIT_MISSING_ARG;
    }
    try {
        std::cout << fac(n) << std::endl;
    } catch(std::invalid_argument e) {
        std::cerr << "# error: invalid argument, " << e.what() << std::endl;
        return EXIT_NEG_ARG;
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        std::string msg("fac argument ");
        msg += std::to_string(n) + ", must be positive";
        throw std::invalid_argument(msg);
    } else {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
}

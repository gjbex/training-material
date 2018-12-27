#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

const int ERR_ARGUMENTS = 1;
const int ERR_DOMAIN = 2;
const int ERR_OVERFLOW = 3;

using Vector = std::vector<int> *;

Vector fac_range(int min_value, int max_value);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "### error: two integer arguments expected" << std::endl;
        return ERR_ARGUMENTS;
    }
    int min_value {std::stoi(argv[1])};
    int max_value {std::stoi(argv[2])};
    try {
        Vector values = fac_range(min_value, max_value);
        for (auto const& value: *values)
            std::cout << value << " ";
        std::cout << std::endl;
        delete values;
    } catch (std::domain_error& e) {
        std::cerr << "### error: " << e.what() << std::endl;
        return ERR_DOMAIN;
    } catch (std::overflow_error& e) {
        std::cerr << "### error: overflow, " << e.what() << std::endl;
        return ERR_OVERFLOW;
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        throw std::domain_error {"negative argument for fac"};
    } else {
        const int max_int = std::numeric_limits<int>::max();
        int value = 1;
        for (int i = 2; i <= n; ++i)
            if (value < max_int/i)
                value *= i;
            else
                throw std::overflow_error {std::to_string(n) +
                                           " caused overflow"};
        return value;
    }
}

Vector fac_range(int min_value, int max_value) {
    Vector values = new std::vector<int>();
    try {
        for (int i = min_value; i < max_value; ++i)
            values->push_back(fac(i));
    } catch(std::exception& e) {
        std::cerr << "# warning: something went wrong in fac_range" << std::endl;
        throw;
    }
    return values;
}

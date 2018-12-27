#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

const int ERR_ARGUMENTS = 1;
const int ERR_DOMAIN = 2;

using Vector = std::unique_ptr<std::vector<int>>;

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
    } catch (std::domain_error& e) {
        std::cerr << "### error: " << e.what() << std::endl;
        return ERR_DOMAIN;
    }
    return 0;
}

int fac(int n) {
    if (n < 0) {
        throw std::domain_error {"negative argument for fac"};
    } else {
        int value = 1;
        for (int i = 2; i <= n; ++i)
            value *= i;
        return value;
    }
}

Vector fac_range(int min_value, int max_value) {
    Vector values = std::make_unique<std::vector<int>>();
    for (int i = min_value; i < max_value; ++i)
        values->push_back(fac(i));
    return values;
}

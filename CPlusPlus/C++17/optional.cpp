#include <iostream>
#include <optional>

std::optional<int> fac(const int n) {
    if (n < 0) return {};
    int result = 1;
    for (int i = 2; i < n; i++)
        result *= i;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "### error: expecting number as argument"
                  << std::endl;
        return 1;
    }
    int n = std::stoi(argv[1]);
    if (auto result = fac(n)) {
        std::cout << "fac(" << n << ") = " << *result << std::endl;
        return 0;
    } else {
        std::cerr << "### error: invalud argument for factorial function"
                  << std::endl;
        return 1;
    }
}

#include <functional>
#include <iostream>
#include <random>
#include <string>

using Seed_t = std::mt19937_64::result_type;
using Distr_t = std::uniform_real_distribution<double>;

int main(int argc, char *argv[]) {
    Seed_t seed {1234};
    if (argc > 1)
        seed = std::stoul(argv[1]);
    auto distribution = std::bind(Distr_t(0.0, 1.0), std::mt19937_64(seed));
    int n {10};
    if (argc > 2)
        n = std::stoi(argv[2]);
    for (int i = 0; i < n; ++i)
        std::cout << distribution() << std::endl;
    return 0;
}

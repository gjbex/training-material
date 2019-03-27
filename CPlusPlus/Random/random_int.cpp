#include <functional>
#include <iostream>
#include <random>
#include <string>

int main(int argc, char *argv[]) {
    std::mt19937::result_type seed {1234};
    if (argc > 1)
        seed = std::stoul(argv[1]);
    auto distribution = std::bind(std::uniform_int_distribution<int>(1, 100),
                                  std::mt19937(seed));
    int n {10};
    if (argc > 2)
        n = std::stoi(argv[2]);
    for (int i = 0; i < n; ++i)
        std::cout << distribution() << std::endl;
    return 0;
}

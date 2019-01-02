#include <iostream>

extern "C" int calc_sum_(int, int, int);

int main(int argc, char *argv[]) {
    int n {2000};
    if (argc == 2)
        n = std::stoi(argv[1]);
    int total {0};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                total += calc_sum_(i, j, k);
    std::cout << "total = " << total << std::endl;
    return 0;
}

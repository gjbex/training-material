#include <iostream>

extern "C" int calc_sum_(int a, int b, int c);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "### error: three integer arguments expected"
                  << std::endl;
        return 1;
    }
    int a {std::stoi(argv[1])};
    int b {std::stoi(argv[2])};
    int c {std::stoi(argv[3])};
    int sum {calc_sum_(a, b, c)};
    std::cout << a << " + " << b << " + " << c << " = " << sum
              << std::endl;
    return 0;
}

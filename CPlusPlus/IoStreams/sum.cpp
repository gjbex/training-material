#include <iostream>

int main() {
    double sum {0.0};
    double data {0.0};
    while (std::cin >> data)
        sum += data;
    std::cout << sum << std::endl;
    return 0;
}

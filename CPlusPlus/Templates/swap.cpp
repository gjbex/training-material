#include <iostream>

template<typename T> void swap_values(T& a, T& b);

int main() {
    int i {1};
    int j {2};
    std::cout << i << ", " << j << std::endl;
    swap_values(i, j);
    std::cout << i << ", " << j << std::endl;
    double a {3.1};
    double b {5.2};
    std::cout << a << ", " << b << std::endl;
    swap_values(a, b);
    std::cout << a << ", " << b << std::endl;
    return 0;
}

template<typename T> void swap_values(T& a, T& b) {
    auto tmp {a};
    a = b;
    b = tmp;
}

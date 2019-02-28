#include <iostream>

template<int N>
struct Fac {
    static constexpr int value = N*Fac<N-1>::value;
};

template<>
struct Fac<0> {
    static const int value = 1;
};

int main() {
    std::cout << Fac<5>::value << std::endl;
    return 0;
}

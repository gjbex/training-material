#include <iostream>

template<unsigned long N>
struct Fac {
    static constexpr unsigned long value = N*Fac<N-1>::value;
};

template<>
struct Fac<0> {
    static const unsigned long value = 1;
};

int main() {
    std::cout << Fac<5>::value << std::endl;
    return 0;
}

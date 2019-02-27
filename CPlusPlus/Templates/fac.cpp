#include <iostream>

template<int N>
struct Fac {
    enum { value = N*Fac<N-1>::value };
};

template<>
struct Fac<0> {
    enum { value = 1 };
};

int main() {
    std::cout << Fac<5>::value << std::endl;
    return 0;
}

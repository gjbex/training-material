#include <iostream>

double sum() { return 0.0; }
template<typename T, typename... Tail>
double sum(T head, Tail... tail) {
    return head + sum(tail...);
}

int main() {
    std::cout << sum(1.2, 2.3, 3.4) << std::endl;
    std::cout << sum(1.2, 2.3, 3.4, 4.5) << std::endl;
    return 0;
}

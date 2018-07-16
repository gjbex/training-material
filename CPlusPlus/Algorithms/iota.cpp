#include <algorithm>
#include <iostream>
#include <numeric>
#include <valarray>

int main() {
    const int n {10};
    std::valarray<double> data(n);
    std::iota(std::begin(data), std::end(data), 1.0);
    for (const auto& value: data)
        std::cout << value << " ";
    std::cout << std::endl;
    data = data.apply([] (double x) { return x*x; });
    for (auto value: data)
        std::cout << value << " ";
    std::cout << std::endl;
    return 0;
}

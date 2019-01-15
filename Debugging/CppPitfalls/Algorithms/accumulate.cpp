#include <iostream>
#include <numeric>
#include <vector>

int main(void) {
    std::vector<int> v1 {3, 5, 7};
    auto sum1 = std::accumulate(v1.cbegin(), v1.cend(), 0);
    std::cout << "sum of";
    for (auto value: v1)
        std::cout << " " << value;
    std::cout << " = " << sum1 << std::endl;
    std::vector<double> v2 {3.3, 5.3, 7.4};
    auto sum2 = std::accumulate(v2.cbegin(), v2.cend(), 0);
    std::cout << "sum of";
    for (auto value: v2)
        std::cout << " " << value;
    std::cout << " = " << sum2 << std::endl;
    auto sum3 = std::accumulate(v2.cbegin(), v2.cend(), 0.0);
    std::cout << "sum of";
    for (auto value: v2)
        std::cout << " " << value;
    std::cout << " = " << sum3 << std::endl;
    return 0;
}

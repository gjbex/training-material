#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> v {{0.5, 0.75, 1.0, 1.5, 3.5}};
    std::for_each(v.begin(), v.end(), [] (double& x) { x *= x; });
    for (auto x: v)
        std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}

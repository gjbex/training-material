#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char *argv[]) {
    int n {5};
    if (argc > 1)
        n = std::stoi(argv[1]);
    std::vector<int> v;
    for (int i = 0; i < n; i++)
        v.push_back(i*i);
    auto sum = std::accumulate(v.cbegin(), v.cend(), 0,
                               [](int x, int y) { return x + y; });
    std::cout << "sum_i=0^" << n << " i^2 = " << sum << std::endl;
    return 0;
}

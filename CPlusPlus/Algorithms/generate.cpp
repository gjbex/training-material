#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(),
                  [] () { static int i {0}; i++; return i*i; });
    for (auto i: v)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> v = {{"a", "b", "c", "d"}};
    int i {0};
    do {
        std::cout << ++i << ": ";
        for (auto str: v)
            std::cout << str << " ";
        std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
    return 0;
}

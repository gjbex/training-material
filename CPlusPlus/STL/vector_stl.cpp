#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        v.push_back(i);
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = v.begin(); it != v.end(); ++it)
        *it = (*it)*(*it);
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    return 0;
}

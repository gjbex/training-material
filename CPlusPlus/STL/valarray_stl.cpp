#include <iostream>
#include <valarray>

int main() {
    std::size_t array_size {10};
    std::valarray<int> v(array_size);
    int i {0};
    for (auto it = begin(v); it != end(v); ++it)
        *it = i++;
    for (auto it = cbegin(v); it != cend(v); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    return 0;
}

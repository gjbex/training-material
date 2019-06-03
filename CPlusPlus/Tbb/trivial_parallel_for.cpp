#include <algorithm>
#include <iostream>
#include <numeric>
#include <tbb/tbb.h>
#include <valarray>

int main() {
    std::valarray<int> data(10);
    std::iota(std::begin(data), std::end(data), 0);
    for (const auto& val: data)
        std::cout << val << " ";
    std::cout << std::endl;
    std::for_each(std::begin(data), std::end(data),
                  [] (int& i) { i = i*i; });
    for (const auto& val: data)
        std::cout << val << " ";
    std::cout << std::endl;
    tbb::parallel_for(0ul, data.size(),
                      [&data] (std::size_t i) { data[i] = data[i]*data[i]; });
    for (const auto& val: data)
        std::cout << val << " ";
    std::cout << std::endl;
    return 0;
}

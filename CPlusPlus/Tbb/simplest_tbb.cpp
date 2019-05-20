#include <iostream>
#include <sstream>
#include <tbb/tbb.h>
#include <valarray>

void print_values(const std::valarray<int>& v) {
    tbb::parallel_for(static_cast<std::size_t>(0), v.size(),
            [&] (std::size_t i) {
                std::string line;
                std::stringstream stream(line);
                stream << i << ": " << v[i] << std::endl;
                std::cout << stream.str();
            });
}

std::valarray<int> init_values(std::size_t n) {
    std::valarray<int> v(n);
    tbb::parallel_for(static_cast<std::size_t>(0), n,
            [&] (std::size_t i) {
                v[i] = i*i;
            });
    return v;
}

int main(int argc, char *argv[]) {
    std::size_t nv {100};
    if (argc > 1)
        nv = std::stoi(argv[1]);
    std::valarray<int> v = init_values(nv);
    print_values(v);
    return 0;
}


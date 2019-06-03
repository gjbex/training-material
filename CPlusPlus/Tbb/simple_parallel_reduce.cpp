#include <iostream>
#include <numeric>
#include <tbb/tbb.h>
#include <valarray>

void print_values(const std::valarray<int>& v) {
    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, v.size()),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (std::size_t i = r.begin(); i < r.end(); i++)
                    std::cout << i << ": " << v[i] << std::endl;
            });
}

std::valarray<int> init_values(size_t n) {
    std::valarray<int> v(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (std::size_t i = r.begin(); i < r.end(); i++)
                    v[i] = i*i;
            });
    return v;
}

int sum_values(const std::valarray<int>& v) {
    int sum = tbb::parallel_reduce(
                  tbb::blocked_range<size_t>(0, v.size()),
                  0,
                  [&](const tbb::blocked_range<size_t>& r, int init) {
                      for (std::size_t i = r.begin(); i < r.end(); i++)
                          init += v[i];
                      return init;
                  },
                  [](int x, int y) { return x + y; });
    return sum;
}

int main(int argc, char *argv[]) {
    std::size_t nv {100};
    if (argc > 1)
        nv = std::stoi(argv[1]);
    std::valarray<int> v = init_values(nv);
    print_values(v);
    std::cout << "sum = " << sum_values(v) << std::endl;
    return 0;
}

#include <iostream>
#include <numeric>
#include <sstream>
#include <tbb/tbb.h>
#include <vector>

std::vector<int> init_values(size_t n) {
    std::vector<int> v(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (std::size_t i = r.begin(); i < r.end(); i++)
                    v[i] = i*i;
            });
    return v;
}

int sum_values(const std::vector<int>& v) {
    int sum = tbb::parallel_reduce(
                  tbb::blocked_range<size_t>(0, v.size()),
                  0.0,
                  [&](const tbb::blocked_range<size_t>& r, int init) {
                      return std::accumulate(
                              v.cbegin() + r.begin(),
                              v.cbegin() + r.end(),
                              init,
                              [](int x, int y) { return x + y; });
                  },
                  [](int x, int y) { return x + y; });
    return sum;
}

int main(int argc, char *argv[]) {
    std::size_t nv {100};
    if (argc > 1)
        nv = std::stoi(argv[1]);
    auto v = init_values(nv);
    std::cout << "sum = " << sum_values(v) << std::endl;
    return 0;
}

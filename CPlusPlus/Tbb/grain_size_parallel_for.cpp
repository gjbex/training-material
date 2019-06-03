#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <tbb/tbb.h>
#include <valarray>

using my_time_t = std::chrono::nanoseconds;
using Vector = std::valarray<double>;
using std::sqrt;
using std::log;
using std::sin;

Vector init_values(size_t n, std::size_t grain_size) {
    Vector v(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n, grain_size),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (std::size_t i = r.begin(); i < r.end(); i++)
                    v[i] = sqrt(log(i + 1.0)) + sin(3.14*i/17.23);
            });
    return v;
}

int main(int argc, char *argv[]) {
    std::size_t nv {100};
    std::size_t grain_size {1};
    if (argc > 1)
        nv = std::stoul(argv[1]);
    if (argc > 2)
        grain_size = std::stoul(argv[2]);
    auto start_time = std::chrono::steady_clock::now();
    Vector v = init_values(nv, grain_size);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    std::cout << "sum = " << v.sum() << std::endl;
    return 0;
}

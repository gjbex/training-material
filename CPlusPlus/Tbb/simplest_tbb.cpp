#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <tbb/tbb.h>
#include <valarray>

using my_time_t = std::chrono::nanoseconds;
using Vector = std::valarray<double>;
using std::log;
using std::sin;
using std::sqrt;

Vector init_values(std::size_t n) {
    Vector v(n);
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
    auto start_time = std::chrono::steady_clock::now();
    Vector v = init_values(nv);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<my_time_t>(end_time - start_time);
    std::cerr << "time: " << duration.count()*1.0e-9 << " s" << std::endl;
    std::cout << "sum = " << v.sum() << std::endl;
    return 0;
}


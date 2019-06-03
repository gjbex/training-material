#include <algorithm>
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <tbb/tbb.h>
#include <valarray>

using namespace std;
using my_time_t = chrono::nanoseconds;

using Complex_t = complex<double>;
using Coords_t = valarray<double>;
using Z_t = valarray<Complex_t>;
using Img_t = valarray<size_t>;

Coords_t coordinates(double min_coord, double max_coord, size_t steps);
Z_t z_values(const Coords_t& x_coords, const Coords_t& y_coords);
Img_t iterate_zs(Z_t& zs, const Complex_t& c, size_t max_iters);
void print_results(const Img_t& ns);

int main(int argc, char *argv[]) {
    const Complex_t c(-0.62772, - 0.42193);
    const double x1 {-1.8};
    const double x2 {1.8};
    const double y1 {-1.8};
    const double y2 {1.8};
    const size_t max_iters {255};
    size_t steps {100};
    if (argc > 1)
        steps = stoi(argv[1]);
    Coords_t x_coords = coordinates(x1, x2, steps);
    Coords_t y_coords = coordinates(y1, y2, steps);
    Z_t zs = z_values(x_coords, y_coords);
    auto start_time = chrono::steady_clock::now();
    Img_t ns = iterate_zs(zs, c, max_iters);
    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<my_time_t>(end_time - start_time);
    cerr << "time: " << duration.count()*1.0e-9 << " s" << endl;
    print_results(ns);
    return 0;
}

Coords_t coordinates(double min_coord, double max_coord, size_t steps) {
    Coords_t coords(steps);
    const double step {(max_coord - min_coord)/steps};
    double value {min_coord};
    for (size_t i = 0; i < steps; i++) {
        coords[i] = value;
        value += step;
    }
    return coords;
}

Z_t z_values(const Coords_t& x_coords, const Coords_t& y_coords) {
    Z_t zs(x_coords.size()*y_coords.size());
    tbb::parallel_for(tbb::blocked_range<size_t>(0, y_coords.size()),
            [&] (const tbb::blocked_range<size_t> r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                    for (size_t j = 0; j < x_coords.size(); j++) {
                        Complex_t z(x_coords[j], y_coords[i]);
                        zs[i*x_coords.size() + j] = z;
                    }
            });
    return zs;
}

int iterate_z(Complex_t z, const Complex_t& c, size_t max_iters) {
    size_t n {0};
    const Complex_t z_in {z};
    while (real(z)*real(z) + imag(z)*imag(z) < 4.0 && n++ < max_iters)
        z = z*z + c;
    return n;
}

Img_t iterate_zs(Z_t& zs, const Complex_t& c, size_t max_iters) {
    Img_t ns(0ul, zs.size());
    tbb::parallel_for(tbb::blocked_range<size_t>(0, zs.size()),
            [&] (const tbb::blocked_range<size_t> r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                    ns[i] = iterate_z(zs[i], c, max_iters);
            });
    return ns;
}

void print_results(const Img_t& ns) {
    size_t steps = ((size_t) sqrt(ns.size()) + 0.1);
    size_t count {0};
    for (auto n: ns) {
        cout << n;
        if (++count % steps == 0)
            cout << endl;
        else
            cout << " ";
    }
}

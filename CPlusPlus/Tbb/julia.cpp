#include <algorithm>
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <valarray>

using namespace std;
using my_time_t = chrono::nanoseconds;

using cmplx = complex<double>;

valarray<double> coordinates(double min_coord, double max_coord,
                             size_t steps);
valarray<cmplx> z_values(const valarray<double>& x_coords,
                         const valarray<double>& y_coords);
valarray<int> iterate_zs(valarray<cmplx>& zs, const complex<double>& c,
                         size_t max_iters);
void print_results(const valarray<int>& ns);

int main(int argc, char *argv[]) {
    const cmplx c(-0.62772, - 0.42193);
    const double x1 {-1.8};
    const double x2 {1.8};
    const double y1 {-1.8};
    const double y2 {1.8};
    const size_t max_iters {255};
    size_t steps {100};
    if (argc > 1)
        steps = stoi(argv[1]);
    valarray<double> x_coords = coordinates(x1, x2, steps);
    valarray<double> y_coords = coordinates(y1, y2, steps);
    valarray<cmplx> zs = z_values(x_coords, y_coords);
    auto start_time = chrono::steady_clock::now();
    valarray<int> ns = iterate_zs(zs, c, max_iters);
    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<my_time_t>(end_time - start_time);
    cerr << "time: " << duration.count()*1.0e-9 << " s" << endl;
    print_results(ns);
    return 0;
}

valarray<double> coordinates(double min_coord, double max_coord,
                             size_t steps) {
    valarray<double> coords(steps);
    const double step {(max_coord - min_coord)/steps};
    double value {min_coord};
    for (size_t i = 0; i < steps; i++) {
        coords[i] = value;
        value += step;
    }
    return coords;
}

valarray<cmplx> z_values(const valarray<double>& x_coords,
                         const valarray<double>& y_coords) {
    valarray<cmplx> zs(x_coords.size()*y_coords.size());
    size_t i {0};
    for (auto y: y_coords)
        for (auto x: x_coords) {
            complex<double> z(x, y);
            zs[i++] = z;
        }
    return zs;
}

int iterate_z(cmplx z, const cmplx& c, size_t max_iters) {
    size_t n {0};
    const complex<double> z_in {z};
    while (real(z)*real(z) + imag(z)*imag(z) < 4.0 && n++ < max_iters)
        z = z*z + c;
    return n;
}

valarray<int> iterate_zs(valarray<cmplx>& zs, const complex<double>& c,
                         size_t max_iters) {
    valarray<int> ns(zs.size());
    size_t i {0};
    for (auto z: zs)
        ns[i++] = iterate_z(z, c, max_iters);
    return ns;
}

void print_results(const valarray<int>& ns) {
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

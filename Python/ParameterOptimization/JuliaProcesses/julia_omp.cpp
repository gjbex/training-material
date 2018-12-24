#include <algorithm>
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <valarray>

using namespace std;
using my_time_t = chrono::nanoseconds;

using cmplx = complex<float>;

valarray<float> coordinates(float min_coord, float max_coord,
                             size_t steps);
valarray<cmplx> z_values(const valarray<float>& x_coords,
                         const valarray<float>& y_coords);
valarray<int> iterate_zs(valarray<cmplx>& zs, const complex<float>& c,
                         size_t max_iters);
void print_results(const valarray<int>& ns);

int main(int argc, char *argv[]) {
    const cmplx c(-0.62772, - 0.42193);
    const float x1 {-1.8};
    const float x2 {1.8};
    const float y1 {-1.8};
    const float y2 {1.8};
    const size_t max_iters {255};
    size_t steps {100};
    if (argc > 1)
        steps = stoi(argv[1]);
    valarray<float> x_coords = coordinates(x1, x2, steps);
    valarray<float> y_coords = coordinates(y1, y2, steps);
    valarray<cmplx> zs = z_values(x_coords, y_coords);
    auto start_time = chrono::steady_clock::now();
    valarray<int> ns = iterate_zs(zs, c, max_iters);
    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<my_time_t>(end_time - start_time);
    cerr << duration.count()*1.0e-9 << endl;
    print_results(ns);
    return 0;
}

valarray<float> coordinates(float min_coord, float max_coord,
                             size_t steps) {
    valarray<float> coords(steps);
    const float step {(max_coord - min_coord)/steps};
    float value {min_coord};
    for (size_t i = 0; i < steps; i++) {
        coords[i] = value;
        value += step;
    }
    return coords;
}

valarray<cmplx> z_values(const valarray<float>& x_coords,
                         const valarray<float>& y_coords) {
    valarray<cmplx> zs(x_coords.size()*y_coords.size());
    size_t i {0};
    for (auto y: y_coords)
        for (auto x: x_coords) {
            complex<float> z(x, y);
            zs[i++] = z;
        }
    return zs;
}

int iterate_z(cmplx z, const cmplx& c, size_t max_iters) {
    size_t n {0};
    const complex<float> z_in {z};
    while (abs(z) < 2.0 && n++ < max_iters)
        z = z*z + c;
    return n;
}

valarray<int> iterate_zs(valarray<cmplx>& zs, const complex<float>& c,
                         size_t max_iters) {
    valarray<int> ns(zs.size());
#pragma omp parallel for schedule(runtime)
    for (size_t i = 0; i < zs.size(); i++)
        ns[i] = iterate_z(zs[i], c, max_iters);
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

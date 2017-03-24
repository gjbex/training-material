#include <complex>
#include <iostream>
#include <valarray>

using namespace std;

int main() {
    complex<double> a {2.0, 3.0};
    complex<double> b {-3.0, 2.0};
    cout << a << " + " << b << " = " << a + b << endl;
    cout << "sqrt(" << a << ") = " << sqrt(a) << endl;
    const size_t v_size {5};
    valarray<complex<double>> v(v_size), w(v_size);
    v[0] = a;
    w[0] = b;
    for (size_t i = 1; i < v_size; i++) {
        v[i] = a*v[i - 1];
        w[i] = b*w[i - 1];
    }
    auto z = v - w;
    for (size_t i = 0; i < z.size(); i++)
        cout << v[i] << " - " << w[i] << " = " << z[i] << endl;
    return 0;
}

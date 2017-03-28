#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<double> init_vector(size_t n);
void update_vector(vector<double>& v);

int main(int argc, char *argv[]) {
    size_t n {10};
    if (argc > 1)
        n = stoi(argv[1]);
    vector<double> v = init_vector(n);
    cout << "first value " << v[0] << " at " << &v[0] << endl;
    cout << "last value " << v[n - 1] << " at " << &v[n - 1] << endl;
    update_vector(v);
    cout << "first value " << v[0] << " at " << &v[0] << endl;
    cout << "last value " << v[n - 1] << " at " << &v[n - 1] << endl;
    cout << "size " << &v[n - 1] - &v[0] + 1 << endl;
    return 0;
}

vector<double> init_vector(size_t n) {
    vector<double> v(n);
    fill(v.begin(), v.end(), 0.0);
    cout << "first value " << v[0] << " at " << &v[0] << endl;
    cout << "last value " << v[n - 1] << " at " << &v[n - 1] << endl;
    return v;
}

void update_vector(vector<double>& v) {
    generate(v.begin(), v.end(),
             [] () { static double x {1.0}; return sqrt(x += 3.0); });
    cout << "first value " << v[0] << " at " << &v[0] << endl;
    cout << "last value " << v[v.size() - 1] << " at "
         << &v[v.size() - 1] << endl;
}

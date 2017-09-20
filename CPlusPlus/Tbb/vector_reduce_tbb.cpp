#include <iostream>
#include <numeric>
#include <tbb/tbb.h>
#include <vector>

using namespace std;

void print_values(const vector<int>& v) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, v.size()),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                    cout << i << ": " << v[i] << endl;
            });
}

vector<int> init_values(size_t n) {
    vector<int> v(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                    v[i] = i*i;
            });
    return v;
}

int sum_values(const vector<int>& v) {
    int sum = tbb::parallel_reduce(
                  tbb::blocked_range<size_t>(0, v.size()),
                  0.0,
                  [&](const tbb::blocked_range<size_t>& r, int init) {
                      return accumulate(
                              v.cbegin() + r.begin(),
                              v.cbegin() + r.end(),
                              init,
                              [](int x, int y) { return x + y; });
                  },
                  [](int x, int y) { return x + y; });
    return sum;
}

int main(int argc, char *argv[]) {
    size_t nv {100};
    if (argc > 1)
        nv = stoi(argv[1]);
    auto v = init_values(nv);
    print_values(v);
    cout << "sum = " << sum_values(v) << endl;
    return 0;
}

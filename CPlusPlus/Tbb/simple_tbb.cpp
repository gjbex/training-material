#include <iostream>
#include <sstream>
#include <tbb/tbb.h>
#include <valarray>

using namespace std;

void print_values(const valarray<int>& v) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, v.size()),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (size_t i = r.begin(); i < r.end(); i++) {
                    string line;
                    stringstream stream(line);
                    stream << i << ": " << v[i] << endl;
                    cout << stream.str();
                }
            });
}

valarray<int> init_values(size_t n) {
    valarray<int> v(n);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n),
            [&] (const tbb::blocked_range<size_t>& r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                    v[i] = i*i;
            });
    return v;
}

int main(int argc, char *argv[]) {
    size_t nv {100};
    if (argc > 1)
        nv = stoi(argv[1]);
    valarray<int> v = init_values(nv);
    print_values(v);
    return 0;
}

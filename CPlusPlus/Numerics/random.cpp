#include <functional>
#include <iostream>
#include <limits>
#include <random>

using namespace std;
using seed_dist_t = uniform_int_distribution<size_t>;

int main() {
    random_device dev;
    seed_dist_t seed_distr(0, numeric_limits<size_t>::max());
    auto seed = seed_distr(dev);
    cout << seed << endl;
    mt19937_64 engine(seed);
    auto die_distr = bind(uniform_int_distribution<int>(1, 6), engine);
    for (int i = 0; i < 5; i++)
        cout << die_distr() << endl;
    return 0;
}

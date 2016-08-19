#include <cstdlib>
#include <functional>
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char *argv[]) {
    mt19937_64::result_type seed = 1234;
    if (argc > 1)
        seed = atoi(argv[1]);
    auto distribution = bind(uniform_real_distribution<double>(0.0, 1.0),
                             mt19937_64(seed));
    int n = 10;
    if (argc > 2)
        n = atoi(argv[2]);
    for (int i = 0; i < n; i++)
        cout << distribution() << endl;
    return 0;
}

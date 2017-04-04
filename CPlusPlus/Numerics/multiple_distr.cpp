#include <functional>
#include <iostream>
#include <random>

using namespace std;

int main() {
    mt19937_64 engine_1(1234);
    auto x_distr_1 = bind(uniform_int_distribution<int>(0, 5), engine_1);
    auto y_distr_1 = bind(uniform_int_distribution<int>(0, 5), engine_1);
    cout << "no ref. wrapper" << endl;
    for (int i = 0; i < 3; i++)
        cout << x_distr_1() << " " << y_distr_1() << endl;
    mt19937_64 engine_2(1234);
    auto x_distr_2 = bind(uniform_int_distribution<int>(0, 5),
                          ref(engine_2));
    auto y_distr_2 = bind(uniform_int_distribution<int>(0, 5),
                          ref(engine_2));
    cout << "ref. wrapper" << endl;
    for (int i = 0; i < 3; i++)
        cout << x_distr_2() << " " << y_distr_2()<< endl;
    return 0;
}

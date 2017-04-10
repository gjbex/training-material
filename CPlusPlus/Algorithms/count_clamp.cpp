#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    const size_t n {10};
    mt19937_64 engine;
    auto distr = bind(uniform_int_distribution<int>(-10, 10), engine);
    vector<int> data;
    for (size_t i = 0; i < n; i++)
        data.push_back(distr());
    cout << "original sequence:" << endl;
    for (const auto& x: data)
        cout << x << " ";
    cout << endl;
    auto nr_pos = count_if(data.cbegin(), data.cend(),
                           [] (int x) { return x > 0; });
    auto nr_neg = count_if(data.cbegin(), data.cend(),
                           [] (int x) { return x < 0; });
    auto nr_zero = count(data.cbegin(), data.cend(), 0);
    cout << "negative: " << nr_neg << endl;
    cout << "zero: " << nr_zero << endl;
    cout << "positive: " << nr_pos << endl;
    cout << "total: " << data.size() << endl;
    cout << "clamp between -5 and 5:" << endl;
    const int pos_max {5};
    const int neg_max {-pos_max};
    replace_if(data.begin(), data.end(),
               [=] (int x) { return x > pos_max; }, pos_max);
    replace_if(data.begin(), data.end(),
               [=] (int x) { return x < neg_max; }, neg_max);
    for (const auto& x: data)
        cout << x << " ";
    cout << endl;
    return 0;
}

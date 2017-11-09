#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    vector<int> v1({3, 5, 7});
    auto sum1 = accumulate(v1.cbegin(), v1.cend(), 0);
    cout << "sum of";
    for (auto value: v1)
        cout << " " << value;
    cout << " = " << sum1 << endl;
    vector<double> v2({3.3, 5.3, 7.4});
    auto sum2 = accumulate(v2.cbegin(), v2.cend(), 0);
    cout << "sum of";
    for (auto value: v2)
        cout << " " << value;
    cout << " = " << sum2 << endl;
    auto sum3 = accumulate(v2.cbegin(), v2.cend(), 0.0);
    cout << "sum of";
    for (auto value: v2)
        cout << " " << value;
    cout << " = " << sum3 << endl;
    return 0;
}

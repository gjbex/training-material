#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << numeric_limits<short>::min() << " < int < "
         << numeric_limits<short>::max() << endl;
    cout << numeric_limits<int>::min() << " < int < "
         << numeric_limits<int>::max() << endl;
    cout << numeric_limits<long>::min() << " < long < "
         << numeric_limits<long>::max() << endl;
    cout << "float < " << numeric_limits<float>::max() << endl;
    cout << "0.0f < " << numeric_limits<float>::min() << endl;
    cout << "1.0f < 1.0f + " << numeric_limits<float>::epsilon() << endl;
    cout << "float digits: " << numeric_limits<float>::digits10 << endl;
    cout << "double < " << numeric_limits<double>::max() << endl;
    cout << "0.0 < " << numeric_limits<double>::min() << endl;
    cout << "1.0 < 1.0 + " << numeric_limits<double>::epsilon() << endl;
    cout << "double digits: " << numeric_limits<double>::digits10 << endl;
    cout << "long double < " << numeric_limits<long double>::max() << endl;
    cout << "0.0 < " << numeric_limits<long double>::min() << endl;
    cout << "1.0 < 1.0 + " << numeric_limits<long double>::epsilon()
         << endl;
    cout << "long double digits: " << numeric_limits<long double>::digits10 << endl;
    double x {1000.0};
    if (!isfinite(exp(x)))
        cout << "exp(" << x << ") is infinity: " << exp(x) << endl;
    x = -1.0;
    if (!isfinite(sqrt(x)))
        cout << "sqrt(" << x << ") is NaN: " << sqrt(x) << endl;
    return 0;
}

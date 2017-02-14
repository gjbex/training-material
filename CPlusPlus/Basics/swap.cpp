#include <iostream>

using namespace std;

void swap(double& x, double& y) {
    double tmp {x};
    x = y;
    y = tmp;
}

void swap(int& x, int& y) {
    int tmp {x};
    x = y;
    y = tmp;
}

int main() {
    double x {3.5};
    double y {5.7};
    cout << x << " <-> " << y << endl;
    swap(x, y);
    cout << "swqpped: " <<  x << " <-> " << y << endl;
    int a {3};
    int b {5};
    cout << a << " <-> " << b << endl;
    swap(a, b);
    cout << "swqpped: " <<  a << " <-> " << b << endl;
    return 0;
}

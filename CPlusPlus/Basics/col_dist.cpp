#include <iostream>
#include <cmath>

using namespace std;

double dist(double x, double y);

int main() {
    double a, b;
    while (cin >> a >> b) {
        cout << dist(a, b) << endl;
    }
    return 0;
}

double dist(double x, double y) {
    return sqrt(x*x + y*y);
}

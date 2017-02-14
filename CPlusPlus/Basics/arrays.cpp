#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

void init_array(double v[], int n);
void print_array(const double v[], int n);
double sum_array(const double v[], int n);

int main() {
    const int n = 10;
    double v[n];
    init_array(v, n);
    print_array(v, n);
    cout << "sum: " << sum_array(v, n) << endl;
    return 0;
}

void init_array(double v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = sqrt((double) i);
}

void print_array(const double v[], int n) {
    cout << fixed;
    for (int i = 0; i < n; i++)
        cout << i + 1 << ": " << setprecision(7) << v[i] << endl;
}

double sum_array(const double v[], int n) {
    double result {0.0};
    for (int i = 0; i < n; i++)
        result += v[i];
    return result;
}

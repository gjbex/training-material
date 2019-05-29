#include <iostream>

class QuadraticFunction {
    private:
        double a_;
        double b_;
        double c_;
    public:
        QuadraticFunction(double a, double b, double c) : a_ {a}, b_ {b}, c_ {c} {}
        double operator()(const double x) { return (a_*x + b_)*x + c_; }
};

int main() {
    QuadraticFunction f1(1.0, 0.0, -1.0);
    QuadraticFunction f2(-1.0, 3.0, 0.0);
    for (double x = -3.0; x <= 3.0; x += 0.2)
        std::cout << x << " " << f1(x) << " " << f2(x) << "\n";
    return 0;
}

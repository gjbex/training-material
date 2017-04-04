#include <armadillo>
#include <iostream>

using namespace arma;

int main() {
    mat A {{1.0, 2.0}, {3.0, 4.0}};
    A.print("A:");
    mat B {{0.5, 1.0}, {-0.5, -1.0}};
    B.print("B:");
    colvec x {5.0, 6.0};
    x.print("x:");
    colvec y = (2.0*A + B)*x;
    y.print("(2A+B)*x:");
    return 0;
}

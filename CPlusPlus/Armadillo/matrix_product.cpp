#include <armadillo>
#include <iostream>

using namespace arma;

int main() {
    mat A(3, 2, fill::randn);
    A.print("A:");
    mat B(2, 4, fill::randn);
    B.print("B:");
    mat C = A*B;
    C.print("A*B:");
    return 0;
}

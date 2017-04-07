#include <armadillo>
#include <iostream>

using namespace arma;
using namespace std;

int main() {
    mat A {{1.0, 2.0}, {3.0, 4.0}};
    A.print("A:");
    mat B = A*A.i();
    B.print("B:");
    mat C = eye<mat>(2, 2);
    C.print("C:");
    cout << "abs. sum: " <<  accu(abs(B - C)) << endl;
    return 0;
}

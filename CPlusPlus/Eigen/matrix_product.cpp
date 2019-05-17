#include <Eigen/Dense>
#include <iostream>

int main() {
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(3, 2);
    std::cout << "A =" << std::endl << A << std::endl;
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(2, 3);
    std::cout << "B =" << std::endl << B << std::endl;
    Eigen::MatrixXd C = A*B;
    std::cout << "C =" << std::endl << C << std::endl;
    return 0;
}

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Eigen::MatrixXd read_matrix(std::string file_name);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "# error: no file specified" << std::endl;
        return 1;
    }
    Eigen::MatrixXd A = read_matrix(std::string(argv[1]));
    std::cout << "A =" << std::endl << A << std::endl;
    return 0;
}

Eigen::MatrixXd read_matrix(std::string file_name) {
    std::size_t nr_rows {0};
    std::vector<double> elements;
    std::size_t nr_cols {0};
    std::ifstream ifs(file_name);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream str(line);
        double val;
        std::size_t nr_vals {0};
        while (str >> val) {
            elements.push_back(val);
            ++nr_vals;
        }
        if (nr_cols == 0) {
            nr_cols = nr_vals;
        } else  if (nr_vals > 0 && nr_vals != nr_cols) {
            std::cerr << "Error: incorrect file format" << std::endl;
            std::exit(1);
        }
        if (nr_vals > 0)
            ++nr_rows;
    }
    ifs.close();
    Eigen::MatrixXd matrix(nr_rows, nr_cols);
    for (long i = 0; i < matrix.rows(); ++i)
        for (long j = 0; j < matrix.cols(); ++j)
            matrix(i, j) = elements[i*matrix.cols() + j];
    return matrix;
}

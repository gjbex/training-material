#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    vector<double> u(3), v(3);
    for (unsigned i = 0; i < v.size (); ++ i) {
        u(i) = 3*i + 1;
        v(i) = i;
    }
    std::cout << u << std::endl << v << std::endl;
    double t = inner_prod(u, v);
    std::cout << t << std::endl;
    return 0;
}

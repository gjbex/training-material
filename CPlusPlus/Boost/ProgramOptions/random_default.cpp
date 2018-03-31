#include <boost/program_options.hpp>
#include <iostream>
#include <random>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    const int default_n {1};
    int n;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("n", po::value<int>(&n)->default_value(default_n),
         "number of random values to generate")
    ;

    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> distr(0.0, 1.0);
    for (int i = 0; i < n; ++i)
        std::cout << distr(engine) << std::endl;

    return 0;
}

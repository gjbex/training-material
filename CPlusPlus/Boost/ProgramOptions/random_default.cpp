#include <boost/program_options.hpp>
#include <iostream>
#include <random>

namespace po = boost::program_options;

using Options = std::tuple<int, double, double, size_t>;

Options get_options(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    int n;
    double a, b;
    size_t seed;
    std::tie(n, a, b, seed) = get_options(argc, argv);

    std::mt19937 engine(seed);
    std::uniform_real_distribution<double> distr(a, b);
    for (int i = 0; i < n; ++i)
        std::cout << distr(engine) << std::endl;

    return 0;
}

Options get_options(int argc, char* argv[]) {
    const int default_n {1};
    const double default_a {0.0};
    const double default_b {1.0};
    int n;
    double a, b;
    size_t seed;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("n", po::value<int>(&n)->default_value(default_n),
         "number of random values to generate")
        ("a", po::value<double>(&a)->default_value(default_a),
         "minimum value")
        ("b", po::value<double>(&b)->default_value(default_b),
         "maximum value")
        ("seed", po::value<size_t>(&seed), "seed to use")
    ;
    po::positional_options_description pos_desc;
    pos_desc.add("n", -1);

    po::variables_map vm;        
    po::store(po::command_line_parser(argc, argv)
                  .options(desc).positional(pos_desc).run(), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        std::exit(0);
    }

    if (!vm.count("seed")) {
        std::random_device device;
        seed = device();
    }
    return std::make_tuple(n, a, b, seed);
}

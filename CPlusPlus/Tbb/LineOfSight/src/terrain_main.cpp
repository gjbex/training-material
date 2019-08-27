#include <boost/program_options.hpp>
#include <iomanip>
#include <iostream>

#include "terrain.h"

namespace po = boost::program_options;

auto get_arguments(int argc, char* argv[]) {
    size_t n {20};
    double distance {30.0};
    double delta_mean {0.02};
    double delta_stddev {0.05};
    double flat_fraction {0.2};
    Seed_t seed {1234};

    po::options_description desc("Create random terrain");
    desc.add_options()
        ("help", "show help message")
        ("n", po::value<size_t>(), "number of points in terrain")
        ("distance", po::value<double>(), "distance of the terrain")
        ("delta_mean", po::value<double>(), "mean altitude change per point")
        ("delta_stddev", po::value<double>(), "standard deviation altitude change per point")
        ("flat_fraction", po::value<double>(), "fraction of the terrain that is flat")
        ("seed", po::value<Seed_t>(), "seed for the random number generator")
    ;
    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            std::exit(0);
        }
        if (vm.count("n"))
            n = vm["n"].as<size_t>();
        if (vm.count("distance"))
            distance = vm["distance"].as<double>();
        if (vm.count("delta_mean"))
            delta_mean = vm["delta_mean"].as<double>();
        if (vm.count("delta_stddev"))
            delta_stddev = vm["delta_stddev"].as<double>();
        if (vm.count("flat_fraction"))
            flat_fraction = vm["flat_fraction"].as<double>();
        if (vm.count("seed"))
            seed = vm["seed"].as<Seed_t>();
    } catch(std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        std::exit(1);
    }

    return std::make_tuple(n, distance, delta_mean, delta_stddev,
                           flat_fraction, seed);
}

int main(int argc, char* argv[]) {
    auto [n, distance, delta_mean, delta_stddev,
          flat_fraction, seed] = get_arguments(argc, argv);
    Terrain terrain(n, distance, delta_mean, delta_stddev, flat_fraction, seed);
    std::cout << terrain;
    return 0;
}

#include <iostream>
#include <memory>

#include "stats.h"
#include "median_stats.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<Stats> stats {nullptr};
    if (argc == 1) {
        stats = std::make_unique<Stats>();
    } else if (argc == 2) {
        std::string arg(argv[1]);
        if (arg != "-m") {
            std::cerr << "### error: unknown command line option '"
                      << arg << "'" << std::endl;
            std::exit(1);
        }
        stats = std::make_unique<MedianStats>();
    } else {
        std::cerr << "### usage: stats.exe [-m]" << std::endl;
        std::exit(1);
    }
    std::cerr << "before parse: " << *stats << std::endl;
    double value;
    while (std::cin >> value)
        stats->add(value);
    std::cerr << "after parse: " << *stats << std::endl;
    try {
        std::cout << "mean: " << stats->mean() << std::endl;
        std::cout << "stddev: " << stats->stddev() << std::endl;
        std::cout << "min: " << stats->min() << std::endl;
        std::cout << "max: " << stats->max() << std::endl;
        {
            MedianStats* mstats = dynamic_cast<MedianStats*>(stats.get());
            if (mstats)
                std::cout << "median: " << mstats->median() << std::endl;
        }
        std::cout << "n: " << stats->nr_values() << std::endl;
    } catch (std::out_of_range& e) {
        std::cerr << "### error: " << e.what() << std::endl;
        std::exit(2);
    }
    return 0;
}

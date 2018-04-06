#include <iostream>

#include "rng_builder.h"

int main() {
    const int nr_runs {3};
    Rng_builder rng_builder;
    std::cout << "first run" << std::endl;
    auto rng1 = rng_builder.lower(-0.5).upper(0.5).seed(123).build();
    auto rng2 = rng_builder.lower(-0.5).upper(0.5).seed(123).build();
    for (int i = 0; i < nr_runs; ++i)
        std::cout << rng1() << std::endl;
    for (int i = 0; i < nr_runs; ++i)
        std::cout << rng2() << std::endl;
    std::cout << "second run" << std::endl;
    for (int i = 0; i < nr_runs; ++i)
        std::cout << rng1() << std::endl;
    for (int i = 0; i < nr_runs; ++i)
        std::cout << rng2() << std::endl;
    return 0;
}

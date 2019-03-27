#include <iostream>
#include <memory>
#include <random>

using Seed_t = std::mt19937_64::result_type;

class MultiDistr {
    private:
        std::unique_ptr<std::mt19937_64> engine_;
        std::uniform_int_distribution<int> distr1_;
        std::uniform_int_distribution<int> distr2_;
    public:
        MultiDistr(int a, int b, Seed_t seed);
        int generate(int choose);
};

MultiDistr::MultiDistr(int a, int b, Seed_t seed = 1234) {
    engine_ = std::make_unique<std::mt19937_64>(seed);
    distr1_ = std::uniform_int_distribution<int>(a, b);
    distr2_ = std::uniform_int_distribution<int>(a, b);
}

int MultiDistr::generate(int choose) {
    switch (choose) {
        case 1:
            return distr1_(*engine_);
            break;
        case 2:
            return distr2_(*engine_);
            break;
        default:
            std::cerr << "choose 1 or 2" << std::endl;
            return -1;
    }
}

int main(int argc, char* argv[]) {
    std::unique_ptr<MultiDistr> distrs;
    if (argc > 1)
        distrs = std::make_unique<MultiDistr>(0, 5, std::stoul(argv[1]));
    else
        distrs = std::make_unique<MultiDistr>(0, 5);
    for (int i = 0; i < 10; ++i) {
        std::cout << "1: " << distrs->generate(1) << std::endl;
        std::cout << "2: " << distrs->generate(2) << std::endl;
    }
    return 0;
}

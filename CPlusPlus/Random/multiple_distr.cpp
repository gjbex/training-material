#include <iostream>
#include <random>

class MultiDistr {
    private:
        std::mt19937_64* _engine;
        std::uniform_int_distribution<int> _distr1;
        std::uniform_int_distribution<int> _distr2;
    public:
        MultiDistr(int a, int b);
        ~MultiDistr();
        int generate(int choose);
};

MultiDistr::MultiDistr(int a, int b) {
    _engine = new std::mt19937_64(1234);
    _distr1 = std::uniform_int_distribution<int>(a, b);
    _distr2 = std::uniform_int_distribution<int>(a, b);
};

MultiDistr::~MultiDistr() {
    delete _engine;
};

int MultiDistr::generate(int choose) {
    switch (choose) {
        case 1:
            return _distr1(*_engine);
            break;
        case 2:
            return _distr2(*_engine);
            break;
        default:
            std::cerr << "choose 1 or 2" << std::endl;
            return -1;
    }
}

int main() {
    MultiDistr distrs(0, 5);
    for (int i = 0; i < 10; i++) {
        std::cout << "1: " << distrs.generate(1) << std::endl;
        std::cout << "2: " << distrs.generate(2) << std::endl;
    }
    return 0;
}

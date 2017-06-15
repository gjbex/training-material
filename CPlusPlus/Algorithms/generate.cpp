#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
class Incr_initializer {
    private:
        T _val;
        T _incr;
    public:
        Incr_initializer(T init, T incr) : _val {init}, _incr {incr} {};
        T operator()() { T val = _val; _val += _incr; return val; };
};

int main() {
    std::vector<int> v1(10);
    Incr_initializer<int> incr1(0, 1);
    std::generate(v1.begin(), v1.end(), incr1);
    for (auto i: v1)
        std::cout << i << " ";
    std::cout << std::endl;
    std::vector<double> v2(10);
    Incr_initializer<double> incr2(1.0, 0.1);
    std::generate(v2.begin(), v2.end(), incr2);
    for (auto x: v2)
        std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}

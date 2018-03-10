#include <iostream>
#include <limits>
#include <map>

class Stats {
    private:
        int _n {0};
        double _sum {0.0};
        double _min {std::numeric_limits<double>::max()};
        double _max {std::numeric_limits<double>::min()};
    public :
        void add(double x);
        double avg() const { return _sum/_n; };
        double min() const { return _min; };
        double max() const { return _max; };
};

void Stats::add(double x) {
    ++_n;
    _sum += x;
    _min = std::min(_min, x);
    _max = std::max(_max, x);
};

int main() {
    int i {0};
    double x {0.0};
    std::map<int,Stats> data;
    while (std::cin >> i >> x) {
        if (data.find(i) == data.end())
            data.emplace(std::make_pair(i, Stats()));
        data[i].add(x);
    }
    for (const auto& values: data) {
        Stats stats = values.second;
        std::cout << values.first << " " << stats.avg() << " "
                  << stats.min() << " " << stats.max() << std::endl;
    }
    return 0;
}

#include <iostream>

class Stats {

    private:
        double _sum;
        int _n;

    public:
        Stats() : _sum {0.0}, _n {0} {};
        int n() const { return _n; };
        double avg() const { return _sum/_n; };
        void add(double data);
};

void Stats::add(double data) {
    _sum += data;
    _n++;
}

int main() {
    const int n {5};
    double data[n] {1.2, 2.3, 3.4, 4.5, 5.6};
    Stats stats;
    for (int i = 0; i < n; i++)
        stats.add(data[i]);
    std::cout << "average = " << stats.avg() << " for "
              << stats.n() << " data points" << std::endl;
    return 0;
}

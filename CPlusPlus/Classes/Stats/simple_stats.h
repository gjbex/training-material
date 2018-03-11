#ifndef SIMPLE_STATS_HDR
#define SIMPLE_STATS_HDR

#include <iostream>

class SimpleStats {
    private:
        double _sum;
        int _n;
    public:
        SimpleStats() : _sum {0.0}, _n {0} {};
        void add(double x) { _sum += x; _n++; };
        double sum() const { return _sum; };
        int n() const { return _n; };
        double mean() const { return sum()/n(); };
        friend std::ostream& operator<<(std::ostream& out,
                                        const SimpleStats& stats);
};

#endif

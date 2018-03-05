#ifndef STATS_H
#define STATS_H

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

#endif

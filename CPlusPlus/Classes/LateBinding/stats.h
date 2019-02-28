#ifndef STATS_HDR
#define STATS_HDR

#include <iostream>
#include <limits>

class Stats {
    protected:
        double sum_;
        double sum2_;
        double min_;
        double max_;
        size_t nr_values_;
    public:
        Stats() : sum_ {0.0}, sum2_ {0.0},
                  min_ {std::numeric_limits<double>::max()},
                  max_ {std::numeric_limits<double>::min()},
                  nr_values_ {0} {}
        size_t nr_values() const { return nr_values_; }
        double mean() const;
        double stddev() const;
        double min() const;
        double max() const;
        virtual void add(const double value);
        virtual std::string to_str() const;
        virtual ~Stats() = default;
        friend std::ostream& operator<<(std::ostream& out,
                                        const Stats& stats);
    protected:
        void check_size(size_t n) const;
};

#endif

#include "stats.h"

void Stats::add(double data) {
    _sum += data;
    _n++;
}

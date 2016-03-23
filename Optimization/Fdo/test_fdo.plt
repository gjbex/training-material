#!/usr/bin/env gnuplot

set datafile separator ","
set logscale x 2
plot 'cache_hierarchy_O3.txt' using 1:2 with lines linetype rgb 'blue' title '-O3', \
     'cache_hierarchy_O3_FDO.txt' using 1:2 with lines linetype rgb 'red' title '-O3 -fprofile-use'

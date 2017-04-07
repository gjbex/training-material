#!/usr/bin/gnuplot -persist

set size square
unset key
set xrange [0:2047]
set yrange [0:2047]

plot 'julia.txt' matrix with image

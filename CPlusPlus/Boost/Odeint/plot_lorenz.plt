#!/usr/bin/gnuplot -persist

set size square
unset key
set xlabel 'x'
set ylabel 'z'
plot 'lorenz.txt' using 2:4 with lines linetype rgb 'red'

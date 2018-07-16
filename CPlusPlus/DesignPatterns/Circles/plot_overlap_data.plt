#!/usr/bin/gnuplot -persist

set key off
set xlabel 'nr. points'
set ylabel 'fraction overlap'
plot 'overlap_data.txt' using 1:($2/$1) with point pointtype 7 pointsize 0.3

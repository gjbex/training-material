#!/usr/bin/env bash

# check whether there is at least one argument given
if [ "$#" -eq 0 ]
then
    (>&2 echo "### error: no data file name given")
    exit 1
fi
file="$1"

# determine size of image
y_size=$(wc -l $file | cut -d ' ' -f 1)
words=$(wc -w $file | cut -d ' ' -f 1)
x_size=$(( $words / $y_size ))

# plot the Julia set
gnuplot -persist <<- EOI
    set size square
    unset key
    set xrange [0:$(( $x_size - 1))]
    set yrange [0:$(( $y_size - 1))]
    plot "$file" matrix with image
EOI

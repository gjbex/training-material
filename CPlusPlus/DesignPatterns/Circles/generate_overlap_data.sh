#!/usr/bin/env bash

radius=0.01
for nr_circles in $(seq 50 50 10000)
do
    for nr_avg in $(seq 1 50)
    do
        seed=$RANDOM
        ./random_circles.exe ${nr_circles} ${radius} ${seed} | \
            ./circle_overlap.exe
    done
done

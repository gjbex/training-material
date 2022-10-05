#!/usr/bin/env bash

export name
export number
for name in 'alice' 'bob'
do
    for number in $(seq 1 3)
    do
        envsubst < template.txt
        echo '#----'
    done
done

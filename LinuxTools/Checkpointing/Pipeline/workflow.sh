#!/bin/bash

nr_iters=$(( 12*60*100 ))
./producer.exe $nr_iters 1 | ./consumer.exe $nr_iters > dump.txt

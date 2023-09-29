#!/bin/bash
gcc -fopenmp mm_seq.cpp -lstdc++ -o mms
for i in 10 50 100 500 1000
do
    ./mms $i
done

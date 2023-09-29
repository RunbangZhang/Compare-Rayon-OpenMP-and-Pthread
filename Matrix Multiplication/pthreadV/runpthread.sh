#!/bin/bash
gcc -pthread -fopenmp mm_pthread.cpp -lstdc++ -o mmp
for size in 10 50 100 500 1000
do
    for thread in 2 4 8 16 32 64
    do 
        ./mmp $size $thread
    done
done


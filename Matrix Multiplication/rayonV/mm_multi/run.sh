#!/bin/bash
for size in 10 50 100 500 1000
do 
    for thread in 2 4 8 16 32 64
    do 
	   cargo run $size $thread
    done
done

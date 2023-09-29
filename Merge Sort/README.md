This is the README.txt for Merge Sort directory.

The seq_c.c is the sequential program of the merge sort in c.
To compile it, use command "gcc -fopenmp -o seq_c seq_c.c", to run it, using "./seq_c",
you can modify the value of n in line 73 to control the problem size.

The openmp.c is the program of the merge sort parallelized using openmp.
To compile it, make sure load gcc-12.2, by using "module load gcc-12.2",
use command "gcc -fopenmp -o openmp openmp.c", to run it, using "./openmp", 
To change the number of threads been used, change the num_threads value in line 71,
to change the number of problem size, change the value of n in line 87.

The pthread.c is the program of the merge sort parallelized using pthread.
To compile it, use "module load gcc-12.2", and then "gcc -pthread -fopenmp -o pthread pthread.c".
To change the number of threads used, change the value of NUM_THREADS in line 8.
To change the number of problem size, change the value of LENGTH in line 7.

To run the Rust sequential version of the merge sort, "cd /Rayon_Seq/src", and use "cargo run".
To change the number of problem size, change the value in line 35, 37, and 45.

To run the Rust parallel version of the merge sort, "cd /Rayon_Parallel/src", and use "cargo run".
To change the number of problem size, change the value in line 44, 46, and 54.
To change the number of threads, change the value in line 57.
We get Matrix Multiplication Algorithm for three library inlcuding OpenMP, Pthreads and Rayon. Please make sure  the environment is set up before running in cims.

- Environment Setup:
	1. module load gcc-12.2 for openmp and pthreads
	2. make sure rust is installed using $ curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh

- To execute the code seperately:
	1. For openmp sequential version, compile using `gcc -fopenmp mm_seq.cpp -lstdc++ -o mms`, and run use `./mms YourProblemSize` under openmpV directory.
	2. For openmp multithread version, compile using `gcc -fopenmp mm_openmp.cpp -lstdc++ -o mmo`, and run use `./mmo YourProblemSize YourThreadNumber` under openmpV directory.
	3. For pthreads sequential version, compile using `gcc -fopenmp mm_seq.cpp -lstdc++ -o mms`, and run use `./mms YourProblemSize` under pthreadV directory.
	4. For pthreads multithread version, compile using `gcc -pthread -fopenmp mm_pthread.cpp -lstdc++ -o mmp`, and run use `./mmp YourProblemSize YourThreadNumber` under pthreadV directory.
	5. For rayon sequential version, run directly using `cargo run YourProblemSize` under rayon/mm_seq directory.
	6. For rayon multithread version, run directly using `cargo run YourProblemSize YourThreadNumber` under rayon/mm_multi directory.

- To execute code in batch: it will execute threads from 2~64 and problem size from 10~1000 under two nested loops.
	1. For openmp and pthread, go into openmpV or pthreadV directory, run the `./run.sh`(sequential) or `./runxxx.sh`(Multithread) correspondingly, where "xxx" means the version you want to run. 
	2. For rayon, go into the mm_seq and mm_multi, and run `./run.sh`.


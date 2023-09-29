- Environment Setup:

  1. module load gcc-12.2 for openmp and pthreads
  2. make sure rust is installed using $ curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh

- To execute the code:

  1. Firstly compile `random_matrix.cpp` using `g++ -fopenmp random_matrix.cpp -o random_matrix` and run use `./random_matrix m` to produce a `lu_input.txt` file which contains a square matrix of size `m`.
  
  2. For openmp and pthreads sequential version, compile using `g++ -fopenmp lu_seq.cpp -o lu_seq`, and run use `./lu_seq m "lu_input.txt"   `  where `m` specifies the size of input matrix.

  3. For openmp parallel version, compile using `g++ -fopenmp lu_openmp.cpp -o lu_openmp`, and run use `./lu_openmp m "lu_input.txt" t  `  where `m` specifies the size of input matrix and `t` specifies the number of threads to be used.
  
  4. For pthreads parallel version, compile using `g++ -fopenmp lu_pthread.cpp -o lu_pthread`, and run use `./lu_pthread m "lu_input.txt" t  `  where `m` specifies the size of input matrix and `t` specifies the number of threads to be used.
  
  5. For rayon sequential version, go to `./rust` directory and run directly using `cargo run m 'lu_input.txt' t ` where `m` specifies the size of input matrix and `t` specifies the number of threads to be used. Remeber to make input matrix file using `./random_matrix` ahead of time.
  
     
  
  
  
  
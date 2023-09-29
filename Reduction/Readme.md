- Environment Setup:

  1. module load gcc-12.2 for openmp and pthreads
  2. make sure rust is installed using $ curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh

- To execute the code:

  1. For openmp sequential and parallel version, compile using `g++ -fopenmp reduce.cpp -o reduce`, and run use `./reduce -n [problem_size] -t [thread_number]  ` under current directory.
  2. For pthreads sequential and parallel version, compile using `g++ -fopenmp -pthread preduce.cpp -o preduce`, and run use `./preduce -n [problem_size] -t [thread_number]  ` under current directory.
  3. For rayon sequential version, go to `./rust` directory and run directly using `cargo run -- -n [problem_size] -t [thread_number] ` .

  
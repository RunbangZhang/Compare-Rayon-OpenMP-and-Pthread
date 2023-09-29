#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>
#include <vector>

using namespace std;

vector<vector<int>> A;
vector<vector<int>> B;
vector<vector<int>> C;

struct ARGS {
    int start;
    int end;
    int N;
};

void* matrix_multiply(void* input) {
    int start = ((struct ARGS*)input)->start;
    int end = ((struct ARGS*)input)->end;
    int N = ((struct ARGS*)input)->N;

    for (int i = start; i < end; ++i) {
    	for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];   
            }   
        }
    }
}

int main(int argc, const char* argv[]) {
    
    const int RANGE = 100;
    int thread_count = 10;
    int N = 100;

    if (argc > 2) {
        N = atoi(argv[1]);
        thread_count = atoi(argv[2]);
    }

    A.resize(N);
    B.resize(N);
    C.resize(N);
    for (int i = 0; i < N; ++i) {
        A[i].resize(N);
        B[i].resize(N);
        C[i].resize(N);
    }

    int i, j, k;
    time_t t;
    srand((unsigned) time(&t));    

    for (i = 0; i < N; ++i) {
    	for (j = 0; j < N; ++j) {
    	    A[i][j] = rand() % RANGE;
    	    B[i][j] = rand() % RANGE;
    	}
    }

    pthread_t threads[thread_count];

    int size = N / thread_count;

    double startTime = omp_get_wtime();

    for (i = 0; i < thread_count; ++i) {
    	int start = i * size;
    	int end = (i == thread_count - 1) ? N - 1 : (i + 1) * size;
    	struct ARGS arg;
    	arg.start = start;
    	arg.end = end; 
        arg.N = N;
    	pthread_create(&threads[i], NULL, matrix_multiply, (void*)(&arg));
    }

    for (i = 0; i < thread_count; ++i) {
	   pthread_join(threads[i], NULL);	
    }

    double endTime = omp_get_wtime();

    printf("Thread Number: %d, Task %d\n", thread_count, N);
    printf("Program Time:  %f\n\n", endTime - startTime);

    return 0;
}

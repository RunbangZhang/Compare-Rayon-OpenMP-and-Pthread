#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <vector>

using namespace std;

int main(int argc, const char* argv[]) {

	const int RANGE = 100;

	int N = 100;
    
	if (argc > 1) {
		N = atoi(argv[1]);
	}

	vector<vector<int>> A(N, vector<int>(N, 0));
	vector<vector<int>> B(N, vector<int>(N, 0));
	vector<vector<int>> C(N, vector<int>(N, 0));

    int i, j, k;
    time_t t;
    srand((unsigned) time(&t));    

    for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
		    A[i][j] = rand() % RANGE;
		    B[i][j] = rand() % RANGE;
		}
    }

    double startTime = omp_get_wtime();

    for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
		    for (k = 0; k < N; ++k) {
				C[i][j] += A[i][k] * B[k][j];	
		    }   
		}
    }

    double endTime = omp_get_wtime();

    printf("Program Time for %d:  %f\n", N, endTime - startTime);

    return 0;
}

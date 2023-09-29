#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#define MAX_NUM_THREADS 300

typedef struct {
    int start;
    int end;
    int k;
    int n;
    float **A;
    float **L;
    float **U;

} ThreadData;


ThreadData data[MAX_NUM_THREADS];

void *compute_L_and_U(void *arg);
void *update_A(void *arg);

void LU_factorization_parallel(int n, float **A, float **L, float **U, int num_threads) {
    pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    for (int i = 0; i < num_threads; i++){
        data[i].A = A;
        data[i].L = L;
        data[i].U = U;
        data[i].n = n;
    }

    for (int k = 0; k < n; k++) {

        U[k][k] = A[k][k]; 
        
        for (int i = 0; i < num_threads; i++) {
            data[i].start = k+1 + i*(n-k-1)/num_threads;
            data[i].end = k+1 + (i+1)*(n-k-1)/num_threads;
            data[i].k = k;
            pthread_create(&threads[i], NULL, compute_L_and_U, (void *)&data[i]);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, update_A, (void *)&data[i]);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    }
    free(threads);
}

void *compute_L_and_U(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start = data->start;
    int end = data->end;
    int n = data->n;
    int k = data->k;
    float **A = data->A;
    float **L = data->L;
    float **U = data->U;


    for (int i = start; i < end; i++) {
        L[i][k] = A[i][k] / U[k][k];
        U[k][i] = A[k][i];
    }
    return NULL;
}

void *update_A(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int start = data->start;
    int end = data->end;
    int n = data->n;
    int k = data->k;
    float **A = data->A;
    float **L = data->L;
    float **U = data->U;

    for (int i = start; i < end; i++) {
        for (int j = k + 1; j < n; j++) {
            A[i][j] = A[i][j] - L[i][k] * U[k][j];
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int n, i, j, num_threads;
    float **A, **L, **U;
    FILE *fp_in, *fp_L, *fp_U;

    if (argc != 4) {
        printf("Usage: %s size filename num_threads\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        printf("Size must be positive.\n");
        return 1;
    }

    num_threads = atoi(argv[3]);
    if (num_threads <= 0) {
        printf("Number of threads must be positive.\n");
        return 1;
    }

    // Allocate memory for matrices
    A = (float **) malloc(n * sizeof(float *));
    L = (float **) malloc(n * sizeof(float *));
    U = (float **) malloc(n * sizeof(float *));
    for (i = 0; i < n; i++) {
        A[i] = (float *) malloc(n * sizeof(float));
        L[i] = (float *) malloc(n * sizeof(float));
        U[i] = (float *) malloc(n * sizeof(float));
    }

    // Read matrix from file
    fp_in = fopen(argv[2], "r");
    if (fp_in == NULL) {
        printf("Could not open file %s for reading.\n", argv[2]);
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (fscanf(fp_in, "%f", &A[i][j]) != 1) {
                printf("Error reading matrix from file.\n");
                fclose(fp_in);
                return 1;
            }
        }
    }

    fclose(fp_in);
    double start, end;
    start = omp_get_wtime();
    // Perform LU factorization
    LU_factorization_parallel(n, A, L, U, num_threads);
    end = omp_get_wtime(); 
    printf("Work took %f seconds\n", end - start);

    // Write L matrix to file
    fp_L = fopen("output_pthread_L.txt", "w");
    if (fp_L == NULL) {
        printf("Could not open file output_pthread_L.txt for writing.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp_L, "%f ", L[i][j]);
        }
        fprintf(fp_L, "\n");
    }

    fclose(fp_L);

    // Write U matrix to file
    fp_U = fopen("output_pthread_U.txt", "w");
    if (fp_U == NULL) {
        printf("Could not open file output_pthread_U.txt for writing.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp_U, "%f ", U[i][j]);
        }
        fprintf(fp_U, "\n");
    }
}
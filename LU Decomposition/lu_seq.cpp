#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void LU_factorization(int n, float **A, float **L, float **U) {
    int i, j, k;

    // Perform Gaussian elimination
    for (k = 0; k < n; k++) {
        U[k][k] = A[k][k];
        for (i = k + 1; i < n; i++) {
            L[i][k] = A[i][k] / U[k][k];
            U[k][i] = A[k][i];
        }
        for (i = k + 1; i < n; i++) {
            for (j = k + 1; j < n; j++) {
                A[i][j] = A[i][j] - L[i][k] * U[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n, i, j;
    float **A, **L, **U;
    FILE *fp_in, *fp_L, *fp_U;

    if (argc != 3) {
        printf("Usage: %s size filename\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        printf("Size must be positive.\n");
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

    // Initialize L and U matrices
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                L[i][j] = 1;
            } else {
                L[i][j] = 0;
            }
            U[i][j] = 0;
        }
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
    LU_factorization(n, A, L, U);
    end = omp_get_wtime(); 
    printf("Work took %f seconds\n", end - start);


    // Write L matrix to file
    fp_L = fopen("output_seq_L.txt", "w");
    if (fp_L == NULL) {
        printf("Could not open file output_seq_L.txt for writing.\n");
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
    fp_U = fopen("output_seq_U.txt", "w");
    if (fp_U == NULL) {
        printf("Could not open file output_seq_LU.txt for writing.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp_U, "%f ", U[i][j]);
        }
        fprintf(fp_U, "\n");
    }
}


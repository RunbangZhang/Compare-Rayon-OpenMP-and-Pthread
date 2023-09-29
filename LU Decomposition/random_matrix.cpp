#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int n, i, j;
    float **A;
    FILE *fp;

    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        printf("Size must be positive.\n");
        return 1;
    }

    // Allocate memory for matrix
    A = (float **) malloc(n * sizeof(float *));
    for (i = 0; i < n; i++) {
        A[i] = (float *) malloc(n * sizeof(float));
    }

    // Generate random matrix
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = (float) (rand() % 10);
        }
    }

    // Write matrix to file
    fp = fopen("lu_input.txt", "w");
    if (fp == NULL) {
        printf("Could not open file lu_input.txt for writing.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(fp, "%f ", A[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    // Free memory
    for (i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}

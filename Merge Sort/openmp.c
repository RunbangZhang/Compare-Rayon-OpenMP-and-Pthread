#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

int min(int a, int b) {
    return (a < b ? a : b);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectionsort(int* v, int low, int high) {
    int i, j;
    for (i=low; i<high; i++) {
        for (j=i+1; j<=high; j++) {
            if (v[i] > v[j]) {
                swap(&v[i], &v[j]);
            }
        }
    }
}

void merge(int* src, int low, int mid, int high, int* dst)
{
    int i=low, j=mid+1, k=low;
    while (i<=mid && j<=high) {
        if (src[i] <= src[j]) {
            dst[k] = src[i++];
        } else {
            dst[k] = src[j++];
        }
        k++;
    }
    /* Handle leftovers */
    while (i<=mid) {
        dst[k] = src[i++];
        k++;
    }
    while (j<=high) {
        dst[k] = src[j++];
        k++;
    }
}

void mergesort_rec(int *v, int i, int j, int *tmp)
{
    const int CUTOFF = 64;
    if (j - i + 1 < CUTOFF)
        selectionsort(v, i, j);
    else
    {
        const int m = (i + j) / 2;
        #pragma omp task shared(v, i, m, tmp)
        mergesort_rec(v, i, m, tmp);
        #pragma omp task shared(v, j, m, tmp)
        mergesort_rec(v, m + 1, j, tmp);
        #pragma omp taskwait
        merge(v, i, m, j, tmp);
        memcpy(v + i, tmp + i, (j - i + 1) * sizeof(v[0]));
    }
}

void mergesort_main(int *v, int n)
{
    int* tmp = (int*)malloc(n*sizeof(v[0]));
    #pragma omp parallel num_threads(1) default(none) shared(v,tmp,n)
    #pragma omp single
    mergesort_rec(v, 0, n-1, tmp);
    free(tmp);
}

int* generate_random_array(int size) {
    int* arr = malloc(size * sizeof(int)); 
    srand(time(NULL)); 
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; 
    }
    return arr;
}

int main( int argc, char* argv[]) {
    int n = 10000000;

    int *a = generate_random_array(n);

    double start = omp_get_wtime();

    mergesort_main(a, n);

    double end = omp_get_wtime();

    printf("Time: %f\n", end - start);

    free(a);

    return EXIT_SUCCESS;
}
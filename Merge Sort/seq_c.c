#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void merge(int *a, int l, int r, int n) {
    int *b = (int *)malloc(n * sizeof(int));
    if (b == NULL) {
        printf("Can't Malloc! Please try again.");
        exit(EXIT_FAILURE);
    }
    int c = l;
    int p1, p2;
    p1 = l;
    p2 = ((l + r) / 2) + 1;
    while ((p1 < ((l + r) / 2) + 1) && (p2 < r + 1)) {
        if (a[p1] <= a[p2]) {
            b[c++] = a[p1];
            p1++;
        }
        else {
            b[c++] = a[p2];
            p2++;
        }
    }

    if (p2 == r + 1) {
        while ((p1 < ((l + r) / 2) + 1)) {
            b[c++] = a[p1];
            p1++;
        }
    } else {
        while ((p2 < r + 1)) {
            b[c++] = a[p2];
            p2++;
        }
    }

    for (c = l; c < r + 1; c++) a[c] = b[c];

    free(b);
}

void merge_sort(int *a, int n, int l, int r) {
    if (r - l == 1) {
        if (a[l] > a[r])
            swap(&a[l], &a[r]);
    } else if (l != r) {
        merge_sort(a, n, l, (l + r) / 2);
        merge_sort(a, n, ((l + r) / 2) + 1, r);
        merge(a, l, r, n);
    }
}

int* generate_random_array(int size) {
    int* arr = malloc(size * sizeof(int)); 
    srand(time(NULL)); 
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; 
    }
    return arr;
}

int main(void) {
    int *a, i;
    int n = 1000000;
    a = generate_random_array(n);

    double start = omp_get_wtime();

    merge_sort(a, n, 0, n - 1);

    double end = omp_get_wtime();

    printf("Time taken: %f\n", end - start);

    free(a);

    return 0;
}
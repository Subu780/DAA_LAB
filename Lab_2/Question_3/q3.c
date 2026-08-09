#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Helper to merge two sorted arrays
int* mergeTwoArrays(int *arr1, int size1, int *arr2, int size2) {
    int total_size = size1 + size2;
    int *merged = (int *)malloc(total_size * sizeof(int));
    int i = 0, j = 0;
    for (int k = 0; k < total_size; k++) {
        long long val1 = (i < size1) ? arr1[i] : (long long)INT_MAX + 1;
        long long val2 = (j < size2) ? arr2[j] : (long long)INT_MAX + 1;
        if (val1 <= val2) {
            merged[k] = arr1[i++];
        } else {
            merged[k] = arr2[j++];
        }
    }
    return merged;
}

// Method 1: Sequential Merge
int* method1(int **arr, int k, int n, int *returnSize) {
    if (k == 0 || arr == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int current_size = n;
    int *result = (int *)malloc(current_size * sizeof(int));
    for (int i = 0; i < current_size; i++) {
        result[i] = arr[0][i];
    }
    for (int i = 1; i < k; i++) {
        int *temp = mergeTwoArrays(result, current_size, arr[i], n); 
        free(result);
        result = temp;
        current_size += n;
    }
    *returnSize = current_size;
    return result;
}

// Method 2: Divide & Conquer Merge
int* method2(int **arr, int n, int l, int r, int *returnSize) {
    if (l == r) {
        *returnSize = n;
        int *copy = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            copy[i] = arr[l][i];
        }
        return copy;
    }
    if (l < r) {
        int m = l + (r - l) / 2;
        int leftSize = 0, rightSize = 0;
        int *leftArr = method2(arr, n, l, m, &leftSize);
        int *rightArr = method2(arr, n, m + 1, r, &rightSize);
        int *mergedArr = mergeTwoArrays(leftArr, leftSize, rightArr, rightSize);
        *returnSize = leftSize + rightSize;
        free(leftArr);
        free(rightArr);
        return mergedArr;
    }
    *returnSize = 0;
    return NULL;
}

// Qsort comparator
int compareInts(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Generate K sorted arrays of size N
int** generateRandomKSortedArrays(int k, int n) {
    int **arr = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++) {
        arr[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 10000;
        }
        qsort(arr[i], n, sizeof(int), compareInts);
    }
    return arr;
}

int main() {
    srand(time(NULL));
    
    int counts[] = {50,  500,  1000, 2000, 3000, 4000, 5000}; 
    int sizes[]  = {100, 1000, 1000, 1000, 1000, 1000, 1000};
    int num_tests = sizeof(counts) / sizeof(counts[0]);
    
    FILE *file = fopen("results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "k_arrays,n_elements,Method1_Time,Method2_Time\n");
    printf("Benchmarking started (k=5000 will take a few seconds)...\n\n");

    for (int t = 0; t < num_tests; t++) {
        int k = counts[t];
        int n = sizes[t];
        
        printf("Testing k = %-5d       n = %-5d", k, n);
        fflush(stdout); // Force print before the heavy calculation
        
        int **lists = generateRandomKSortedArrays(k, n);
        clock_t start, end;
        
        //  Method 1
        int finalSize1 = 0;
        start = clock();
        int *mergedMethod1 = method1(lists, k, n, &finalSize1);
        end = clock();
        double time1 = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // Method 2
        int finalSize2 = 0;
        start = clock();
        int *mergedMethod2 = method2(lists, n, 0, k - 1, &finalSize2);
        end = clock();
        double time2 = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // Write to CSV
        fprintf(file, "%d,%d,%f,%f\n", k, n, time1, time2);
        printf("(M1: %.4fs, M2: %.4fs)\n", time1, time2);
        
        // Free Memory
        free(mergedMethod1);
        free(mergedMethod2);
        for (int i = 0; i < k; i++) {
            free(lists[i]);
        }
        free(lists);
    }
    
    fclose(file);
    printf("\nResults successfully saved to 'results.csv'\n");
    return 0;
}
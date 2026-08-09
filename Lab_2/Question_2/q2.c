#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard 2-way merge function
void merge(int *arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    int *left = (int *)malloc(len1 * sizeof(int));
    int *right = (int *)malloc(len2 * sizeof(int));
    for (int i = 0; i < len1; i++) left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < len1) arr[k++] = left[i++];
    while (j < len2) arr[k++] = right[j++];
    
    free(left);
    free(right);
}

// Standard Merge Sort (2 halves)
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Modified Merge Sort (3 halves)
void modifiedMergeSort(int *arr, int l, int r) {
    if (l >= r) return;
    if (r - l == 1) { // Base case for 2 elements
        if (arr[l] > arr[r]) {
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
        }
        return;
    }
    // Divide array into 3 parts
    int mid1 = l + ((r - l) / 3);
    int mid2 = l + 2 * ((r - l) / 3) + 1;
    // Recursively sort the 3 parts
    modifiedMergeSort(arr, l, mid1);
    modifiedMergeSort(arr, mid1 + 1, mid2);
    modifiedMergeSort(arr, mid2 + 1, r);
    merge(arr, l, mid1, mid2);
    merge(arr, l, mid2, r);
}

int main() {
    srand(time(NULL));
    // Array sizes
    int sizes[] = {10, 100, 1000, 10000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    // Open a CSV file for writing
    FILE *file = fopen("results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    // Write the CSV header
    fprintf(file, "Size,MergeSort_Time,ModifiedMergeSort_Time\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        // Generate identical random numbers for both arrays
        for (int i = 0; i < n; i++) {
            arr1[i] = rand() % 100000;
            arr2[i] = arr1[i]; 
        }
        clock_t start, end;
        double time_2way, time_3way;
        // Standard 2-Way Merge Sort 
        start = clock();
        mergeSort(arr1, 0, n - 1);
        end = clock();
        time_2way = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // Modified 3-Way Merge Sort
        start = clock();
        modifiedMergeSort(arr2, 0, n - 1);
        end = clock();
        time_3way = ((double) (end - start)) / CLOCKS_PER_SEC;
        // Write the results to the file
        fprintf(file, "%d,%f,%f\n", n, time_2way, time_3way);
        printf("Size: %-6d = 2-Way: %f s      3-Way: %f s\n", n, time_2way, time_3way);
        free(arr1);
        free(arr2);
    }
    fclose(file);
    printf("\nResults saved successfully to 'results.csv'\n");
    return 0;
}
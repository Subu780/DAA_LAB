#include <stdio.h>
#include <stdlib.h>

// Global counters
long long bsc = 0;
long long tsc = 0;

// Recursive Binary Search
int binarySearch(int arr[], int l, int r, int x) {
    if (l == r) {
        bsc++;
        return (arr[l] == x) ? l : -1;
    }
    if (l > r) return -1;
    
    int m = l + (r - l) / 2;
    
    bsc++;
    if (arr[m] >= x) {
        return binarySearch(arr, l, m, x);
    } else {
        return binarySearch(arr, m + 1, r, x);
    }
}

// Recursive Ternary Search
int ternarySearch(int arr[], int l, int r, int x) {
    if (l == r) {
        tsc++;
        return (arr[l] == x) ? l : -1;
    }
    // Base case: 2 elements remaining
    if (r - l == 1) { 
        tsc += 2; 
        if (arr[l] == x) return l;
        if (arr[r] == x) return r;
        return -1;
    }
    if (l > r) return -1;
    
    int mid1 = l + (r - l) / 3;
    int mid2 = r - (r - l) / 3;
    
    tsc++;
    if (arr[mid1] >= x) {
        return ternarySearch(arr, l, mid1, x);
    } else {
        tsc++;
        if (arr[mid2] >= x) {
            return ternarySearch(arr, mid1 + 1, mid2, x);
        } else {
            return ternarySearch(arr, mid2 + 1, r, x);
        }
    }
}

int main() {
    int sizes[] = {
        1000, 5000, 10000, 25000, 50000, 75000, 
        100000, 250000, 500000, 750000, 1000000, 
        2500000, 5000000
    };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    FILE *fp = fopen("results.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(fp, "Array_Size,bsc,tsc\n");
    printf("%-15s | %-15s | %-15s\n", "Array Size", "bsc", "tsc");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        
        // Populate simple sorted array
        for (int j = 0; j < n; j++) {
            arr[j] = j * 2; 
        }
        
        // Reset counters
        bsc = 0;
        tsc = 0;
        
        // Search for a single worst-case value (-1 is not in the array)
        int target = -1;
        
        binarySearch(arr, 0, n - 1, target);
        ternarySearch(arr, 0, n - 1, target);
        
        // Write to CSV and console
        fprintf(fp, "%d,%lld,%lld\n", n, bsc, tsc);
        printf("%-15d | %-15lld | %-15lld\n", n, bsc, tsc);
        
        free(arr);
    }
    
    fclose(fp);
    printf("\nResults saved to 'results.csv'.\n");
    
    return 0;
}
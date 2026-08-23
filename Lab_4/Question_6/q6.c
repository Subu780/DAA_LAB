#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merges two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

// Merge Sort: O(n log n)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Two-pointer sweep to find the point with maximum coverage
void findMaxCoveragePoint(int starts[], int ends[], int n) {
    // Sort starts and ends independently: O(n log n)
    mergeSort(starts, 0, n - 1);
    mergeSort(ends, 0, n - 1);

    int current_coverage = 0;
    int max_coverage = 0;
    int best_point = -1;

    int i = 0; // Pointer for starts
    int j = 0; // Pointer for ends

    // Sweep through the arrays: O(n)
    while (i < n && j < n) {
        // The <= ensures inclusive endpoints are counted correctly
        if (starts[i] <= ends[j]) {
            current_coverage++;
            
            if (current_coverage > max_coverage) {
                max_coverage = current_coverage;
                best_point = starts[i];
            }
            i++; 
        } else {
            current_coverage--;
            j++;
        }
    }

    printf("\nMaximum intervals overlapping at a single point: %d\n", max_coverage);
    printf("A point with this maximum coverage is: %d\n", best_point);
}

int main() {
    int n, choice;

    printf("Enter the number of intervals: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of intervals must be greater than 0.\n");
        return 1;
    }

    int *starts = (int *)malloc(n * sizeof(int));
    int *ends = (int *)malloc(n * sizeof(int));

    printf("Choose input method:\n");
    printf("1. Manual Input (Use this to test the S = {(10, 40), ...} example)\n");
    printf("2. Random Generation\n");
    printf("Choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the intervals as pairs (e.g., 10 40):\n");
        for (int i = 0; i < n; i++) {
            printf("Interval %d: ", i + 1);
            scanf("%d %d", &starts[i], &ends[i]);
        }
    } else if (choice == 2) {
        srand(time(NULL));
        printf("\nRandomly generated intervals:\n");
        for (int i = 0; i < n; i++) {
            starts[i] = rand() % 50; 
            ends[i] = starts[i] + 1 + (rand() % 50); 
            printf("Interval %d: (%d, %d)\n", i + 1, starts[i], ends[i]);
        }
    } else {
        printf("Invalid choice.\n");
        free(starts);
        free(ends);
        return 1;
    }

    findMaxCoveragePoint(starts, ends, n);

    free(starts);
    free(ends);
    return 0;
}
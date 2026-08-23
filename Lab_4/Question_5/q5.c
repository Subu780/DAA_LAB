#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard struct to represent an interval
typedef struct {
    int start;
    int end;
} Interval;

// Merges two subarrays of Intervals, sorted by start time
void merge(Interval arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Interval *L = (Interval *)malloc(n1 * sizeof(Interval));
    Interval *R = (Interval *)malloc(n2 * sizeof(Interval));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].start <= R[j].start) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

// Merge Sort for Intervals array: O(n log n)
void mergeSort(Interval arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Standard interval merging logic
void mergeIntervals(Interval arr[], int n) {
    if (n <= 0) return;

    // 1. Sort intervals based on start time
    mergeSort(arr, 0, n - 1);

    // 2. Array to hold the final merged intervals
    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    int count = 0; // Tracks the number of merged intervals

    // Put the first interval into the merged array
    merged[0] = arr[0];
    count++;

    // 3. Traverse the sorted array and merge overlapping intervals: O(n)
    for (int i = 1; i < n; i++) {
        // If the current interval overlaps with the last merged interval
        if (arr[i].start <= merged[count - 1].end) {
            // Update the end time directly if the current interval's end is larger
            if (arr[i].end > merged[count - 1].end) {
                merged[count - 1].end = arr[i].end;
            }
        } 
        // Otherwise, no overlap, so add it as a new distinct interval
        else {
            merged[count] = arr[i];
            count++;
        }
    }

    printf("\nMerged Intervals: { ");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d) ", merged[i].start, merged[i].end);
    }
    printf("}\n");

    free(merged);
}

int main() {
    int n, choice;

    printf("Enter the number of intervals: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of intervals must be greater than 0.\n");
        return 1;
    }

    Interval *arr = (Interval *)malloc(n * sizeof(Interval));

    printf("Choose input method:\n");
    printf("1. Manual Input\n");
    printf("2. Random Generation\n");
    printf("Choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the intervals as pairs (e.g., 1 3):\n");
        for (int i = 0; i < n; i++) {
            printf("Interval %d: ", i + 1);
            scanf("%d %d", &arr[i].start, &arr[i].end);
        }
    } else if (choice == 2) {
        srand(time(NULL));
        printf("\nRandomly generated intervals:\n");
        for (int i = 0; i < n; i++) {
            arr[i].start = rand() % 30; // Random start time between 0 and 29
            arr[i].end = arr[i].start + 1 + (rand() % 15); // End time is guaranteed to be larger
            printf("Interval %d: (%d, %d)\n", i + 1, arr[i].start, arr[i].end);
        }
    } else {
        printf("Invalid choice.\n");
        free(arr);
        return 1;
    }

    mergeIntervals(arr, n);

    free(arr);
    return 0;
}
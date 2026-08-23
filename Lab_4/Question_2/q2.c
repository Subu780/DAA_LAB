#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Merges two sorted subarrays into a single sorted array
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Standard Merge Sort algorithm
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Finds if any S1[i] + S2[j] == x using sorting and two pointers
bool findPairWithSum(int S1[], int S2[], int n, int x) {
    // Sort both arrays: O(n log n)
    mergeSort(S1, 0, n - 1);
    mergeSort(S2, 0, n - 1);

    int i = 0;       // Starts at smallest element of S1
    int j = n - 1;   // Starts at largest element of S2

    // Two-pointer search: O(n)
    while (i < n && j >= 0) {
        int current_sum = S1[i] + S2[j];

        if (current_sum == x) {
            printf("Success: Found pair (%d, %d) which adds up to %d.\n", S1[i], S2[j], x);
            return true;
        } else if (current_sum < x) {
            i++; 
        } else {
            j--; 
        }
    }

    printf("Failure: No pair adds up to %d.\n", x);
    return false;
}

int main() {
    int n, choice, x;

    printf("Enter the size of the sets (n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for the arrays
    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));

    printf("Choose input method:\n");
    printf("1. Manual Input\n");
    printf("2. Random Generation\n");
    printf("Choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter %d elements for S1:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &S1[i]);
        
        printf("Enter %d elements for S2:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &S2[i]);
    } else {
        // Seed the random number generator
        srand(time(NULL)); 
        
        printf("\nRandomly generated S1: ");
        for (int i = 0; i < n; i++) {
            S1[i] = rand() % 100; // Generates numbers from 0 to 99
            printf("%d ", S1[i]);
        }
        
        printf("\nRandomly generated S2: ");
        for (int i = 0; i < n; i++) {
            S2[i] = rand() % 100;
            printf("%d ", S2[i]);
        }
        printf("\n\n");
    }

    printf("Enter the target sum (x): ");
    scanf("%d", &x);

    findPairWithSum(S1, S2, n, x);

    // Free allocated memory
    free(S1);
    free(S2);

    return 0;
}
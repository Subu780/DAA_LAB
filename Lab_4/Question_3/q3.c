#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Merges two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Standard Merge Sort algorithm: O(n log n)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search returning the index of target, or -1 if not found: O(log n)
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Recursive function to pick (k-1) elements and binary search the k-th: O(n^(k-1) log n)
bool kSumRecursive(int arr[], int n, int k, int target, int depth, int start, int current_sum, int chosen[]) {
    // Base case: We have picked k-1 elements
    if (depth == k - 1) {
        int rem = target - current_sum;
        // Search for the final required element in the remaining array
        int foundIdx = binarySearch(arr, start, n - 1, rem);
        
        if (foundIdx != -1) {
            chosen[depth] = arr[foundIdx]; // Store the last element
            return true;
        }
        return false;
    }

    // Recursive case: Pick the next element and increment depth
    for (int i = start; i <= n - (k - depth); i++) {
        chosen[depth] = arr[i];
        if (kSumRecursive(arr, n, k, target, depth + 1, i + 1, current_sum + arr[i], chosen)) {
            return true;
        }
    }
    return false;
}

// Wrapper function for the k-SUM logic
void findKSum(int S[], int n, int k, int T) {
    if (k <= 0 || k > n) {
        printf("Invalid k. Must be between 1 and %d.\n", n);
        return;
    }

    mergeSort(S, 0, n - 1);
    
    int *chosen = (int *)malloc(k * sizeof(int));

    if (kSumRecursive(S, n, k, T, 0, 0, 0, chosen)) {
        printf("Success: Found %d elements that add up to %d -> ( ", k, T);
        for (int i = 0; i < k; i++) {
            printf("%d ", chosen[i]);
        }
        printf(")\n");
    } else {
        printf("Failure: No %d elements add up to %d.\n", k, T);
    }

    free(chosen);
}

int main() {
    int n, k, T, choice;
    printf("Enter the size of the set (n): ");
    scanf("%d", &n);
    int *S = (int *)malloc(n * sizeof(int));
    printf("Choose input method:\n");
    printf("1. Manual Input\n");
    printf("2. Random Generation\n");
    printf("Choice (1 or 2): ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter %d elements for S:\n", n);
        for (int i = 0; i < n; i++) scanf("%d", &S[i]);
    } else {
        srand(time(NULL)); 
        printf("\nRandomly generated S: ");
        for (int i = 0; i < n; i++) {
            S[i] = rand() % 50; 
            printf("%d ", S[i]);
        }
        printf("\n\n");
    }
    printf("Enter number of elements to sum (k): ");
    scanf("%d", &k);
    printf("Enter the target sum (T): ");
    scanf("%d", &T);
    findKSum(S, n, k, T);
    free(S);
    return 0;
}
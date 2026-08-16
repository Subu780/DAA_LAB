#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Divide and Conquer function using pointers
void getMinMax(int arr[], int low, int high, int *min, int *max) {
    int mid;
    int min_left, max_left, min_right, max_right;

    // Base Case 1: If there is only one element
    if (low == high) {
        *max = arr[low];
        *min = arr[low];
        return;
    }

    // Base Case 2: If there are exactly two elements
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            *max = arr[low];
            *min = arr[high];
        } else {
            *max = arr[high];
            *min = arr[low];
        }
        return;
    }

    // Divide: If there are more than 2 elements
    mid = (low + high) / 2;
    
    // Conquer: Recursively find min and max of both halves
    getMinMax(arr, low, mid, &min_left, &max_left);
    getMinMax(arr, mid + 1, high, &min_right, &max_right);

    // Combine: Compare the minimums and maximums of both halves
    if (min_left < min_right) {
        *min = min_left;
    } else {
        *min = min_right;
    }

    if (max_left > max_right) {
        *max = max_left;
    } else {
        *max = max_right;
    }
}

int main() {
    int choice, n;
    
    printf("Enter 1 to input array manually, or 2 to generate a random array: ");
    scanf("%d", &choice);
    
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }
    
    int arr[n];
    
    if (choice == 1) {
        printf("Enter %d elements:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (choice == 2) {
        srand(time(NULL));
        printf("Generated random array: ");
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000; // Generates random numbers between 0 and 999
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    int min, max;
    
    // Pass the memory addresses of min and max using '&'
    getMinMax(arr, 0, n - 1, &min, &max);

    printf("\nArray size (n): %d\n", n);
    printf("Minimum element: %d\n", min);
    printf("Maximum element: %d\n", max);
    
    return 0;
}
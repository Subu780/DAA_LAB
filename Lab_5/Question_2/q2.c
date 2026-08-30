#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap two integer values
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition using last element as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

// Recursive function to find K'th smallest element
int findKthSmallest(int arr[], int low, int high, int target) {
    if (target > 0 && target <= high - low + 1) {
        int pivotIndex = partition(arr, low, high);
        
        if (pivotIndex - low == target - 1) {
            return arr[pivotIndex];
        }
        if (pivotIndex - low > target - 1) {
            return findKthSmallest(arr, low, pivotIndex - 1, target);
        }
        return findKthSmallest(arr, pivotIndex + 1, high, target - pivotIndex + low - 1);
    }
    return -1; 
}

// Main function 
int main() {
    int choice, n, k;
    
    printf("Find K'th Smallest Element Without Sorting\n");
    printf("1. Enter elements manually\n");
    printf("2. Generate random array\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    printf("Enter the number of elements (N): ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter the value of K (1 to %d): ", n);
    scanf("%d", &k);

    if (k <= 0 || k > n) {
        printf("Invalid value of K.\n");
        return 1;
    }
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    if (choice == 1) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    } else if (choice == 2) {
        srand(time(0));
        printf("Generating random array...\nArray: ");
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Invalid choice.\n");
        free(arr);
        return 1;
    }
    
    int kthSmallest = findKthSmallest(arr, 0, n - 1, k);
    printf("The %d'th smallest element is: %d\n", k, kthSmallest);
    
    free(arr);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap two integer values
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// To heapify a subtree rooted with node i
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Build a max heap from the array
void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// Main function 
int main() {
    int choice, n;
    FILE *file;
    
    printf("Heap Sort from File\n");
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
    
    file = fopen("numbers.txt", "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }
    
    if (choice == 1) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            int val;
            scanf("%d", &val);
            fprintf(file, "%d ", val);
        }
        printf("Elements saved to 'numbers.txt'.\n");
    } else if (choice == 2) {
        srand(time(0));
        printf("Generating random array...\n");
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d ", rand() % 1000);
        }
        printf("Random elements saved to 'numbers.txt'.\n");
    } else {
        printf("Invalid choice.\n");
        fclose(file);
        return 1;
    }
    fclose(file); 
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        free(arr);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    
    heapSort(arr, n);
    printf("Array sorted successfully using Heap Sort.\n");
    
    file = fopen("sorted_numbers.txt", "w");
    if (file == NULL) {
        printf("Error creating sorted file.\n");
        free(arr);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
    printf("Sorted elements saved to 'sorted_numbers.txt'.\n");
    
    free(arr);
    return 0;
}
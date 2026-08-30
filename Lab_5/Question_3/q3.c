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

// Recursive function for Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Main function 
int main() {
    int choice, n;
    FILE *file;
    
    printf("Quick Sort from File\n");
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
    
    // Create and write elements to the initial file
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
    fclose(file); // Ensure the file is closed so it saves properly before reading
    
    // Allocate memory for reading the elements back
    int* arr = (int*)malloc(n * sizeof(int));
    
    // Read elements from the file
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
    
    // Perform Quick Sort
    quickSort(arr, 0, n - 1);
    printf("Array sorted successfully using Quick Sort.\n");
    
    // Write sorted elements to a new file
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
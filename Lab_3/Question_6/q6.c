#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The sorting algorithm (Selection Sort logic)
void sorting_algo(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Assume the first element in the unsorted portion is the smallest
        int min_index = i;
        
        // Scan the rest of the array to find the true minimum
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        
        // Swap the found minimum element with the first unsorted element
        int temp = A[min_index];
        A[min_index] = A[i];
        A[i] = temp;
    }
}

// Helper function to print the array
void print_array(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    
    int choice;
    int n;
    
    printf("Enter 1 to input the array manually, or 2 to generate a random array: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size!\n");
        return 1;
    }
    
    // Allocate memory for the array
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Populate the array based on user choice
    if (choice == 1) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }
    } 
    else if (choice == 2) {
        printf("Generating %d random numbers...\n", n);
        for (int i = 0; i < n; i++) {
            A[i] = rand() % 1000; // Generate random numbers from 0 to 999
        }
    } 
    else {
        printf("Invalid choice. Exiting.\n");
        free(A);
        return 1;
    }
    
    // Display original array
    printf("\nOriginal Array:\n");
    print_array(A, n);
    
    // Call the sorting algorithm
    sorting_algo(A, n);
    
    // Display sorted array
    printf("\nSorted Array:\n");
    print_array(A, n);
    
    // Free allocated memory
    free(A);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Define the maximum possible value for the hash array size
#define MAX_VAL 50000 

// Check for duplicates by simply counting occurrences
bool fun(int arr[], int n) {
    
    // Build the hash array directly on the stack. 
    int hash[MAX_VAL] = {0}; 

    for (int i = 0; i < n; i++) {
        int key = arr[i];
        hash[key]++;
        
        // If the count for this number is greater than 1, it's a duplicate!
        if (hash[key] > 1) {
            return true; 
        }
    }

    // Reached the end with no counts going over 1
    return false; 
}

int main() {
    int n = 20;
    
    // Put the random number array on the stack
    int arr[20]; 
    
    srand(time(NULL));

    printf("Array: [ ");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % MAX_VAL; 
        printf("%d ", arr[i]);
    }
    printf("]\n\n");

    // Check for duplicates using the updated function name
    if (fun(arr, n)) {
        printf("Result: Duplicates found!\n");
    } else {
        printf("Result: All elements are unique.\n");
    }

    return 0;
}
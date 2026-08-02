#include <stdio.h>

// Upper Bound Algorithm: Finds the first element strictly greater than 'target'
int transition(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    
    // ans stores the index of the first '1'. Default is -1 if no '1' exists.
    int ans = -1; 

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // If the current element is 0, the upper bound must be to the right
        if (arr[mid] == 0) {
            low = mid + 1;
        } 
        // If the current element is 1, it might be the upper bound, 
        else {
            ans = mid;       // Record current index as a potential answer
            high = mid - 1;  // Narrow the search to the left half
        }
    }

    return ans;
}

// Helper function to print array and its transition point
void find(int arr[], int n) {
    printf("Array: [");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], i == n - 1 ? "" : ", ");
    }
    printf("]\n");

    int index = transition(arr, n);

    if (index != -1) {
        printf("Transition point found at index: %d\n\n", index);
    } else {
        printf("No transition point found.\n\n");
    }
}

int main() {
    // Case 1: Standard case
    int arr1[] = {0, 0, 0, 0, 1, 1, 1};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    find(arr1, n1);

    // Case 2: Transition at the very beginning
    int arr2[] = {1, 1, 1, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    find(arr2, n2);

    // Case 3: Transition at the very end
    int arr3[] = {0, 0, 0, 0, 0, 0, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    find(arr3, n3);

    // Case 4: No transition (all 0s)
    int arr4[] = {0, 0, 0, 0, 0};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    find(arr4, n4);

    return 0;
}
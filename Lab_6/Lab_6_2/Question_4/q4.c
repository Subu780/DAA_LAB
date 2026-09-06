#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Reverse subsequence from i to j
int reverse(int p[], int i, int j) {
    int cost = j - i + 1;
    while (i < j) {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
        i++;
        j--;
    }
    return cost;
}

// Check if sorted
int isSorted(int p[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (p[i] > p[i + 1])
            return 0;
    return 1;
}

// Sort using reversals - O(n) reversals
int sort1(int p[], int n) {
    int totalCost = 0;
    int reversals = 0;
    
    for (int curr = n; curr > 1; curr--) {
        // Find max in p[0..curr-1]
        int maxIdx = 0;
        for (int i = 1; i < curr; i++)
            if (p[i] > p[maxIdx])
                maxIdx = i;
        
        if (maxIdx == curr - 1)
            continue;
        
        // Move max to front
        if (maxIdx > 0) {
            totalCost += reverse(p, 0, maxIdx);
            reversals++;
        }
        
        // Move max to correct position
        totalCost += reverse(p, 0, curr - 1);
        reversals++;
    }
    
    printf("Reversals: %d, Total cost: %d\n", reversals, totalCost);
    return totalCost;
}

// Merge-based sorting
int sort2(int p[], int temp[], int left, int right);

int merge2(int p[], int temp[], int left, int mid, int right) {
    int cost = 0;
    
    // Copy to temp
    for (int i = left; i <= right; i++)
        temp[i] = p[i];
    
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (temp[i] <= temp[j]) {
            p[k++] = temp[i++];
        } else {
            p[k++] = temp[j++];
        }
    }
    
    while (i <= mid)
        p[k++] = temp[i++];
    while (j <= right)
        p[k++] = temp[j++];
    
    // Cost is proportional to merge size
    cost = right - left + 1;
    return cost;
}

int sort2(int p[], int temp[], int left, int right) {
    int cost = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        cost += sort2(p, temp, left, mid);
        cost += sort2(p, temp, mid + 1, right);
        cost += merge2(p, temp, left, mid, right);
    }
    return cost;
}

void printArr(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int choice, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter n: ");
        scanf("%d", &n);
        
        int *p = (int *)malloc(n * sizeof(int));
        printf("Enter permutation of 1 to %d: ", n);
        for (int i = 0; i < n; i++)
            scanf("%d", &p[i]);
        
        printf("\nOriginal: ");
        printArr(p, n);
        
        int *p1 = (int *)malloc(n * sizeof(int));
        int *p2 = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            p1[i] = p[i];
            p2[i] = p[i];
        }
        
        printf("\n--- Method 1 (O(n) reversals) ---\n");
        int cost1 = sort1(p1, n);
        printf("Sorted: ");
        printArr(p1, n);
        
        printf("\n--- Method 2 (O(n log n) cost) ---\n");
        int *temp = (int *)malloc(n * sizeof(int));
        int cost2 = sort2(p2, temp, 0, n - 1);
        printf("Cost: %d\n", cost2);
        printf("Sorted: ");
        printArr(p2, n);
        
        free(p);
        free(p1);
        free(p2);
        free(temp);
        
    } else {
        srand(time(NULL));
        n = rand() % 8 + 5; // 5-12
        
        int *p = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            p[i] = i + 1;
        
        // Shuffle
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
        
        printf("n = %d\n", n);
        printf("Original: ");
        printArr(p, n);
        
        int *p1 = (int *)malloc(n * sizeof(int));
        int *p2 = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            p1[i] = p[i];
            p2[i] = p[i];
        }
        
        printf("\n--- Method 1 ---\n");
        int cost1 = sort1(p1, n);
        printf("Result: ");
        printArr(p1, n);
        
        printf("\n--- Method 2 ---\n");
        int *temp = (int *)malloc(n * sizeof(int));
        int cost2 = sort2(p2, temp, 0, n - 1);
        printf("Cost: %d\n", cost2);
        printf("Result: ");
        printArr(p2, n);
        
        free(p);
        free(p1);
        free(p2);
        free(temp);
    }
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper function to simulate the balance scale
int weigh_pan(int coins[], int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += coins[i];
    }
    return sum;
}

// Simplified Recursive Divide and Conquer
int search_halves(int coins[], int low, int high) {
    // Base Case: 1 coin left to check
    if (low == high) {
        // Simply check if it's the defective one (-1)
        return (coins[low] == -1) ? low : -1;
    }

    int length = high - low + 1;
    int half_size = length / 2;
    
    // Define the two halves
    int left_start = low;
    int left_end = low + half_size - 1;
    int right_start = low + half_size;
    int right_end = right_start + half_size - 1;
    
    // Simulate weighing the two halves
    int left_weight = weigh_pan(coins, left_start, left_end);
    int right_weight = weigh_pan(coins, right_start, right_end);

    if (left_weight == right_weight) {
        // Both halves balanced. 
        if (length % 2 == 0) {
            // Even number of coins, no defective coin exists.
            return -1;
        } else {
            // Odd number of coins. The one we left out at 'high' is the suspect.
            return (coins[high] == -1) ? high : -1;
        }
    } 
    else if (left_weight < right_weight) {
        // Left side is lighter. Defective coin is in the left half.
        return search_halves(coins, left_start, left_end);
    } 
    else {
        // Right side is lighter. Defective coin is in the right half.
        return search_halves(coins, right_start, right_end);
    }
}

// Wrapper function
int find_defective_coin(int coins[], int n) {
    if (n <= 0) return -1;
    return search_halves(coins, 0, n - 1);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));
    
    int choice;
    
    printf("Enter 1 to input coins manually, or 2 to generate a random batch: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    int n;
    
    if (choice == 1) {
        printf("\nEnter the total number of coins: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Invalid number of coins!\n");
            return 1;
        }
        
        int *coins = (int *)malloc(n * sizeof(int));
        printf("Enter the weights (1 for normal, -1 for defective):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &coins[i]);
        }
        
        int result = find_defective_coin(coins, n);
        printf("\nInspection Report\n");
        if (result == -1) {
            printf("STATUS: PASS - All coins are perfectly weighted.\n");
        } else {
            printf("STATUS: FAIL - Defective coin isolated at index %d.\n", result);
        }
        
        free(coins);
    } 
    else if (choice == 2) {
        printf("\nEnter the total number of coins for the random batch: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Invalid number of coins!\n");
            return 1;
        }
        
        int *coins = (int *)malloc(n * sizeof(int));
        
        // Initialize all coins to normal (1)
        for (int i = 0; i < n; i++) {
            coins[i] = 1;
        }
        
        // Randomly decide if this batch has a defective coin (90% chance defect, 10% chance perfect)
        int has_defect = (rand() % 10) != 0; 
        
        if (has_defect) {
            int hidden_defect_idx = rand() % n;
            coins[hidden_defect_idx] = -1;
            printf("[Simulation Info] A defective coin was secretly placed at index %d.\n", hidden_defect_idx);
        }
        
        // Run the algorithm
        int result = find_defective_coin(coins, n);
        
        printf("\nInspection Report\n");
        if (result == -1) {
            printf("STATUS: PASS - Algorithm confirms all coins are perfectly weighted.\n");
        } else {
            printf("STATUS: FAIL - Algorithm isolated defective coin at index %d.\n", result);
        }
        
        free(coins);
    } 
    else {
        printf("Invalid choice. Exiting.\n");
    }
    
    return 0;
}
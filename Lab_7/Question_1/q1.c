#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate the minimum number of moves to invert the coin triangle using the formula
int calculateMinimumMovesFormula(int size) {
    // The minimum number of moves is given by the formula (size * (size + 1)) / 2
    return (size * (size + 1)) / 2;
}

// Function to calculate the minimum number of moves to invert the coin triangle using dynamic programming
int calculateMinimumMovesDP(int size) {
    int dp[size + 1];
    dp[0] = 0;
    for (int i = 1; i <= size; i++) {
        dp[i] = dp[i - 1] + i;
    }
    return dp[size];
}

int main() {
    int choice;
    int size;

    printf("Choose an option:\n");
    printf("1. Random size\n");
    printf("2. Input size\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Generate a random size between 1 and 10
        srand(time(0));
        size = rand() % 10 + 1;
        printf("Generated random size: %d\n", size);
    } else if (choice == 2) {
        printf("Enter the size of the equilateral triangle: ");
        scanf("%d", &size);
    } else {
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    int movesFormula = calculateMinimumMovesFormula(size);
    int movesDP = calculateMinimumMovesDP(size);

    printf("Minimum number of moves to invert the coin triangle (using formula): %d\n", movesFormula);
    printf("Minimum number of moves to invert the coin triangle (using dynamic programming): %d\n", movesDP);

    return 0;
}
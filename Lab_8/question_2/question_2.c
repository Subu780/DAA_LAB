/* Question 2: Coin Change - total number of combinations */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COINS 100

int getMenuChoice() {
    int choice;
    while (1) {
        printf("Enter 1 to give input manually\n");
        printf("Enter 2 to generate random input\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input, exiting.\n");
            exit(1);
        }
        if (choice == 1 || choice == 2)
            return choice;
        printf("Please enter only 1 or 2.\n\n");
    }
}

/* ways[v] = number of combinations that sum to v.
   Coins are the OUTER loop so that 1+2 and 2+1 are counted once. */
long long countWays(int coins[], int n, int V, long long ways[]) {
    int i, v;
    for (v = 0; v <= V; v++)
        ways[v] = 0;
    ways[0] = 1;
    for (i = 0; i < n; i++) {
        for (v = coins[i]; v <= V; v++) {
            ways[v] = ways[v] + ways[v - coins[i]];
        }
    }
    return ways[V];
}

int main() {
    int n, V, i, j, choice, same;
    int coins[MAX_COINS];
    long long *ways;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Number of coin denominations (1 to %d): ", MAX_COINS);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_COINS) {
            printf("Invalid number of coins.\n");
            return 1;
        }
        printf("Enter the %d distinct coin values: ", n);
        for (i = 0; i < n; i++) {
            if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0) {
                printf("Coin values must be positive integers.\n");
                return 1;
            }
            for (j = 0; j < i; j++) {
                if (coins[j] == coins[i]) {
                    printf("Coins must be distinct.\n");
                    return 1;
                }
            }
        }
        printf("Target amount V: ");
        if (scanf("%d", &V) != 1 || V < 0) {
            printf("Invalid target amount.\n");
            return 1;
        }
    } else {
        n = 2 + rand() % 4;
        for (i = 0; i < n; i++) {
            do {
                coins[i] = 1 + rand() % 10;
                same = 0;
                for (j = 0; j < i; j++)
                    if (coins[j] == coins[i])
                        same = 1;
            } while (same);
        }
        V = 5 + rand() % 30;
        printf("Generated coins:");
        for (i = 0; i < n; i++)
            printf(" %d", coins[i]);
        printf("\nGenerated target V = %d\n", V);
    }

    ways = (long long *) malloc((V + 1) * sizeof(long long));
    if (ways == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Number of distinct combinations = %lld\n", countWays(coins, n, V, ways));

    free(ways);
    return 0;
}

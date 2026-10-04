/* Question 1: Minimum Coin Change (bottom-up DP) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_COINS 100
#define INF 1000000000

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

/* dp[v] = fewest coins needed to make amount v
   lastCoin[v] = the coin used last to reach v (for printing the answer) */
int minCoins(int coins[], int n, int V, int dp[], int lastCoin[]) {
    int v, i;
    dp[0] = 0;
    for (v = 1; v <= V; v++) {
        dp[v] = INF;
        lastCoin[v] = -1;
        for (i = 0; i < n; i++) {
            if (coins[i] <= v && dp[v - coins[i]] != INF
                && dp[v - coins[i]] + 1 < dp[v]) {
                dp[v] = dp[v - coins[i]] + 1;
                lastCoin[v] = coins[i];
            }
        }
    }
    if (dp[V] == INF)
        return -1;
    return dp[V];
}

int main() {
    int n, V, i, j, choice, answer, v, same;
    int coins[MAX_COINS];
    int *dp, *lastCoin;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Number of coin denominations (1 to %d): ", MAX_COINS);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_COINS) {
            printf("Invalid number of coins.\n");
            return 1;
        }
        printf("Enter the %d coin values: ", n);
        for (i = 0; i < n; i++) {
            if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0) {
                printf("Coin values must be positive integers.\n");
                return 1;
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
                coins[i] = 1 + rand() % 20;
                same = 0;
                for (j = 0; j < i; j++)
                    if (coins[j] == coins[i])
                        same = 1;
            } while (same);
        }
        V = 10 + rand() % 60;
        printf("Generated coins:");
        for (i = 0; i < n; i++)
            printf(" %d", coins[i]);
        printf("\nGenerated target V = %d\n", V);
    }

    dp = (int *) malloc((V + 1) * sizeof(int));
    lastCoin = (int *) malloc((V + 1) * sizeof(int));
    if (dp == NULL || lastCoin == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    answer = minCoins(coins, n, V, dp, lastCoin);

    if (answer == -1) {
        printf("Result: -1 (amount %d cannot be made)\n", V);
    } else {
        printf("Minimum number of coins = %d\n", answer);
        printf("Coins used:");
        v = V;
        while (v > 0) {
            printf(" %d", lastCoin[v]);
            v = v - lastCoin[v];
        }
        printf("\n");
    }

    free(dp);
    free(lastCoin);
    return 0;
}

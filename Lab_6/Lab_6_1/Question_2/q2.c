#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// 0/1 Knapsack using DP
int knapsack(int wt[], int val[], int n, int W) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }
    
    // Build table bottom-up
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    
    int result = dp[n][W];
    
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
    
    return result;
}

int main() {
    int choice, n, W;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter number of items: ");
        scanf("%d", &n);
        printf("Enter knapsack capacity: ");
        scanf("%d", &W);
        
        int *wt = (int *)malloc(n * sizeof(int));
        int *val = (int *)malloc(n * sizeof(int));
        
        printf("Enter weights: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &wt[i]);
        
        printf("Enter values: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &val[i]);
        
        int maxProfit = knapsack(wt, val, n, W);
        printf("Maximum profit: %d\n", maxProfit);
        
        free(wt);
        free(val);
    } else {
        srand(time(NULL));
        n = rand() % 8 + 3; // Random 3-10 items
        W = rand() % 50 + 20; // Random capacity 20-69
        
        int *wt = (int *)malloc(n * sizeof(int));
        int *val = (int *)malloc(n * sizeof(int));
        
        printf("Number of items: %d\n", n);
        printf("Knapsack capacity: %d\n", W);
        printf("Weights: ");
        for (int i = 0; i < n; i++) {
            wt[i] = rand() % 20 + 1;
            printf("%d ", wt[i]);
        }
        printf("\nValues: ");
        for (int i = 0; i < n; i++) {
            val[i] = rand() % 100 + 1;
            printf("%d ", val[i]);
        }
        printf("\n");
        
        int maxProfit = knapsack(wt, val, n, W);
        printf("Maximum profit: %d\n", maxProfit);
        
        free(wt);
        free(val);
    }
    
    return 0;
}

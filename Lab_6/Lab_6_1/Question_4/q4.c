#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Matrix Chain Multiplication using DP
int matChainMul(int arr[], int n, int **dp, int **brk) {
    // n is number of matrices = size of arr - 1
    
    // Cost is 0 for single matrix
    for (int i = 1; i < n; i++)
        dp[i][i] = 0;
    
    // L is chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    brk[i][j] = k;
                }
            }
        }
    }
    
    return dp[1][n-1];
}

void printOrder(int **brk, int i, int j) {
    if (i == j) {
        printf("M%d", i);
        return;
    }
    printf("(");
    printOrder(brk, i, brk[i][j]);
    printOrder(brk, brk[i][j] + 1, j);
    printf(")");
}

int main() {
    int choice, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter number of matrices: ");
        scanf("%d", &n);
        
        int *arr = (int *)malloc((n + 1) * sizeof(int));
        printf("Enter %d dimensions: ", n + 1);
        for (int i = 0; i <= n; i++)
            scanf("%d", &arr[i]);
        
        // Allocate DP and bracket tables
        int **dp = (int **)malloc((n + 1) * sizeof(int *));
        int **brk = (int **)malloc((n + 1) * sizeof(int *));
        for (int i = 0; i <= n; i++) {
            dp[i] = (int *)malloc((n + 1) * sizeof(int));
            brk[i] = (int *)malloc((n + 1) * sizeof(int));
        }
        
        int minCost = matChainMul(arr, n + 1, dp, brk);
        printf("Minimum multiplications: %d\n", minCost);
        printf("Optimal order: ");
        printOrder(brk, 1, n);
        printf("\n");
        
        // Free memory
        for (int i = 0; i <= n; i++) {
            free(dp[i]);
            free(brk[i]);
        }
        free(dp);
        free(brk);
        free(arr);
        
    } else {
        srand(time(NULL));
        n = rand() % 5 + 3; // 3-7 matrices
        
        int *arr = (int *)malloc((n + 1) * sizeof(int));
        printf("Number of matrices: %d\n", n);
        printf("Dimensions: ");
        for (int i = 0; i <= n; i++) {
            arr[i] = rand() % 50 + 5; // 5-54
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        // Allocate DP and bracket tables
        int **dp = (int **)malloc((n + 1) * sizeof(int *));
        int **brk = (int **)malloc((n + 1) * sizeof(int *));
        for (int i = 0; i <= n; i++) {
            dp[i] = (int *)malloc((n + 1) * sizeof(int));
            brk[i] = (int *)malloc((n + 1) * sizeof(int));
        }
        
        int minCost = matChainMul(arr, n + 1, dp, brk);
        printf("Minimum multiplications: %d\n", minCost);
        printf("Optimal order: ");
        printOrder(brk, 1, n);
        printf("\n");
        
        // Free memory
        for (int i = 0; i <= n; i++) {
            free(dp[i]);
            free(brk[i]);
        }
        free(dp);
        free(brk);
        free(arr);
    }
    
    return 0;
}

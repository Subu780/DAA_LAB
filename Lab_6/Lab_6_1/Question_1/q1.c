#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fibonacci using DP (Tabulation)
long long fibDP(int n) {
    if (n <= 1) return n;
    
    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    long long result = dp[n];
    free(dp);
    return result;
}

int main() {
    int choice, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter n: ");
        scanf("%d", &n);
    } else {
        srand(time(NULL));
        n = rand() % 40 + 1; // Random between 1-40
        printf("Random n: %d\n", n);
    }
    
    long long result = fibDP(n);
    printf("Fibonacci(%d) = %lld\n", n, result);
    
    return 0;
}

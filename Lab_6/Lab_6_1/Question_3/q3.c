#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

// LCS using DP - returns length
int lcsLength(char *s1, char *s2, int m, int n, int **dp) {
    // Build DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}

// Print the LCS
void printLCS(char *s1, char *s2, int m, int n, int **dp) {
    int len = dp[m][n];
    char *lcs = (char *)malloc((len + 1) * sizeof(char));
    lcs[len] = '\0';
    
    int i = m, j = n, idx = len - 1;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs[idx--] = s1[i-1];
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    
    printf("LCS: %s\n", lcs);
    free(lcs);
}

void genRandStr(char *str, int len) {
    for (int i = 0; i < len; i++)
        str[i] = 'A' + rand() % 26;
    str[len] = '\0';
}

int main() {
    int choice;
    char s1[100], s2[100];
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter first string: ");
        scanf("%s", s1);
        printf("Enter second string: ");
        scanf("%s", s2);
    } else {
        srand(time(NULL));
        int len1 = rand() % 10 + 5; // 5-14 chars
        int len2 = rand() % 10 + 5;
        genRandStr(s1, len1);
        genRandStr(s2, len2);
        printf("String 1: %s\n", s1);
        printf("String 2: %s\n", s2);
    }
    
    int m = strlen(s1);
    int n = strlen(s2);
    
    // Create DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    
    int len = lcsLength(s1, s2, m, n, dp);
    printf("LCS Length: %d\n", len);
    
    if (len > 0)
        printLCS(s1, s2, m, n, dp);
    
    // Free memory
    for (int i = 0; i <= m; i++)
        free(dp[i]);
    free(dp);
    
    return 0;
}

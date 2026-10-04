/* Question 6: Edit Distance with traceback */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 1000

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

void randomString(char s[], int len) {
    int i;
    for (i = 0; i < len; i++)
        s[i] = 'a' + rand() % 4;
    s[len] = '\0';
}

int min3(int x, int y, int z) {
    int r = x;
    if (y < r) r = y;
    if (z < r) r = z;
    return r;
}

int main() {
    char A[MAX_LEN + 1], B[MAX_LEN + 1];
    char opType[2 * MAX_LEN + 1], opFrom[2 * MAX_LEN + 1], opTo[2 * MAX_LEN + 1];
    int m, n, i, j, choice, steps = 0, k;
    int **dp;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Enter string A (no spaces): ");
        scanf("%1000s", A);
        printf("Enter string B (no spaces): ");
        scanf("%1000s", B);
    } else {
        randomString(A, 4 + rand() % 5);
        randomString(B, 4 + rand() % 5);
        printf("Generated A = %s\n", A);
        printf("Generated B = %s\n", B);
    }

    m = strlen(A);
    n = strlen(B);

    /* dp[i][j] = min operations to turn first i chars of A into first j chars of B */
    dp = (int **) malloc((m + 1) * sizeof(int *));
    for (i = 0; i <= m; i++)
        dp[i] = (int *) malloc((n + 1) * sizeof(int));

    for (i = 0; i <= m; i++)
        dp[i][0] = i;
    for (j = 0; j <= n; j++)
        dp[0][j] = j;

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min3(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]);
        }
    }

    printf("Minimum edit distance = %d\n", dp[m][n]);

    /* traceback from the bottom-right corner; ops come out in reverse order
       K = keep, R = replace, D = delete, I = insert */
    i = m;
    j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && dp[i][j] == dp[i - 1][j - 1]) {
            opType[steps] = 'K'; opFrom[steps] = A[i - 1]; opTo[steps] = B[j - 1];
            i--; j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            opType[steps] = 'R'; opFrom[steps] = A[i - 1]; opTo[steps] = B[j - 1];
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            opType[steps] = 'D'; opFrom[steps] = A[i - 1]; opTo[steps] = ' ';
            i--;
        } else {
            opType[steps] = 'I'; opFrom[steps] = ' '; opTo[steps] = B[j - 1];
            j--;
        }
        steps++;
    }

    printf("Traceback (A -> B):\n");
    for (k = steps - 1; k >= 0; k--) {
        if (opType[k] == 'K')
            printf("  Keep    '%c'\n", opFrom[k]);
        else if (opType[k] == 'R')
            printf("  Replace '%c' with '%c'\n", opFrom[k], opTo[k]);
        else if (opType[k] == 'D')
            printf("  Delete  '%c'\n", opFrom[k]);
        else
            printf("  Insert  '%c'\n", opTo[k]);
    }

    for (i = 0; i <= m; i++)
        free(dp[i]);
    free(dp);
    return 0;
}

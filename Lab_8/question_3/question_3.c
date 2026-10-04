/* Question 3: Longest Common Subsequence */
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
        s[i] = 'A' + rand() % 4;
    s[len] = '\0';
}

int main() {
    char X[MAX_LEN + 1], Y[MAX_LEN + 1], *lcs;
    int m, n, i, j, k, choice;
    int **L;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Enter sequence X (no spaces): ");
        scanf("%1000s", X);
        printf("Enter sequence Y (no spaces): ");
        scanf("%1000s", Y);
    } else {
        randomString(X, 6 + rand() % 7);
        randomString(Y, 6 + rand() % 7);
        printf("Generated X = %s\n", X);
        printf("Generated Y = %s\n", Y);
    }

    m = strlen(X);
    n = strlen(Y);

    /* L[i][j] = LCS length of first i chars of X and first j chars of Y */
    L = (int **) malloc((m + 1) * sizeof(int *));
    for (i = 0; i <= m; i++)
        L[i] = (int *) calloc(n + 1, sizeof(int));

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else if (L[i - 1][j] >= L[i][j - 1])
                L[i][j] = L[i - 1][j];
            else
                L[i][j] = L[i][j - 1];
        }
    }

    /* walk back from L[m][n] to build the string (filled from the end) */
    k = L[m][n];
    lcs = (char *) malloc(k + 1);
    lcs[k] = '\0';
    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[--k] = X[i - 1];
            i--;
            j--;
        } else if (L[i - 1][j] >= L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Length of LCS = %d\n", L[m][n]);
    printf("LCS = %s\n", lcs);

    for (i = 0; i <= m; i++)
        free(L[i]);
    free(L);
    free(lcs);
    return 0;
}

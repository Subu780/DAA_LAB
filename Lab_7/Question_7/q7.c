#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void printOrder(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOrder(s, i, s[i][j]);
        printf(" ");
        printOrder(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int choice, n, i, j, k, len;
    int *p;
    long long **m;
    int **s;

    printf("Matrix Chain Multiplication\n");
    printf("1. Random dimensions\n");
    printf("2. Enter dimensions\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        srand(time(NULL));
        n = 2 + rand() % 5;
        p = (int *)malloc((n + 1) * sizeof(int));
        printf("Number of matrices: %d\n", n);
        printf("Dimensions: ");
        for (i = 0; i <= n; i++) {
            p[i] = 1 + rand() % 10;
            if (i > 0) printf("A%d:%dx%d ", i, p[i - 1], p[i]);
            else printf("p[0]=%d ", p[i]);
        }
        printf("\n");
    } else {
        printf("Enter number of matrices (1-20): ");
        scanf("%d", &n);
        if (n < 1 || n > 20) {
            printf("Invalid n. Must be between 1 and 20.\n");
            return 1;
        }
        p = (int *)malloc((n + 1) * sizeof(int));
        printf("Enter %d dimensions (p[0] p[1] ... p[%d]): ", n + 1, n);
        for (i = 0; i <= n; i++) {
            scanf("%d", &p[i]);
            if (p[i] < 1) {
                printf("Invalid dimension. All p must be >= 1.\n");
                free(p);
                return 1;
            }
        }
        printf("Number of matrices: %d\n", n);
        printf("Dimensions: ");
        for (i = 1; i <= n; i++) {
            printf("A%d:%dx%d ", i, p[i - 1], p[i]);
        }
        printf("\n");
    }

    if (n == 1) {
        printf("Minimum scalar multiplications: 0\n");
        printf("Optimal parenthesization: (A1)\n");
        free(p);
        return 0;
    }

    m = (long long **)malloc((n + 1) * sizeof(long long *));
    s = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        m[i] = (long long *)calloc(n + 1, sizeof(long long));
        s[i] = (int *)calloc(n + 1, sizeof(int));
    }

    for (len = 2; len <= n; len++) {
        for (i = 1; i <= n - len + 1; i++) {
            j = i + len - 1;
            m[i][j] = LLONG_MAX;
            for (k = i; k < j; k++) {
                long long cost = m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("Minimum scalar multiplications: %lld\n", m[1][n]);
    printf("Optimal parenthesization: ");
    printOrder(s, 1, n);
    printf("\n");

    for (i = 0; i <= n; i++) {
        free(m[i]);
        free(s[i]);
    }
    free(m);
    free(s);
    free(p);

    return 0;
}

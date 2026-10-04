/* Question 8: Optimal Binary Search Tree */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_N 200
#define BIG 1e18

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

/* prints the tree sideways-indented: each node shows which side of its parent it is on */
void printTree(int **root, int i, int j, int depth, char side) {
    int r, d;
    for (d = 0; d < depth; d++)
        printf("    ");
    if (j < i) {
        printf("%cd%d\n", side, j);
        return;
    }
    r = root[i][j];
    printf("%ck%d\n", side, r);
    printTree(root, i, r - 1, depth + 1, 'L');
    printTree(root, r + 1, j, depth + 1, 'R');
}

int main() {
    int n, i, j, r, l, choice;
    double p[MAX_N + 2], q[MAX_N + 2], total, t;
    double **e, **w;
    int **root;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Number of keys n (1 to %d): ", MAX_N);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
            printf("Invalid n.\n");
            return 1;
        }
        printf("Enter p1..p%d (search probabilities of keys): ", n);
        for (i = 1; i <= n; i++)
            scanf("%lf", &p[i]);
        printf("Enter q0..q%d (probabilities of dummy keys): ", n);
        for (i = 0; i <= n; i++)
            scanf("%lf", &q[i]);
    } else {
        n = 3 + rand() % 4;
        total = 0;
        for (i = 1; i <= n; i++) {
            p[i] = 1 + rand() % 20;
            total += p[i];
        }
        for (i = 0; i <= n; i++) {
            q[i] = 1 + rand() % 20;
            total += q[i];
        }
        /* scale so everything adds up to 1 */
        for (i = 1; i <= n; i++)
            p[i] = p[i] / total;
        for (i = 0; i <= n; i++)
            q[i] = q[i] / total;
        printf("Generated n = %d\n", n);
        printf("p:");
        for (i = 1; i <= n; i++)
            printf(" %.3f", p[i]);
        printf("\nq:");
        for (i = 0; i <= n; i++)
            printf(" %.3f", q[i]);
        printf("\n");
    }

    total = 0;
    for (i = 1; i <= n; i++)
        total += p[i];
    for (i = 0; i <= n; i++)
        total += q[i];
    if (fabs(total - 1.0) > 1e-6) {
        printf("All probabilities must add up to 1 (they add up to %f).\n", total);
        return 1;
    }

    e = (double **) malloc((n + 2) * sizeof(double *));
    w = (double **) malloc((n + 2) * sizeof(double *));
    root = (int **) malloc((n + 2) * sizeof(int *));
    for (i = 0; i <= n + 1; i++) {
        e[i] = (double *) calloc(n + 1, sizeof(double));
        w[i] = (double *) calloc(n + 1, sizeof(double));
        root[i] = (int *) calloc(n + 1, sizeof(int));
    }

    /* empty subtrees hold only a dummy key */
    for (i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* e[i][j] = expected cost of the best tree on keys ki..kj,
       w[i][j] = total probability of that range */
    for (l = 1; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            e[i][j] = BIG;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (r = i; r <= j; r++) {
                t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Minimum expected search cost = %.4f\n", e[1][n]);
    printf("Root of the optimal tree = k%d\n", root[1][n]);
    printf("Tree structure:\n");
    printTree(root, 1, n, 0, '*');

    for (i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }
    free(e);
    free(w);
    free(root);
    return 0;
}

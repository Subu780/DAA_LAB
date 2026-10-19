/* DAA Lab-10 : Question 5 - Lexicographically smallest permutation using allowed swaps (DSU) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 1000000
#define MAXM 1000000

static int *parent, *sz;

static int find(int x)
{
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}

static void unite(int a, int b)
{
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    sz[a] += sz[b];
}

static void solve(int n, const int *A, int m, const int *eu, const int *ev)
{
    parent = malloc((n + 1) * sizeof(int));
    sz = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) { parent[i] = i; sz[i] = 1; }
    for (int i = 0; i < m; i++) unite(eu[i], ev[i]);

    int *root = malloc((n + 1) * sizeof(int)), *cnt = calloc(n + 2, sizeof(int));
    for (int i = 1; i <= n; i++) { root[i] = find(i); cnt[root[i]]++; }

    /* list of positions of each component, stored consecutively and in increasing order */
    int *start = malloc((n + 2) * sizeof(int)), *ptr = malloc((n + 2) * sizeof(int));
    int *list = malloc(n * sizeof(int));
    int off = 0;
    for (int r = 1; r <= n; r++) { start[r] = ptr[r] = off; off += cnt[r]; }
    for (int i = 1; i <= n; i++) list[ptr[root[i]]++] = i;
    for (int r = 1; r <= n; r++) ptr[r] = start[r];

    /* A is a permutation, so scanning the values 1..n in increasing order gives each
       component its values already sorted: no explicit sorting needed. */
    int *posOf = malloc((n + 1) * sizeof(int)), *res = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) posOf[A[i - 1]] = i;
    for (int v = 1; v <= n; v++) {
        int r = root[posOf[v]];
        res[list[ptr[r]++]] = v;
    }

    printf("\nn = %d, allowed swaps: %d\nOriginal permutation:", n, m);
    for (int i = 0; i < n; i++) printf(" %d", A[i]);
    printf("\n");
    if (n <= 20) {
        printf("\nConnected components (positions -> values before => after):\n");
        unsigned char *shown = calloc(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            int r = root[i];
            if (shown[r]) continue;
            shown[r] = 1;
            printf("  positions {");
            for (int j = start[r]; j < start[r] + cnt[r]; j++) printf("%s%d", j > start[r] ? "," : "", list[j]);
            printf("}  values {");
            for (int j = start[r]; j < start[r] + cnt[r]; j++) printf("%s%d", j > start[r] ? "," : "", A[list[j] - 1]);
            printf("} => {");
            for (int j = start[r]; j < start[r] + cnt[r]; j++) printf("%s%d", j > start[r] ? "," : "", res[list[j]]);
            printf("}\n");
        }
        free(shown);
    }
    printf("\nSmallest permutation:");
    for (int i = 1; i <= n; i++) printf(" %d", res[i]);
    printf("\n");
    free(parent); free(sz); free(root); free(cnt); free(start); free(ptr); free(list); free(posOf); free(res);
}

static void manualInput(void)
{
    int n, m;
    printf("Enter n (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid n.\n"); return; }
    int *A = malloc(n * sizeof(int));
    unsigned char *seen = calloc(n + 1, 1);
    printf("Enter the permutation of 1..%d: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1 || A[i] < 1 || A[i] > n || seen[A[i]]) {
            printf("Invalid permutation.\n"); free(A); free(seen); return;
        }
        seen[A[i]] = 1;
    }
    free(seen);
    printf("Enter number of allowed swaps m (0-%d): ", MAXM);
    if (scanf("%d", &m) != 1 || m < 0 || m > MAXM) { printf("Invalid m.\n"); free(A); return; }
    int *eu = malloc((m + 1) * sizeof(int)), *ev = malloc((m + 1) * sizeof(int));
    printf("Enter %d swaps as 'u v' (positions 1..%d):\n", m, n);
    for (int i = 0; i < m; i++)
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 1 || eu[i] > n || ev[i] < 1 || ev[i] > n) {
            printf("Invalid swap.\n"); free(A); free(eu); free(ev); return;
        }
    solve(n, A, m, eu, ev);
    free(A); free(eu); free(ev);
}

static void generateInput(void)
{
    int n = 7 + rand() % 5, m = 3 + rand() % 4;
    int *A = malloc(n * sizeof(int)), *eu = malloc(m * sizeof(int)), *ev = malloc(m * sizeof(int));
    for (int i = 0; i < n; i++) A[i] = i + 1;
    for (int i = n - 1; i > 0; i--) { int j = rand() % (i + 1), t = A[i]; A[i] = A[j]; A[j] = t; }
    for (int i = 0; i < m; i++) {
        eu[i] = 1 + rand() % n;
        do ev[i] = 1 + rand() % n; while (ev[i] == eu[i]);
    }
    printf("Generated random input: n = %d, m = %d\nSwaps:", n, m);
    for (int i = 0; i < m; i++) printf(" (%d,%d)", eu[i], ev[i]);
    printf("\n");
    solve(n, A, m, eu, ev);
    free(A); free(eu); free(ev);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Lexicographically Smallest Permutation =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

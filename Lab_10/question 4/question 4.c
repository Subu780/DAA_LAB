/* DAA Lab-10 : Question 4 - Vertex deletions answered by reverse-time DSU */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 1000000
#define MAXE 1000000

static int *parent, *sz;
static long long *sum;

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
    sum[a] += sum[b];
}

static void solve(int V, int E, const long long *a, const int *eu, const int *ev, const int *P)
{
    /* adjacency in CSR form */
    int *start = calloc(V + 2, sizeof(int)), *adj = malloc((2 * (size_t)E + 1) * sizeof(int));
    for (int i = 0; i < E; i++) { start[eu[i] + 1]++; start[ev[i] + 1]++; }
    for (int v = 1; v <= V + 1; v++) start[v] += start[v - 1];
    int *fill = malloc((V + 2) * sizeof(int));
    for (int v = 0; v <= V + 1; v++) fill[v] = start[v];
    for (int i = 0; i < E; i++) { adj[fill[eu[i]]++] = ev[i]; adj[fill[ev[i]]++] = eu[i]; }

    parent = malloc((V + 1) * sizeof(int));
    sz = malloc((V + 1) * sizeof(int));
    sum = malloc((V + 1) * sizeof(long long));
    unsigned char *active = calloc(V + 1, 1);
    long long *res = calloc(V + 1, sizeof(long long));    /* res[i] = answer after i deletions */

    long long cur = 0;
    res[V] = 0;
    for (int i = V; i >= 2; i--) {                         /* add p_i back, then answer for i-1 deletions */
        int v = P[i - 1];
        active[v] = 1; parent[v] = v; sz[v] = 1; sum[v] = a[v];
        for (int j = start[v]; j < start[v + 1]; j++)
            if (active[adj[j]]) unite(v, adj[j]);
        long long s = sum[find(v)];
        if (s > cur) cur = s;
        res[i - 1] = cur;
    }

    printf("\nV = %d, E = %d\nVertex values:", V, E);
    for (int v = 1; v <= V; v++) printf(" %lld", a[v]);
    printf("\nDeletion order P:");
    for (int i = 0; i < V; i++) printf(" %d", P[i]);
    printf("\n\n");
    for (int i = 1; i <= V; i++)
        printf("After deleting p%d = %d: max component sum = %lld\n", i, P[i - 1], res[i]);

    free(start); free(adj); free(fill); free(parent); free(sz); free(sum); free(active); free(res);
}

static void manualInput(void)
{
    int V, E;
    printf("Enter number of vertices V (1-%d): ", MAXV);
    if (scanf("%d", &V) != 1 || V < 1 || V > MAXV) { printf("Invalid V.\n"); return; }
    long long *a = malloc((V + 1) * sizeof(long long));
    printf("Enter the %d vertex values (non-negative): ", V);
    for (int v = 1; v <= V; v++)
        if (scanf("%lld", &a[v]) != 1 || a[v] < 0) { printf("Invalid value.\n"); free(a); return; }
    printf("Enter number of edges E (0-%d): ", MAXE);
    if (scanf("%d", &E) != 1 || E < 0 || E > MAXE) { printf("Invalid E.\n"); free(a); return; }
    int *eu = malloc((E + 1) * sizeof(int)), *ev = malloc((E + 1) * sizeof(int)), *P = malloc(V * sizeof(int));
    printf("Enter %d edges as 'u v' (vertices 1..%d):\n", E, V);
    for (int i = 0; i < E; i++)
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 1 || eu[i] > V || ev[i] < 1 || ev[i] > V) {
            printf("Invalid edge.\n"); free(a); free(eu); free(ev); free(P); return;
        }
    printf("Enter the deletion order (a permutation of 1..%d): ", V);
    unsigned char *seen = calloc(V + 1, 1);
    for (int i = 0; i < V; i++) {
        if (scanf("%d", &P[i]) != 1 || P[i] < 1 || P[i] > V || seen[P[i]]) {
            printf("Invalid permutation.\n"); free(a); free(eu); free(ev); free(P); free(seen); return;
        }
        seen[P[i]] = 1;
    }
    free(seen);
    solve(V, E, a, eu, ev, P);
    free(a); free(eu); free(ev); free(P);
}

static void generateInput(void)
{
    int V = 6 + rand() % 4, E = V + rand() % 4;
    long long *a = malloc((V + 1) * sizeof(long long));
    int *eu = malloc(E * sizeof(int)), *ev = malloc(E * sizeof(int)), *P = malloc(V * sizeof(int));
    for (int v = 1; v <= V; v++) a[v] = 1 + rand() % 20;
    for (int i = 0; i < E; i++) {
        eu[i] = 1 + rand() % V;
        do ev[i] = 1 + rand() % V; while (ev[i] == eu[i]);
    }
    for (int i = 0; i < V; i++) P[i] = i + 1;
    for (int i = V - 1; i > 0; i--) { int j = rand() % (i + 1), t = P[i]; P[i] = P[j]; P[j] = t; }
    printf("Generated random input: V = %d, E = %d\nEdges:", V, E);
    for (int i = 0; i < E; i++) printf(" (%d,%d)", eu[i], ev[i]);
    printf("\n");
    solve(V, E, a, eu, ev, P);
    free(a); free(eu); free(ev); free(P);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Reverse Time-Step DSU (Vertex Deletions) =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

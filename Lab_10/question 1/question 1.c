/* DAA Lab-10 : Question 1 - Online bipartiteness testing (DSU with parity) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 1000000
#define MAXM 1000000

static int *parent, *sz;
static unsigned char *par;          /* par[x] = colour(x) XOR colour(parent[x]) */

/* find root of x; *p receives colour(x) XOR colour(root). Path compression keeps parities. */
static int find(int x, int *p)
{
    int r = x, acc = 0;
    while (parent[r] != r) { acc ^= par[r]; r = parent[r]; }
    *p = acc;
    int cur = x, curp = acc;
    while (cur != r) {
        int next = parent[cur];
        int nextp = curp ^ par[cur];
        parent[cur] = r;
        par[cur] = (unsigned char)curp;
        cur = next;
        curp = nextp;
    }
    return r;
}

static void online(int V, int m, const int *eu, const int *ev)
{
    parent = malloc((V + 1) * sizeof(int));
    sz = malloc((V + 1) * sizeof(int));
    par = calloc(V + 1, 1);
    for (int i = 1; i <= V; i++) { parent[i] = i; sz[i] = 1; }

    int acc = 0, rej = 0;
    printf("\nV = %d, edges arriving online: %d\n\n", V, m);
    for (int k = 0; k < m; k++) {
        int u = eu[k], v = ev[k];
        printf("Edge %3d: (%d, %d) -> ", k + 1, u, v);
        if (u == v) {
            printf("REJECTED (self-loop is an odd cycle of length 1)\n");
            rej++;
            continue;
        }
        int pu, pv;
        int ru = find(u, &pu), rv = find(v, &pv);
        if (ru == rv) {
            if (pu == pv) {
                printf("REJECTED (same colour: would close an odd cycle)\n");
                rej++;
            } else {
                printf("ACCEPTED (same component, colours differ: even cycle or parallel edge)\n");
                acc++;
            }
        } else {
            /* attach the smaller tree under the larger; choose the parity so colours of u, v differ */
            if (sz[ru] < sz[rv]) { int t = ru; ru = rv; rv = t; }
            parent[rv] = ru;
            par[rv] = (unsigned char)(pu ^ pv ^ 1);
            sz[ru] += sz[rv];
            printf("ACCEPTED (merged two components)\n");
            acc++;
        }
    }
    printf("\nAccepted: %d   Rejected: %d   (graph stayed bipartite throughout)\n", acc, rej);
    if (V <= 30) {
        printf("A valid 2-colouring of the final graph:\n  Side 0:");
        for (int v = 1; v <= V; v++) { int p; find(v, &p); if (p == 0) printf(" %d", v); }
        printf("\n  Side 1:");
        for (int v = 1; v <= V; v++) { int p; find(v, &p); if (p == 1) printf(" %d", v); }
        printf("\n");
    }
    free(parent); free(sz); free(par);
}

static void manualInput(void)
{
    int V, m;
    printf("Enter number of vertices V (1-%d): ", MAXV);
    if (scanf("%d", &V) != 1 || V < 1 || V > MAXV) { printf("Invalid V.\n"); return; }
    printf("Enter number of edges m (0-%d): ", MAXM);
    if (scanf("%d", &m) != 1 || m < 0 || m > MAXM) { printf("Invalid m.\n"); return; }
    int *eu = malloc((m + 1) * sizeof(int)), *ev = malloc((m + 1) * sizeof(int));
    printf("Enter %d edges as 'u v' (vertices are 1..%d):\n", m, V);
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 1 || eu[i] > V || ev[i] < 1 || ev[i] > V) {
            printf("Invalid edge.\n"); free(eu); free(ev); return;
        }
    }
    online(V, m, eu, ev);
    free(eu); free(ev);
}

static void generateInput(void)
{
    int V = 5 + rand() % 6, m = 8 + rand() % 8;
    int *eu = malloc(m * sizeof(int)), *ev = malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        eu[i] = 1 + rand() % V;
        do ev[i] = 1 + rand() % V; while (ev[i] == eu[i]);
    }
    printf("Generated random graph: V = %d, m = %d\n", V, m);
    online(V, m, eu, ev);
    free(eu); free(ev);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Online Bipartiteness Testing =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

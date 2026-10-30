/* DAA Lab-11 : Question 1 - Parity-constrained shortest paths via 0-1 BFS on the doubled graph
 *
 * Cost(P) = W(P) + (C if k1(P) is odd else 0), with edge weights in {0,1}.
 * Since every weight-1 edge adds exactly 1 to W(P), we have W(P) = k1(P).
 * State = (vertex, parity of the number of weight-1 edges used so far).
 *   weight-0 edge: (u,p) -> (v,p)     cost 0
 *   weight-1 edge: (u,p) -> (v,1-p)   cost 1
 * dist[v][p] = minimum k1 over all walks S -> v whose k1 has parity p.
 * Cost(v)    = min( dist[v][0], dist[v][1] + C ).
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 1000000
#define MAXE 2000000

typedef long long ll;

static void solve(int V, int E, int S, ll C, const int *eu, const int *ev, const int *ew)
{
    if (V < 1 || V > MAXV || E < 0 || E > MAXE) return;   /* callers validate; this also bounds the sizes */
    /* directed graph in CSR (compressed adjacency) form */
    int *start = calloc(V + 2, sizeof(int));
    int *to = malloc((E + 1) * sizeof(int)), *wt = malloc((E + 1) * sizeof(int));
    for (int i = 0; i < E; i++) start[eu[i] + 1]++;
    for (int v = 1; v <= V + 1; v++) start[v] += start[v - 1];
    int *fill = malloc((V + 2) * sizeof(int));
    for (int v = 0; v <= V + 1; v++) fill[v] = start[v];
    for (int i = 0; i < E; i++) { to[fill[eu[i]]] = ev[i]; wt[fill[eu[i]]++] = ew[i]; }

    size_t NS = 2 * ((size_t)V + 1);                   /* state id = 2*v + parity */
    int *dist = malloc(NS * sizeof(int));
    unsigned char *done = calloc(NS, 1);
    for (size_t i = 0; i < NS; i++) dist[i] = -1;

    /* double-ended queue as a circular buffer; every state-edge is relaxed at most once,
       so at most 1 + 2E entries are ever pushed */
    int cap = 2 * E + 4, head = 0, cnt = 0;
    int *dq = malloc(cap * sizeof(int));
    dist[2 * S] = 0;
    dq[0] = 2 * S; cnt = 1;
    ll pops = 0;
    while (cnt > 0) {
        int s = dq[head]; head = (head + 1) % cap; cnt--;
        if (done[s]) continue;                         /* stale duplicate entry */
        done[s] = 1; pops++;
        int u = s >> 1, p = s & 1;
        for (int j = start[u]; j < start[u + 1]; j++) {
            int v = to[j], w = wt[j];
            int t = 2 * v + (p ^ w);
            int nd = dist[s] + w;
            if (dist[t] < 0 || nd < dist[t]) {
                dist[t] = nd;
                if (w == 0) { head = (head - 1 + cap) % cap; dq[head] = t; }       /* push front */
                else dq[(head + cnt) % cap] = t;                                    /* push back  */
                cnt++;
            }
        }
    }

    printf("\nV = %d, E = %d, source S = %d, odd-parity penalty C = %lld\n", V, E, S, C);
    printf("State graph: %d states, %d transitions; %lld states settled\n\n", 2 * V, 2 * E, pops);
    for (int v = 1; v <= V; v++) {
        int d0 = dist[2 * v], d1 = dist[2 * v + 1];
        printf("Vertex %d: even=", v);
        if (d0 >= 0) printf("%d", d0); else printf("-");
        printf(" odd=");
        if (d1 >= 0) printf("%d", d1); else printf("-");
        printf(" -> Cost = ");
        if (d0 < 0 && d1 < 0) { printf("UNREACHABLE\n"); continue; }
        ll best;
        if (d0 >= 0 && (d1 < 0 || d0 <= d1 + C)) best = d0; else best = d1 + C;
        printf("%lld\n", best);
    }
    free(start); free(to); free(wt); free(fill); free(dist); free(done); free(dq);
}

static void manualInput(void)
{
    int V, E, S;
    ll C;
    printf("Enter number of vertices V (1-%d): ", MAXV);
    if (scanf("%d", &V) != 1 || V < 1 || V > MAXV) { printf("Invalid V.\n"); return; }
    printf("Enter number of directed edges E (0-%d): ", MAXE);
    if (scanf("%d", &E) != 1 || E < 0 || E > MAXE) { printf("Invalid E.\n"); return; }
    printf("Enter source vertex S (1-%d): ", V);
    if (scanf("%d", &S) != 1 || S < 1 || S > V) { printf("Invalid S.\n"); return; }
    printf("Enter penalty C (>= 0): ");
    if (scanf("%lld", &C) != 1 || C < 0) { printf("Invalid C.\n"); return; }
    int *eu = malloc((E + 1) * sizeof(int)), *ev = malloc((E + 1) * sizeof(int)), *ew = malloc((E + 1) * sizeof(int));
    printf("Enter %d edges as 'u v w' with w = 0 or 1 (vertices 1..%d):\n", E, V);
    for (int i = 0; i < E; i++)
        if (scanf("%d %d %d", &eu[i], &ev[i], &ew[i]) != 3 || eu[i] < 1 || eu[i] > V ||
            ev[i] < 1 || ev[i] > V || (ew[i] != 0 && ew[i] != 1)) {
            printf("Invalid edge.\n"); free(eu); free(ev); free(ew); return;
        }
    solve(V, E, S, C, eu, ev, ew);
    free(eu); free(ev); free(ew);
}

static void generateInput(void)
{
    int V = 5 + rand() % 4, E = 8 + rand() % 7, S = 1 + rand() % V;
    ll C = rand() % 6;
    int *eu = malloc(E * sizeof(int)), *ev = malloc(E * sizeof(int)), *ew = malloc(E * sizeof(int));
    printf("Generated random input: V = %d, E = %d, S = %d, C = %lld\nEdges (u -> v : w):", V, E, S, C);
    for (int i = 0; i < E; i++) {
        eu[i] = 1 + rand() % V;
        do ev[i] = 1 + rand() % V; while (ev[i] == eu[i]);
        ew[i] = rand() % 2;
        printf(" %d->%d:%d", eu[i], ev[i], ew[i]);
    }
    printf("\n");
    solve(V, E, S, C, eu, ev, ew);
    free(eu); free(ev); free(ew);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Parity-Constrained Shortest Paths (0-1 BFS) =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

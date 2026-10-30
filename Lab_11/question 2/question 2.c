/* DAA Lab-11 : Question 2 - Multi-source BFS: radius-constrained Voronoi partition of a graph
 *
 * All K hubs are put into the queue at distance 0 (in one BFS).  A vertex v discovered at distance
 * d+1 takes the owner of its discoverer; if another vertex at the same level d also reaches v,
 * the smaller hub index wins.  The search never expands a vertex whose distance already equals R.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 1000000
#define MAXE 2000000

static void solve(int V, int E, const int *eu, const int *ev, int K, const int *hub, int R)
{
    /* undirected graph in CSR form (each edge stored in both directions) */
    int *start = calloc(V + 2, sizeof(int)), *adj = malloc((2 * (size_t)E + 1) * sizeof(int));
    for (int i = 0; i < E; i++) { start[eu[i] + 1]++; start[ev[i] + 1]++; }
    for (int v = 1; v <= V + 1; v++) start[v] += start[v - 1];
    int *fill = malloc((V + 2) * sizeof(int));
    for (int v = 0; v <= V + 1; v++) fill[v] = start[v];
    for (int i = 0; i < E; i++) { adj[fill[eu[i]]++] = ev[i]; adj[fill[ev[i]]++] = eu[i]; }

    int *dist = malloc((V + 1) * sizeof(int)), *owner = malloc((V + 1) * sizeof(int));
    int *queue = malloc((V + 1) * sizeof(int)), head = 0, tail = 0;
    for (int v = 0; v <= V; v++) { dist[v] = -1; owner[v] = -1; }
    for (int i = 0; i < K; i++) { dist[hub[i]] = 0; owner[hub[i]] = i + 1; queue[tail++] = hub[i]; }

    while (head < tail) {
        int u = queue[head++];
        if (dist[u] >= R) continue;                     /* coverage radius reached: do not expand */
        for (int j = start[u]; j < start[u + 1]; j++) {
            int v = adj[j];
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1; owner[v] = owner[u]; queue[tail++] = v;
            } else if (dist[v] == dist[u] + 1 && owner[u] < owner[v]) {
                owner[v] = owner[u];                    /* tie at equal distance: smaller index wins */
            }
        }
    }

    printf("\nV = %d, E = %d, K = %d hubs, radius R = %d\nHubs (index: vertex):", V, E, K, R);
    for (int i = 0; i < K; i++) printf(" %d:%d", i + 1, hub[i]);
    printf("\n\n");
    int *size = calloc(K + 1, sizeof(int)), outside = 0;
    for (int v = 1; v <= V; v++) {
        if (owner[v] > 0) {
            printf("Vertex %d: owner=%d (hub vertex %d) dist=%d\n", v, owner[v], hub[owner[v] - 1], dist[v]);
            size[owner[v]]++;
        } else {
            printf("Vertex %d: owner=-1 dist=-\n", v);
            outside++;
        }
    }
    printf("\nVoronoi cell sizes:");
    for (int i = 1; i <= K; i++) printf(" hub %d -> %d;", i, size[i]);
    printf(" uncovered -> %d\n", outside);
    printf("Vertices visited by the BFS: %d of %d\n", tail, V);
    free(start); free(adj); free(fill); free(dist); free(owner); free(queue); free(size);
}

static void manualInput(void)
{
    int V, E, K, R;
    printf("Enter number of vertices V (1-%d): ", MAXV);
    if (scanf("%d", &V) != 1 || V < 1 || V > MAXV) { printf("Invalid V.\n"); return; }
    printf("Enter number of undirected edges E (0-%d): ", MAXE);
    if (scanf("%d", &E) != 1 || E < 0 || E > MAXE) { printf("Invalid E.\n"); return; }
    int *eu = malloc((E + 1) * sizeof(int)), *ev = malloc((E + 1) * sizeof(int));
    printf("Enter %d edges as 'u v' (vertices 1..%d):\n", E, V);
    for (int i = 0; i < E; i++)
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 1 || eu[i] > V || ev[i] < 1 || ev[i] > V) {
            printf("Invalid edge.\n"); free(eu); free(ev); return;
        }
    printf("Enter number of hubs K (1-%d): ", V);
    if (scanf("%d", &K) != 1 || K < 1 || K > V) { printf("Invalid K.\n"); free(eu); free(ev); return; }
    int *hub = malloc(K * sizeof(int));
    unsigned char *seen = calloc(V + 1, 1);
    printf("Enter the %d distinct hub vertices h1..hK: ", K);
    for (int i = 0; i < K; i++) {
        if (scanf("%d", &hub[i]) != 1 || hub[i] < 1 || hub[i] > V || seen[hub[i]]) {
            printf("Invalid or repeated hub.\n"); free(eu); free(ev); free(hub); free(seen); return;
        }
        seen[hub[i]] = 1;
    }
    free(seen);
    printf("Enter radius R (>= 0): ");
    if (scanf("%d", &R) != 1 || R < 0) { printf("Invalid R.\n"); free(eu); free(ev); free(hub); return; }
    solve(V, E, eu, ev, K, hub, R);
    free(eu); free(ev); free(hub);
}

static void generateInput(void)
{
    int V = 8 + rand() % 7, E = V + rand() % 6, K = 2 + rand() % 2, R = 1 + rand() % 3;
    int *eu = malloc(E * sizeof(int)), *ev = malloc(E * sizeof(int)), *hub = malloc(K * sizeof(int));
    for (int i = 0; i < E; i++) {
        eu[i] = 1 + rand() % V;
        do ev[i] = 1 + rand() % V; while (ev[i] == eu[i]);
    }
    for (int i = 0; i < K; i++) {
        int ok;
        do {
            hub[i] = 1 + rand() % V; ok = 1;
            for (int j = 0; j < i; j++) if (hub[j] == hub[i]) ok = 0;
        } while (!ok);
    }
    printf("Generated random input: V = %d, E = %d, K = %d, R = %d\nEdges:", V, E, K, R);
    for (int i = 0; i < E; i++) printf(" (%d,%d)", eu[i], ev[i]);
    printf("\n");
    solve(V, E, eu, ev, K, hub, R);
    free(eu); free(ev); free(hub);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Multi-Source BFS: Voronoi Cell Partitioning =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

/* DAA Lab-10 : Question 3 - Maximum weight component with size constraint (DSU + lazy max-heap) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 1000000
#define MAXE 1000000

typedef struct { long long w; int r; } Item;

static int *parent, *sz, K;
static long long *W;
static Item *heap;
static int hn;

static int find(int x)
{
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }
    return x;
}

static void push(Item it)
{
    int i = hn++;
    heap[i] = it;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].w >= heap[i].w) break;
        Item t = heap[p]; heap[p] = heap[i]; heap[i] = t;
        i = p;
    }
}

static void pop(void)
{
    heap[0] = heap[--hn];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, b = i;
        if (l < hn && heap[l].w > heap[b].w) b = l;
        if (r < hn && heap[r].w > heap[b].w) b = r;
        if (b == i) break;
        Item t = heap[b]; heap[b] = heap[i]; heap[i] = t;
        i = b;
    }
}

/* An entry is current iff its root is still a root, its weight is unchanged and the size is <= K */
static int valid(Item it)
{
    return parent[it.r] == it.r && W[it.r] == it.w && sz[it.r] <= K;
}

static void report(const char *label)
{
    while (hn > 0 && !valid(heap[0])) pop();
    if (hn == 0) printf("%s max eligible weight = none (no component has size <= %d)\n", label, K);
    else printf("%s max eligible weight = %lld (component size %d)\n", label, heap[0].w, sz[heap[0].r]);
}

static void solve(int V, int E, const long long *w, const int *eu, const int *ev, const long long *ew, int k)
{
    K = k;
    parent = malloc((V + 1) * sizeof(int));
    sz = malloc((V + 1) * sizeof(int));
    W = malloc((V + 1) * sizeof(long long));
    heap = malloc(((size_t)V + E + 1) * sizeof(Item));
    hn = 0;
    for (int i = 1; i <= V; i++) {
        parent[i] = i; sz[i] = 1; W[i] = w[i];
        if (sz[i] <= K) { Item it = {W[i], i}; push(it); }
    }

    printf("\nV = %d, E = %d, size limit K = %d\nVertex weights:", V, E, K);
    for (int i = 1; i <= V; i++) printf(" %lld", w[i]);
    printf("\n\n");
    report("Initially:           ");
    for (int i = 0; i < E; i++) {
        int a = find(eu[i]), b = find(ev[i]);
        if (a != b) {
            if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
            parent[b] = a;
            sz[a] += sz[b];
            W[a] += W[b];
            if (sz[a] <= K) { Item it = {W[a], a}; push(it); }
        }
        char label[64];
        snprintf(label, sizeof label, "After edge %3d (%d,%d,w=%lld):", i + 1, eu[i], ev[i], ew[i]);
        report(label);
    }
    free(parent); free(sz); free(W); free(heap);
}

static void manualInput(void)
{
    int V, E, k;
    printf("Enter number of vertices V (1-%d): ", MAXV);
    if (scanf("%d", &V) != 1 || V < 1 || V > MAXV) { printf("Invalid V.\n"); return; }
    long long *w = malloc((V + 1) * sizeof(long long));
    printf("Enter the %d vertex weights: ", V);
    for (int i = 1; i <= V; i++)
        if (scanf("%lld", &w[i]) != 1) { printf("Invalid weight.\n"); free(w); return; }
    printf("Enter number of edges E (0-%d): ", MAXE);
    if (scanf("%d", &E) != 1 || E < 0 || E > MAXE) { printf("Invalid E.\n"); free(w); return; }
    int *eu = malloc((E + 1) * sizeof(int)), *ev = malloc((E + 1) * sizeof(int));
    long long *ew = malloc((E + 1) * sizeof(long long));
    printf("Enter %d edges as 'u v weight' (vertices 1..%d):\n", E, V);
    for (int i = 0; i < E; i++)
        if (scanf("%d %d %lld", &eu[i], &ev[i], &ew[i]) != 3 || eu[i] < 1 || eu[i] > V || ev[i] < 1 || ev[i] > V) {
            printf("Invalid edge.\n"); free(w); free(eu); free(ev); free(ew); return;
        }
    printf("Enter size threshold K (>= 1): ");
    if (scanf("%d", &k) != 1 || k < 1) { printf("Invalid K.\n"); free(w); free(eu); free(ev); free(ew); return; }
    solve(V, E, w, eu, ev, ew, k);
    free(w); free(eu); free(ev); free(ew);
}

static void generateInput(void)
{
    int V = 6 + rand() % 4, E = 6 + rand() % 5, k = 3 + rand() % 3;
    long long *w = malloc((V + 1) * sizeof(long long)), *ew = malloc(E * sizeof(long long));
    int *eu = malloc(E * sizeof(int)), *ev = malloc(E * sizeof(int));
    for (int i = 1; i <= V; i++) w[i] = 1 + rand() % 20;
    for (int i = 0; i < E; i++) {
        eu[i] = 1 + rand() % V;
        do ev[i] = 1 + rand() % V; while (ev[i] == eu[i]);
        ew[i] = 1 + rand() % 9;
    }
    printf("Generated random input: V = %d, E = %d, K = %d\n", V, E, k);
    solve(V, E, w, eu, ev, ew, k);
    free(w); free(eu); free(ev); free(ew);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Maximum Weight Component with Size Constraint =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

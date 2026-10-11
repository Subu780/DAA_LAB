/* Q9: Hu-Tucker algorithm (optimal alphabetic binary tree) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 200
#ifndef PLACE_LEFT
#define PLACE_LEFT 1
#endif
static long long val[2 * MAXN];
static int lc[2 * MAXN], rc[2 * MAXN], term[2 * MAXN], depth_[MAXN];
static int order_[2 * MAXN];

static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static void dfs(int v, int n, int d) {
    if (v < n) { depth_[v] = d; return; }
    dfs(lc[v], n, d + 1); dfs(rc[v], n, d + 1);
}
/* Phase 1: combination. Returns total cost; fills depth_[] (leaf levels). */
static long long hu_tucker(const long long *w, int n) {
    int m = n, nodes = n; long long cost = 0;
    for (int i = 0; i < n; i++) { val[i] = w[i]; term[i] = 1; order_[i] = i; }
    while (m > 1) {
        long long best = -1; int bi = -1, bj = -1;
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++) {
                long long s = val[order_[i]] + val[order_[j]];
                if (best < 0 || s < best) { best = s; bi = i; bj = j; }
                if (term[order_[j]]) break;          /* a terminal blocks every farther j */
            }
        int a = order_[bi], b = order_[bj], v = nodes++;
        val[v] = best; lc[v] = a; rc[v] = b; term[v] = 0; cost += best;
        int keep = PLACE_LEFT ? bi : bj, drop = PLACE_LEFT ? bj : bi;
        order_[keep] = v;
        for (int k = drop; k < m - 1; k++) order_[k] = order_[k + 1];
        m--;
    }
    dfs(order_[0], n, 0);
    return cost;
}
/* Phase 2: rebuild an ordered tree from the leaf levels with a stack */
static char *build(const int *lv, int n) {
    static char *st[MAXN]; static int sl[MAXN]; int sp = 0;
    for (int i = 0; i < n; i++) {
        char buf[16]; snprintf(buf, sizeof buf, "%d", i + 1);
        st[sp] = strdup(buf); sl[sp] = lv[i]; sp++;
        while (sp >= 2 && sl[sp - 1] == sl[sp - 2]) {
            char *t = malloc(strlen(st[sp - 2]) + strlen(st[sp - 1]) + 4);
            sprintf(t, "(%s %s)", st[sp - 2], st[sp - 1]);
            free(st[sp - 2]); free(st[sp - 1]); sp--; st[sp - 1] = t; sl[sp - 1]--;
        }
    }
    return (sp == 1 && sl[0] == 0) ? st[0] : strdup("<invalid>");
}
static long long dpc(const long long *w, int n) {      /* O(n^3) interval DP */
    static long long c[MAXN][MAXN], pre[MAXN + 1];
    pre[0] = 0; for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[i];
    for (int i = 0; i < n; i++) c[i][i] = 0;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1; long long b = -1;
            for (int k = i; k < j; k++) { long long t = c[i][k] + c[k + 1][j]; if (b < 0 || t < b) b = t; }
            c[i][j] = b + pre[j + 1] - pre[i];
        }
    return c[0][n - 1];
}
int main(void) {
    long long w[MAXN]; int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of weights: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        printf("Weights in order: "); for (int i = 0; i < n; i++) if (scanf("%lld", &w[i]) != 1) return 1;
    } else {
        unsigned seed; printf("n and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) w[i] = 1 + rand() % 30;
    }
    printf("\nWeights:"); for (int i = 0; i < n; i++) printf(" %lld", w[i]); printf("\n");
    long long cost = hu_tucker(w, n);
    printf("Leaf levels (phase 1):"); for (int i = 0; i < n; i++) printf(" %d", depth_[i]); printf("\n");
    char *t = build(depth_, n);
    long long chk = 0; for (int i = 0; i < n; i++) chk += w[i] * depth_[i];
    printf("Phase 2 tree (in-order 1..n): %s\n", t);
    printf("Optimal cost sum(w_i*depth_i) = %lld (merge-sum = %lld)\n", chk, cost);
    long long d = dpc(w, n);
    printf("Interval-DP optimum           = %lld -> %s\n", d, (d == cost && chk == cost) ? "PASS" : "FAIL");
    return 0;
}

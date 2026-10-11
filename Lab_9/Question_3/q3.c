/* Q3: Minimum number of refuelling stops (max-heap greedy) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 1000
typedef struct { long long d, f; } St;
static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static int cmp_st(const void *a, const void *b) { const St *x = a, *y = b; return (x->d > y->d) - (x->d < y->d); }
static long long hp[MAXN + 1]; static int hs;
static void push(long long x) {
    int i = hs++; hp[i] = x;
    while (i > 0 && hp[i] > hp[(i - 1) / 2]) { int p = (i - 1) / 2; long long t = hp[i]; hp[i] = hp[p]; hp[p] = t; i = p; }
}
static long long pop(void) {
    long long r = hp[0]; hp[0] = hp[--hs]; int i = 0;
    for (;;) {
        int l = 2 * i + 1, rr = l + 1, m = i;
        if (l < hs && hp[l] > hp[m]) m = l;
        if (rr < hs && hp[rr] > hp[m]) m = rr;
        if (m == i) break;
        long long t = hp[i]; hp[i] = hp[m]; hp[m] = t; i = m;
    }
    return r;
}
static int greedy(St *s, int n, long long D, long long F) {
    hs = 0; long long cur = F; int stops = 0, i = 0;
    while (cur < D) {
        while (i < n && s[i].d <= cur) push(s[i++].f);
        if (hs == 0) return -1;
        cur += pop(); stops++;
    }
    return stops;
}
static int dp_check(St *s, int n, long long D, long long F) {
    long long dp[MAXN + 1]; dp[0] = F; for (int k = 1; k <= n; k++) dp[k] = -1;
    for (int i = 0; i < n; i++)
        for (int k = i + 1; k >= 1; k--) if (dp[k - 1] >= s[i].d && dp[k - 1] + s[i].f > dp[k]) dp[k] = dp[k - 1] + s[i].f;
    for (int k = 0; k <= n; k++) if (dp[k] >= D) return k;
    return -1;
}
int main(void) {
    St s[MAXN]; int n; long long D, F;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Target D, initial fuel F, number of stations n: "); if (scanf("%lld %lld %d", &D, &F, &n) != 3) return 1;
        for (int i = 0; i < n; i++) { printf("Station %d (distance fuel): ", i + 1); if (scanf("%lld %lld", &s[i].d, &s[i].f) != 2) return 1; }
    } else {
        unsigned seed; printf("n, D, seed(0=time): "); if (scanf("%d %lld %u", &n, &D, &seed) != 3) return 1;
        srand(seed ? seed : (unsigned)time(NULL));
        F = 1 + D / 5;
        for (int i = 0; i < n; i++) { s[i].d = 1 + rand() % (D - 1); s[i].f = 1 + rand() % (D / 4 + 1); }
    }
    if (n < 0 || n > MAXN) { printf("n out of range\n"); return 1; }
    qsort(s, n, sizeof(St), cmp_st);
    printf("\nTarget D = %lld, initial fuel F = %lld\nStations (distance, fuel):", D, F);
    for (int i = 0; i < n; i++) printf(" (%lld,%lld)", s[i].d, s[i].f);
    int g = greedy(s, n, D, F), c = dp_check(s, n, D, F);
    if (g < 0) printf("\n\nResult: target cannot be reached (-1)\n"); else printf("\n\nMinimum refuelling stops = %d\n", g);
    printf("Validation (DP over stops) = %d -> %s\n", c, c == g ? "PASS" : "FAIL");
    return 0;
}

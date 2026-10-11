/* Q7: Minimise deviation in array (max-heap, two-way greedy) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100000
static long long hp[MAXN + 1]; static int hs;
static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
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
static long long solve(const long long *a, int n) {
    hs = 0; long long mn = -1;
    for (int i = 0; i < n; i++) {
        long long x = a[i] % 2 ? a[i] * 2 : a[i];
        push(x); if (mn < 0 || x < mn) mn = x;
    }
    long long best = hp[0] - mn;
    while (hs) {
        long long t = pop();
        if (t - mn < best) best = t - mn;
        if (t % 2) break;
        t /= 2; if (t < mn) mn = t; push(t);
    }
    return best;
}
static long long bf_best; static long long cur[16];
static void bf(const long long *a, int i, int n) {
    if (i == n) {
        long long mx = cur[0], mn = cur[0];
        for (int k = 1; k < n; k++) { if (cur[k] > mx) mx = cur[k]; if (cur[k] < mn) mn = cur[k]; }
        if (bf_best < 0 || mx - mn < bf_best) bf_best = mx - mn;
        return;
    }
    long long x = a[i];
    if (x % 2) { cur[i] = x; bf(a, i + 1, n); cur[i] = 2 * x; bf(a, i + 1, n); }
    else for (long long v = x;; v /= 2) { cur[i] = v; bf(a, i + 1, n); if (v % 2) break; }
}
int main(void) {
    static long long a[MAXN]; int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Array size: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        printf("Elements (positive): "); for (int i = 0; i < n; i++) if (scanf("%lld", &a[i]) != 1) return 1;
    } else {
        unsigned seed; printf("n and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) a[i] = 1 + rand() % 60;
    }
    if (n <= 30) { printf("\nArray:"); for (int i = 0; i < n; i++) printf(" %lld", a[i]); printf("\n"); }
    long long mx = a[0], mn = a[0];
    for (int i = 1; i < n; i++) { if (a[i] > mx) mx = a[i]; if (a[i] < mn) mn = a[i]; }
    long long r = solve(a, n);
    printf("Initial deviation = %lld\nMinimum deviation = %lld\n", mx - mn, r);
    if (n <= 8) { bf_best = -1; bf(a, 0, n); printf("Brute force       = %lld -> %s\n", bf_best, bf_best == r ? "PASS" : "FAIL"); }
    else printf("(Brute-force check runs only when n<=8)\n");
    return 0;
}

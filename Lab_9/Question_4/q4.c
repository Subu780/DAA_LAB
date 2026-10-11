/* Q4: Minimum cost to connect sticks (min-heap, Huffman-style) */
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
    while (i > 0 && hp[i] < hp[(i - 1) / 2]) { int p = (i - 1) / 2; long long t = hp[i]; hp[i] = hp[p]; hp[p] = t; i = p; }
}
static long long pop(void) {
    long long r = hp[0]; hp[0] = hp[--hs]; int i = 0;
    for (;;) {
        int l = 2 * i + 1, rr = l + 1, m = i;
        if (l < hs && hp[l] < hp[m]) m = l;
        if (rr < hs && hp[rr] < hp[m]) m = rr;
        if (m == i) break;
        long long t = hp[i]; hp[i] = hp[m]; hp[m] = t; i = m;
    }
    return r;
}
static long long brute(long long *a, int n) {
    if (n == 1) return 0;
    long long best = -1;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
        long long b[16], s = a[i] + a[j]; int m = 0;
        for (int k = 0; k < n; k++) if (k != i && k != j) b[m++] = a[k];
        b[m++] = s;
        long long c = s + brute(b, m);
        if (best < 0 || c < best) best = c;
    }
    return best;
}
int main(void) {
    static long long L[MAXN]; int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of sticks: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        printf("Lengths: "); for (int i = 0; i < n; i++) if (scanf("%lld", &L[i]) != 1) return 1;
    } else {
        unsigned seed; printf("n and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) L[i] = 1 + rand() % 20;
    }
    if (n <= 20) { printf("\nSticks:"); for (int i = 0; i < n; i++) printf(" %lld", L[i]); printf("\n"); }
    hs = 0; for (int i = 0; i < n; i++) push(L[i]);
    long long cost = 0; int step = 1;
    while (hs > 1) {
        long long x = pop(), y = pop(); cost += x + y; push(x + y);
        if (n <= 20) printf("  step %d: join %lld + %lld -> %lld (cost so far %lld)\n", step, x, y, x + y, cost);
        step++;
    }
    printf("Minimum total cost = %lld\n", cost);
    if (n <= 8) { long long b = brute(L, n); printf("Brute force        = %lld -> %s\n", b, b == cost ? "PASS" : "FAIL"); }
    else printf("(Brute-force check runs only when n<=8)\n");
    return 0;
}

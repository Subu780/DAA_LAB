/* Q5: Candy distribution (two-pass slope greedy) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100000
static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static long long two_pass(const int *r, int n, int *c) {
    for (int i = 0; i < n; i++) c[i] = 1;
    for (int i = 1; i < n; i++) if (r[i] > r[i - 1]) c[i] = c[i - 1] + 1;           /* left -> right */
    for (int i = n - 2; i >= 0; i--) if (r[i] > r[i + 1] && c[i] <= c[i + 1]) c[i] = c[i + 1] + 1; /* right -> left */
    long long s = 0; for (int i = 0; i < n; i++) s += c[i];
    return s;
}
static long long one_pass(const int *r, int n) {      /* O(1) extra space, counts up/down slopes */
    long long total = 1; int up = 0, down = 0, peak = 0;
    for (int i = 1; i < n; i++) {
        if (r[i] > r[i - 1]) { up++; peak = up; down = 0; total += 1 + up; }
        else if (r[i] == r[i - 1]) { up = down = peak = 0; total += 1; }
        else { up = 0; down++; total += 1 + down; if (peak >= down) total--; }
    }
    return total;
}
static int cand[10], rr[10]; static long long best;
static int ok(int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0 && rr[i] > rr[i - 1] && cand[i] <= cand[i - 1]) return 0;
        if (i < n - 1 && rr[i] > rr[i + 1] && cand[i] <= cand[i + 1]) return 0;
    }
    return 1;
}
static void bf(int i, int n, long long s) {
    if (i == n) { if (ok(n) && (best < 0 || s < best)) best = s; return; }
    for (int v = 1; v <= n; v++) { cand[i] = v; bf(i + 1, n, s + v); }
}
int main(void) {
    static int r[MAXN], c[MAXN]; int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of children: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        printf("Ratings: "); for (int i = 0; i < n; i++) if (scanf("%d", &r[i]) != 1) return 1;
    } else {
        unsigned seed; printf("n and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) r[i] = 1 + rand() % 9;
    }
    long long t = two_pass(r, n, c);
    if (n <= 30) {
        printf("\nRatings:"); for (int i = 0; i < n; i++) printf(" %d", r[i]);
        printf("\nCandies:"); for (int i = 0; i < n; i++) printf(" %d", c[i]); printf("\n");
    }
    printf("Minimum total candies = %lld\n", t);
    long long o = one_pass(r, n);
    printf("One-pass slope method = %lld -> %s\n", o, o == t ? "PASS" : "FAIL");
    if (n <= 7) {
        for (int i = 0; i < n; i++) rr[i] = r[i];
        best = -1; bf(0, n, 0);
        printf("Brute force           = %lld -> %s\n", best, best == t ? "PASS" : "FAIL");
    } else printf("(Brute-force check runs only when n<=7)\n");
    return 0;
}

/* Q6: Reorganise string so equal characters are >= K apart (max-heap + cooldown) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXL 4096
static int cnt[256], hp[256], hs;
static int better(int a, int b) { return cnt[a] != cnt[b] ? cnt[a] > cnt[b] : a < b; }
static void push(int x) {
    int i = hs++; hp[i] = x;
    while (i > 0 && better(hp[i], hp[(i - 1) / 2])) { int p = (i - 1) / 2, t = hp[i]; hp[i] = hp[p]; hp[p] = t; i = p; }
}
static int pop(void) {
    int r = hp[0]; hp[0] = hp[--hs]; int i = 0;
    for (;;) {
        int l = 2 * i + 1, rr = l + 1, m = i;
        if (l < hs && better(hp[l], hp[m])) m = l;
        if (rr < hs && better(hp[rr], hp[m])) m = rr;
        if (m == i) break;
        int t = hp[i]; hp[i] = hp[m]; hp[m] = t; i = m;
    }
    return r;
}
static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
/* returns 1 and fills res, or 0 if impossible */
static int reorganize(const char *s, int K, char *res) {
    int n = strlen(s); if (K < 1) K = 1;
    memset(cnt, 0, sizeof cnt); hs = 0;
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    for (int c = 0; c < 256; c++) if (cnt[c]) push(c);
    for (int i = 0; i < n; i++) {
        if (hs == 0) return 0;
        int c = pop(); res[i] = (char)c; cnt[c]--;
        if (i - K + 1 >= 0) { int d = (unsigned char)res[i - K + 1]; if (cnt[d] > 0) push(d); }
    }
    res[n] = 0; return 1;
}
/* brute-force feasibility by backtracking */
static int bc[256], last[256], bn, bK;
static int dfs(int pos) {
    if (pos == bn) return 1;
    for (int c = 0; c < 256; c++) if (bc[c] > 0 && (last[c] < 0 || pos - last[c] >= bK)) {
        int old = last[c]; bc[c]--; last[c] = pos;
        if (dfs(pos + 1)) { bc[c]++; last[c] = old; return 1; }
        bc[c]++; last[c] = old;
    }
    return 0;
}
int main(void) {
    char S[MAXL], res[MAXL]; int K;
    int mode = choose_mode();
    if (mode == 1) {
        printf("String S (no spaces): "); if (scanf("%4000s", S) != 1) return 1;
        printf("K: "); if (scanf("%d", &K) != 1) return 1;
    } else {
        int n, m; unsigned seed;
        printf("length n, alphabet size m (<=26), K, seed(0=time): "); if (scanf("%d %d %d %u", &n, &m, &K, &seed) != 4) return 1;
        if (n < 1 || n > 4000 || m < 1 || m > 26) { printf("bad parameters\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) S[i] = 'a' + rand() % m;
        S[n] = 0;
    }
    printf("\nS = \"%s\", K = %d\n", S, K);
    int ok = reorganize(S, K, res);
    if (ok) printf("Rearranged: \"%s\"\n", res); else printf("Rearranged: \"\" (impossible)\n");
    int valid = 1;
    if (ok) {
        int a[256] = {0}, b[256] = {0}, n = strlen(S);
        for (int i = 0; i < n; i++) { a[(unsigned char)S[i]]++; b[(unsigned char)res[i]]++; }
        for (int c = 0; c < 256; c++) if (a[c] != b[c]) valid = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n && j < i + K; j++) if (res[i] == res[j]) valid = 0;
        printf("Output check (same letters, spacing >= K): %s\n", valid ? "PASS" : "FAIL");
    }
    int n = strlen(S);
    if (n <= 10) {
        memset(bc, 0, sizeof bc); for (int c = 0; c < 256; c++) last[c] = -1;
        for (int i = 0; i < n; i++) bc[(unsigned char)S[i]]++;
        bn = n; bK = K < 1 ? 1 : K;
        int f = dfs(0);
        printf("Brute-force feasibility = %s -> %s\n", f ? "possible" : "impossible", (f == ok && valid) ? "PASS" : "FAIL");
    } else printf("(Brute-force check runs only when |S|<=10)\n");
    return 0;
}

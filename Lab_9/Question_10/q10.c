/* Q10: Greedy Superstring (max-overlap merging) vs exact optimum (bitmask DP) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 12
#define MAXL 32
#define BUF (MAXN * MAXL + 1)
static char S[MAXN][MAXL + 1];
static char G[MAXN][BUF];

static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static int overlap(const char *a, const char *b) {
    int la = strlen(a), lb = strlen(b), m = la < lb ? la : lb;
    for (int k = m; k > 0; k--) if (strncmp(a + la - k, b, k) == 0) return k;
    return 0;
}
/* remove duplicates and strings contained in another string */
static int reduce(char in[][MAXL + 1], int n, char out[][MAXL + 1]) {
    int m = 0;
    for (int i = 0; i < n; i++) {
        int drop = 0;
        for (int j = 0; j < n && !drop; j++) {
            if (i == j) continue;
            if (strstr(in[j], in[i])) { if (strlen(in[j]) > strlen(in[i]) || j < i) drop = 1; }
        }
        if (!drop) strcpy(out[m++], in[i]);
    }
    return m;
}
static int greedy(char w[][MAXL + 1], int m, char *result, int verbose) {
    for (int i = 0; i < m; i++) strcpy(G[i], w[i]);
    int cnt = m;
    while (cnt > 1) {
        int bo = -1, bi = 0, bj = 1;
        for (int i = 0; i < cnt; i++) for (int j = 0; j < cnt; j++) if (i != j) {
            int o = overlap(G[i], G[j]);
            if (o > bo) { bo = o; bi = i; bj = j; }
        }
        char merged[BUF];
        snprintf(merged, sizeof merged, "%s%s", G[bi], G[bj] + bo);
        if (verbose) printf("  merge \"%s\" + \"%s\" (overlap %d) -> \"%s\"\n", G[bi], G[bj], bo, merged);
        strcpy(G[bi], merged);
        for (int k = bj; k < cnt - 1; k++) strcpy(G[k], G[k + 1]);
        cnt--;
    }
    strcpy(result, G[0]);
    return strlen(result);
}
static int optimal(char w[][MAXL + 1], int m) {
    static int ov[MAXN][MAXN], dp[1 << MAXN][MAXN];
    int total = 0;
    for (int i = 0; i < m; i++) { total += strlen(w[i]); for (int j = 0; j < m; j++) ov[i][j] = i == j ? 0 : overlap(w[i], w[j]); }
    for (int mask = 0; mask < (1 << m); mask++) for (int l = 0; l < m; l++) dp[mask][l] = -1;
    for (int i = 0; i < m; i++) dp[1 << i][i] = 0;
    for (int mask = 1; mask < (1 << m); mask++) for (int l = 0; l < m; l++) if (dp[mask][l] >= 0)
        for (int nx = 0; nx < m; nx++) if (!(mask & (1 << nx))) {
            int nm = mask | (1 << nx), v = dp[mask][l] + ov[l][nx];
            if (v > dp[nm][nx]) dp[nm][nx] = v;
        }
    int best = 0; for (int l = 0; l < m; l++) if (dp[(1 << m) - 1][l] > best) best = dp[(1 << m) - 1][l];
    return total - best;
}
int main(void) {
    int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of strings (<=%d): ", MAXN); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        for (int i = 0; i < n; i++) { printf("String %d: ", i + 1); if (scanf("%32s", S[i]) != 1) return 1; }
    } else {
        int k, A; unsigned seed;
        printf("n (<=%d), string length k (<=%d), alphabet size (<=26), seed(0=time): ", MAXN, MAXL);
        if (scanf("%d %d %d %u", &n, &k, &A, &seed) != 4) return 1;
        if (n < 1 || n > MAXN || k < 1 || k > MAXL || A < 1 || A > 26) { printf("bad parameters\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) { for (int j = 0; j < k; j++) S[i][j] = 'a' + rand() % A; S[i][k] = 0; }
    }
    printf("\nInput strings:"); for (int i = 0; i < n; i++) printf(" %s", S[i]); printf("\n");
    static char W[MAXN][MAXL + 1]; int m = reduce(S, n, W);
    printf("After removing duplicates/substrings: %d string(s)\n", m);
    char res[BUF]; printf("Greedy merges:\n");
    int g = greedy(W, m, res, 1);
    printf("Greedy superstring  : %s (length %d)\n", res, g);
    int ok = 1; for (int i = 0; i < n; i++) if (!strstr(res, S[i])) ok = 0;
    printf("Contains every input string: %s\n", ok ? "PASS" : "FAIL");
    int o = optimal(W, m);
    printf("Optimal length (DP)  : %d\nGreedy / Optimal     : %.4f\n", o, (double)g / o);
    printf("Greedy is optimal here: %s\n", g == o ? "yes" : "no");
    return 0;
}

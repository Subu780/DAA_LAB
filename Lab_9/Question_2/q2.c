/* Q2: Huffman Coding with canonical codebook */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXS 64
static int n;
static char sym[MAXS];
static long long nf[2 * MAXS];
static int nl[2 * MAXS], nr[2 * MAXS], heap[2 * MAXS], hs, len_[MAXS];

static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static int less(int a, int b) { return nf[a] != nf[b] ? nf[a] < nf[b] : a < b; }
static void hpush(int x) {
    int i = hs++; heap[i] = x;
    while (i > 0 && less(heap[i], heap[(i - 1) / 2])) { int p = (i - 1) / 2, t = heap[i]; heap[i] = heap[p]; heap[p] = t; i = p; }
}
static int hpop(void) {
    int r = heap[0]; heap[0] = heap[--hs]; int i = 0;
    for (;;) {
        int l = 2 * i + 1, rr = l + 1, m = i;
        if (l < hs && less(heap[l], heap[m])) m = l;
        if (rr < hs && less(heap[rr], heap[m])) m = rr;
        if (m == i) break;
        int t = heap[i]; heap[i] = heap[m]; heap[m] = t; i = m;
    }
    return r;
}
static void dfs(int v, int d) {
    if (v < n) { len_[v] = d ? d : 1; return; }
    dfs(nl[v], d + 1); dfs(nr[v], d + 1);
}
static int cmp_ll(const void *a, const void *b) { long long x = *(long long *)a, y = *(long long *)b; return (x > y) - (x < y); }

int main(void) {
    long long fr[MAXS];
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of symbols: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXS) { printf("n out of range\n"); return 1; }
        for (int i = 0; i < n; i++) { printf("Symbol %d (char freq): ", i + 1); if (scanf(" %c %lld", &sym[i], &fr[i]) != 2) return 1; }
    } else {
        unsigned seed; printf("n (<=26) and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > 26) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) { sym[i] = 'a' + i; fr[i] = 1 + rand() % 50; }
    }
    for (int i = 0; i < n; i++) nf[i] = fr[i];
    hs = 0; for (int i = 0; i < n; i++) hpush(i);
    int cnt = n;
    while (hs > 1) {
        int a = hpop(), b = hpop();
        nf[cnt] = nf[a] + nf[b]; nl[cnt] = a; nr[cnt] = b; hpush(cnt++);
    }
    dfs(heap[0], 0);
    int ord[MAXS]; for (int i = 0; i < n; i++) ord[i] = i;
    for (int i = 1; i < n; i++) {                  /* sort by (length, symbol) */
        int x = ord[i], j = i - 1;
        while (j >= 0 && (len_[ord[j]] > len_[x] || (len_[ord[j]] == len_[x] && sym[ord[j]] > sym[x]))) { ord[j + 1] = ord[j]; j--; }
        ord[j + 1] = x;
    }
    unsigned long long code[MAXS], c = 0; int prev = len_[ord[0]];
    for (int k = 0; k < n; k++) {
        if (k > 0) c = (c + 1) << (len_[ord[k]] - prev);
        code[ord[k]] = c; prev = len_[ord[k]];
    }
    printf("\nCanonical Huffman codebook:\n sym  freq  len  code\n");
    long long cost = 0;
    for (int k = 0; k < n; k++) {
        int s = ord[k];
        printf("  %c  %5lld  %3d  ", sym[s], fr[s], len_[s]);
        for (int b = len_[s] - 1; b >= 0; b--) putchar('0' + (int)((code[s] >> b) & 1));
        putchar('\n'); cost += fr[s] * len_[s];
    }
    long long tot = 0; for (int i = 0; i < n; i++) tot += fr[i];
    printf("Total encoded length = %lld bits, average = %.4f bits/symbol\n", cost, (double)cost / tot);
    /* validation 1: two-queue Huffman cost; 2: Kraft equality; 3: prefix-free */
    long long s1[MAXS], q2[MAXS]; for (int i = 0; i < n; i++) s1[i] = fr[i];
    qsort(s1, n, sizeof(long long), cmp_ll);
    int i1 = 0, h2 = 0, t2 = 0; long long c2 = 0;
    for (int m = 0; m < n - 1; m++) {
        long long s = 0;
        for (int t = 0; t < 2; t++) {
            if (i1 < n && (h2 == t2 || s1[i1] <= q2[h2])) s += s1[i1++]; else s += q2[h2++];
        }
        q2[t2++] = s; c2 += s;
    }
    int maxl = 0; for (int i = 0; i < n; i++) if (len_[i] > maxl) maxl = len_[i];
    unsigned long long kraft = 0; for (int i = 0; i < n; i++) kraft += 1ULL << (maxl - len_[i]);
    int pf = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        if (i != j && len_[i] <= len_[j] && (code[j] >> (len_[j] - len_[i])) == code[i]) pf = 0;
    int ok = (c2 == cost) && (n == 1 || kraft == (1ULL << maxl)) && pf;
    printf("Validation: two-queue cost = %lld, Kraft sum = 1: %s, prefix-free: %s -> %s\n",
           c2, (n == 1 || kraft == (1ULL << maxl)) ? "yes" : "no", pf ? "yes" : "no", ok ? "PASS" : "FAIL");
    return 0;
}

/* DAA Lab-11 : Question 3 - Word ladder with bidirectional BFS
 *
 * The word graph is never built explicitly (it can have Theta(N^2) edges).  Instead every word is
 * indexed under its L "wildcard patterns" (e.g. hot -> *ot, h*t, ho*).  Two words are neighbours
 * iff they share a pattern, so the neighbours of x are the other members of its L buckets.
 * A bucket is scanned at most once per search direction.
 * A pattern is packed exactly into a 64-bit integer (base 27, wildcard = 26): 27^10 < 2^63.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 100000
#define MAXL 10

typedef unsigned long long u64;
typedef struct { u64 key; char s[MAXL + 1]; } Word;
typedef struct { u64 key; int node; int pos; } Entry;

static int cmpWord(const void *a, const void *b)
{
    u64 x = ((const Word *)a)->key, y = ((const Word *)b)->key;
    return x < y ? -1 : x > y;
}

static int cmpEntry(const void *a, const void *b)
{
    const Entry *x = a, *y = b;
    if (x->key != y->key) return x->key < y->key ? -1 : 1;
    return x->node - y->node;
}

static u64 wordKey(const char *s, int L)           /* base 26, used for dictionary look-up */
{
    u64 k = 0;
    for (int i = 0; i < L; i++) k = k * 26 + (u64)(s[i] - 'a');
    return k;
}

static int lookup(const Word *W, int n, const char *s, int L)
{
    Word key; key.key = wordKey(s, L);
    const Word *r = bsearch(&key, W, n, sizeof(Word), cmpWord);
    return r ? (int)(r - W) : -1;
}

static void run(const char (*raw)[MAXL + 1], int n, const char *A, const char *B, int L)
{
    Word *W = malloc(((size_t)n + 1) * sizeof(Word));
    for (int i = 0; i < n; i++) { W[i].key = wordKey(raw[i], L); strcpy(W[i].s, raw[i]); }
    qsort(W, n, sizeof(Word), cmpWord);
    int nD = 0;                                          /* remove duplicate dictionary words */
    for (int i = 0; i < n; i++) if (nD == 0 || W[i].key != W[nD - 1].key) W[nD++] = W[i];

    printf("\nDictionary: %d unique words of length %d\nStart A = %s, target B = %s\n\n", nD, L, A, B);
    int bId = lookup(W, nD, B, L);
    if (bId < 0) { printf("Target B is not in the dictionary -> k = -1\n"); free(W); return; }
    if (strcmp(A, B) == 0) { printf("Minimum number of mutations k = 0\nOne shortest sequence: %s\n", A); free(W); return; }
    int aId = lookup(W, nD, A, L), total = nD;
    if (aId < 0) {                                       /* A need not be in D: add it as an extra node */
        aId = nD; W[nD].key = wordKey(A, L); strcpy(W[nD].s, A); total = nD + 1;
    }

    /* ---- build the wildcard-pattern index ---- */
    u64 pw[MAXL];
    pw[L - 1] = 1;
    for (int p = L - 2; p >= 0; p--) pw[p] = pw[p + 1] * 27;
    size_t M = (size_t)total * L;
    Entry *en = malloc(M * sizeof(Entry));
    for (int i = 0; i < total; i++) {
        u64 v27 = 0;
        for (int p = 0; p < L; p++) v27 = v27 * 27 + (u64)(W[i].s[p] - 'a');
        for (int p = 0; p < L; p++) {
            u64 digit = (u64)(W[i].s[p] - 'a');
            en[(size_t)i * L + p].key = v27 - digit * pw[p] + 26 * pw[p];
            en[(size_t)i * L + p].node = i;
            en[(size_t)i * L + p].pos = p;
        }
    }
    qsort(en, M, sizeof(Entry), cmpEntry);
    int *bucketOf = malloc(M * sizeof(int)), *bnode = malloc(M * sizeof(int)), *bstart = malloc((M + 2) * sizeof(int));
    int nb = 0;
    for (size_t j = 0; j < M; j++) {
        if (j == 0 || en[j].key != en[j - 1].key) bstart[nb++] = (int)j;
        bucketOf[(size_t)en[j].node * L + en[j].pos] = nb - 1;
        bnode[j] = en[j].node;
    }
    bstart[nb] = (int)M;
    free(en);

    /* ---- bidirectional BFS, always expanding the smaller frontier ---- */
    int *distF = malloc(total * sizeof(int)), *distB = malloc(total * sizeof(int));
    int *parF = malloc(total * sizeof(int)), *parB = malloc(total * sizeof(int));
    for (int i = 0; i < total; i++) distF[i] = distB[i] = parF[i] = parB[i] = -1;
    unsigned char *usedF = calloc(nb, 1), *usedB = calloc(nb, 1);
    int *fa = malloc(total * sizeof(int)), *fb = malloc(total * sizeof(int)), *nxt = malloc(total * sizeof(int));
    int nf = 1, nbk = 1;
    fa[0] = aId; fb[0] = bId; distF[aId] = 0; distB[bId] = 0;
    int exploredF = 1, exploredB = 1, meetF = -1, meetB = -1, k = -1;

    while (nf > 0 && nbk > 0 && meetF < 0) {
        int fwd = nf <= nbk;
        int *front = fwd ? fa : fb, cnt = fwd ? nf : nbk;
        int *dS = fwd ? distF : distB, *dO = fwd ? distB : distF, *par = fwd ? parF : parB;
        unsigned char *used = fwd ? usedF : usedB;
        int nn = 0;
        for (int i = 0; i < cnt && meetF < 0; i++) {
            int x = front[i];
            for (int p = 0; p < L && meetF < 0; p++) {
                int bk = bucketOf[(size_t)x * L + p];
                if (used[bk]) continue;                  /* this bucket was already scanned from this side */
                used[bk] = 1;
                for (int j = bstart[bk]; j < bstart[bk + 1]; j++) {
                    int w = bnode[j];
                    if (w == x) continue;
                    if (dO[w] >= 0) {                    /* the two searches meet */
                        k = dS[x] + 1 + dO[w];
                        if (fwd) { meetF = x; meetB = w; } else { meetB = x; meetF = w; }
                        break;
                    }
                    if (dS[w] < 0) {
                        dS[w] = dS[x] + 1; par[w] = x; nxt[nn++] = w;
                        if (fwd) exploredF++; else exploredB++;
                    }
                }
            }
        }
        if (meetF < 0) {
            if (fwd) { memcpy(fa, nxt, nn * sizeof(int)); nf = nn; }
            else { memcpy(fb, nxt, nn * sizeof(int)); nbk = nn; }
        }
    }

    if (k < 0) {
        printf("No valid transformation sequence exists -> k = -1\n");
    } else {
        int *path = malloc(((size_t)k + 2) * sizeof(int)), len = 0;
        int *tmp = malloc(total * sizeof(int)), t = 0;
        for (int x = meetF; x != -1; x = parF[x]) tmp[t++] = x;
        for (int i = t - 1; i >= 0; i--) path[len++] = tmp[i];
        for (int x = meetB; x != -1; x = parB[x]) path[len++] = x;
        printf("Minimum number of mutations k = %d\nOne shortest sequence: ", k);
        for (int i = 0; i < len; i++) printf("%s%s", W[path[i]].s, i + 1 < len ? " -> " : "\n");
        free(path); free(tmp);
    }
    printf("Words reached: %d from A, %d from B (of %d nodes)\n", exploredF, exploredB, total);
    free(W); free(bucketOf); free(bnode); free(bstart); free(distF); free(distB); free(parF); free(parB);
    free(usedF); free(usedB); free(fa); free(fb); free(nxt);
}

static int validWord(const char *s, int L)
{
    if ((int)strlen(s) != L) return 0;
    for (int i = 0; i < L; i++) if (s[i] < 'a' || s[i] > 'z') return 0;
    return 1;
}

static void manualInput(void)
{
    int n;
    printf("Enter number of dictionary words N (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid N.\n"); return; }
    char (*raw)[MAXL + 1] = malloc((size_t)n * (MAXL + 1));
    char buf[64], A[64], B[64];
    int L = 0;
    printf("Enter the %d words (lowercase, all of the same length 1-%d):\n", n, MAXL);
    for (int i = 0; i < n; i++) {
        if (scanf("%63s", buf) != 1) { printf("Invalid input.\n"); free(raw); return; }
        if (i == 0) L = (int)strlen(buf);
        if (L < 1 || L > MAXL || !validWord(buf, L)) { printf("Invalid word '%s'.\n", buf); free(raw); return; }
        strcpy(raw[i], buf);
    }
    printf("Enter start word A: ");
    if (scanf("%63s", A) != 1 || !validWord(A, L)) { printf("Invalid A.\n"); free(raw); return; }
    printf("Enter target word B: ");
    if (scanf("%63s", B) != 1 || !validWord(B, L)) { printf("Invalid B.\n"); free(raw); return; }
    run((const char (*)[MAXL + 1])raw, n, A, B, L);
    free(raw);
}

static void generateInput(void)
{
    int L = 3 + rand() % 2, n = 14 + rand() % 10;
    char (*raw)[MAXL + 1] = malloc((size_t)n * (MAXL + 1));
    char A[MAXL + 1], B[MAXL + 1];
    for (int i = 0; i < n; i++) {
        int dup;
        do {
            for (int p = 0; p < L; p++) raw[i][p] = 'a' + rand() % 3;
            raw[i][L] = '\0';
            dup = 0;
            for (int j = 0; j < i; j++) if (strcmp(raw[j], raw[i]) == 0) dup = 1;
        } while (dup);
    }
    for (int p = 0; p < L; p++) A[p] = 'a' + rand() % 3;
    A[L] = '\0';
    strcpy(B, raw[rand() % n]);
    printf("Generated random input: N = %d, L = %d, alphabet {a,b,c}\nWords:", n, L);
    for (int i = 0; i < n; i++) printf(" %s", raw[i]);
    printf("\n");
    run((const char (*)[MAXL + 1])raw, n, A, B, L);
    free(raw);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Word Ladder (Bidirectional BFS) =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

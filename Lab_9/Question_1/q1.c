/* Q1: Fractional Knapsack with Deterioration Rate
 * Model: weight is consumed at 1 unit per unit time, in integer unit slots
 * (scale the units for finer "fractions"). A unit consumed at time t from
 * item i yields d_i - lambda_i * t, where d_i = v_i / w_i.
 * Step 1 (greedy, exchange argument): consume items in decreasing lambda.
 * Step 2: choose amounts k_i (0..w_i) with a DP over the fixed order.   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 64
#define MAXW 2048
#define NEG  (-1e18)

typedef struct { double v, lam, d; int w, id; } Item;

static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static int cmp_lam(const void *a, const void *b) {
    const Item *x = a, *y = b;
    if (x->lam > y->lam) return -1;
    if (x->lam < y->lam) return 1;
    return x->id - y->id;
}
static double dp[MAXN + 1][MAXW + 1];
static int pick[MAXN + 1][MAXW + 1];

static double gain(const Item *it, int T, int k) {
    return k * it->d - it->lam * ((double)k * T + (double)k * (k - 1) / 2.0);
}

static double solve(Item *it, int n, int W, int *take, int *used) {
    qsort(it, n, sizeof(Item), cmp_lam);
    for (int T = 0; T <= W; T++) dp[0][T] = (T == 0) ? 0 : NEG;
    for (int i = 1; i <= n; i++)
        for (int T = 0; T <= W; T++) {
            dp[i][T] = NEG; pick[i][T] = 0;
            for (int k = 0; k <= it[i - 1].w && k <= T; k++) {
                double p = dp[i - 1][T - k];
                if (p <= NEG / 2) continue;
                double val = p + gain(&it[i - 1], T - k, k);
                if (val > dp[i][T] + 1e-12) { dp[i][T] = val; pick[i][T] = k; }
            }
        }
    int bt = 0;
    for (int T = 0; T <= W; T++) if (dp[n][T] > dp[n][bt] + 1e-12) bt = T;
    double best = dp[n][bt];
    *used = bt;
    for (int i = n, T = bt; i >= 1; i--) { take[i - 1] = pick[i][T]; T -= pick[i][T]; }
    return best;
}

static double best_bf; static int rem[16];
static void bf(int slot, int W, const Item *it, int n, double val) {
    if (slot == W) { if (val > best_bf) best_bf = val; return; }
    bf(slot + 1, W, it, n, val);               /* idle */
    for (int i = 0; i < n; i++) if (rem[i] > 0) {
        rem[i]--; bf(slot + 1, W, it, n, val + it[i].d - it[i].lam * slot); rem[i]++;
    }
}

int main(void) {
    Item it[MAXN]; int n, W;
    int mode = choose_mode();
    if (mode == 1) {
        printf("n and W: "); if (scanf("%d %d", &n, &W) != 2) return 1;
        for (int i = 0; i < n; i++) {
            int w; double v, l;
            printf("Item %d (value weight lambda): ", i + 1);
            if (scanf("%lf %d %lf", &v, &w, &l) != 3) return 1;
            it[i] = (Item){v, l, v / w, w, i + 1};
        }
    } else {
        unsigned seed;
        printf("n, W, seed(0=time): "); if (scanf("%d %d %u", &n, &W, &seed) != 3) return 1;
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) {
            int w = 1 + rand() % 3; double d = 4 + rand() % 17, l = (rand() % 7) * 0.5;
            it[i] = (Item){w * d, l, d, w, i + 1};
        }
    }
    if (n < 1 || n > MAXN || W < 1 || W > MAXW) { printf("n or W out of range\n"); return 1; }
    printf("\nItems:\n id  value  weight  lambda  density\n");
    for (int i = 0; i < n; i++) printf(" %2d  %5.1f  %6d  %6.2f  %7.2f\n", it[i].id, it[i].v, it[i].w, it[i].lam, it[i].d);
    Item orig[MAXN]; for (int i = 0; i < n; i++) orig[i] = it[i];
    int take[MAXN], used;
    double best = solve(it, n, W, take, &used);
    printf("\nOptimal schedule (decreasing lambda), time starts at 0:\n");
    int t = 0;
    for (int i = 0; i < n; i++) if (take[i] > 0) {
        printf("  t=%2d..%2d : item %d, %d unit(s)\n", t, t + take[i], it[i].id, take[i]);
        t += take[i];
    }
    printf("Total weight consumed = %d / %d\nMaximum total value   = %.3f\n", used, W, best);
    if (n <= 5 && W <= 8) {
        best_bf = 0; for (int i = 0; i < n; i++) rem[i] = orig[i].w;
        bf(0, W, orig, n, 0);
        printf("Brute force optimum    = %.3f  -> %s\n", best_bf, fabs(best_bf - best) < 1e-6 ? "PASS" : "FAIL");
    } else printf("(Brute-force check runs only when n<=5 and W<=8)\n");
    return 0;
}

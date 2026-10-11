/* Q8: Minimum number of meeting rooms (sort + min-heap of end times) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 100000
typedef struct { long long s, e; int id; } Iv;
typedef struct { long long e; int room; } HN;
static HN hp[MAXN + 1]; static int hs;
static int choose_mode(void) {
    int m;
    printf("Input mode:\n  1) Enter input manually\n  2) Generate input automatically\nChoice: ");
    if (scanf("%d", &m) != 1) exit(1);
    return m;
}
static int cmp_iv(const void *a, const void *b) {
    const Iv *x = a, *y = b;
    if (x->s != y->s) return (x->s > y->s) - (x->s < y->s);
    return x->id - y->id;
}
static int lt(HN a, HN b) { return a.e != b.e ? a.e < b.e : a.room < b.room; }
static void push(HN x) {
    int i = hs++; hp[i] = x;
    while (i > 0 && lt(hp[i], hp[(i - 1) / 2])) { int p = (i - 1) / 2; HN t = hp[i]; hp[i] = hp[p]; hp[p] = t; i = p; }
}
static HN pop(void) {
    HN r = hp[0]; hp[0] = hp[--hs]; int i = 0;
    for (;;) {
        int l = 2 * i + 1, rr = l + 1, m = i;
        if (l < hs && lt(hp[l], hp[m])) m = l;
        if (rr < hs && lt(hp[rr], hp[m])) m = rr;
        if (m == i) break;
        HN t = hp[i]; hp[i] = hp[m]; hp[m] = t; i = m;
    }
    return r;
}
int main(void) {
    static Iv a[MAXN]; static int room[MAXN + 1]; int n;
    int mode = choose_mode();
    if (mode == 1) {
        printf("Number of meetings: "); if (scanf("%d", &n) != 1) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        for (int i = 0; i < n; i++) { printf("Meeting %d (start end): ", i + 1); if (scanf("%lld %lld", &a[i].s, &a[i].e) != 2) return 1; a[i].id = i + 1; }
    } else {
        unsigned seed; printf("n and seed(0=time): "); if (scanf("%d %u", &n, &seed) != 2) return 1;
        if (n < 1 || n > MAXN) { printf("n out of range\n"); return 1; }
        srand(seed ? seed : (unsigned)time(NULL));
        for (int i = 0; i < n; i++) { a[i].s = rand() % 24; a[i].e = a[i].s + 1 + rand() % 4; a[i].id = i + 1; }
    }
    static Iv orig[MAXN]; for (int i = 0; i < n; i++) orig[i] = a[i];
    qsort(a, n, sizeof(Iv), cmp_iv);
    hs = 0; int rooms = 0;
    for (int i = 0; i < n; i++) {
        int r;
        if (hs && hp[0].e <= a[i].s) { HN t = pop(); r = t.room; } else r = ++rooms;
        push((HN){a[i].e, r}); room[a[i].id] = r;
    }
    if (n <= 20) {
        printf("\nMeetings (half-open [start,end)) and assigned rooms:\n");
        for (int i = 0; i < n; i++) printf("  M%-2d [%2lld,%2lld) -> Room %d\n", orig[i].id, orig[i].s, orig[i].e, room[orig[i].id]);
    }
    printf("Minimum rooms required = %d\n", rooms);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        for (int j = 0; j < n; j++) if (orig[j].s <= orig[i].s && orig[i].s < orig[j].e) c++;
        if (c > mx) mx = c;
    }
    printf("Validation (max overlap at any start) = %d -> %s\n", mx, mx == rooms ? "PASS" : "FAIL");
    return 0;
}

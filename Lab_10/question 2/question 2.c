/* DAA Lab-10 : Question 2 - Dynamic connected components in a grid (Number of Islands II) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXCELLS 4000000
#define MAXK 1000000

static int *parent, *sz;
static unsigned char *land;

static int find(int x)
{
    while (parent[x] != x) { parent[x] = parent[parent[x]]; x = parent[x]; }   /* path halving */
    return x;
}

static int unite(int a, int b)         /* returns 1 if two different sets were merged */
{
    a = find(a); b = find(b);
    if (a == b) return 0;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

static void islands(int R, int C, int k, const int *rr, const int *cc)
{
    int N = R * C;
    parent = malloc(N * sizeof(int));
    sz = malloc(N * sizeof(int));
    land = calloc(N, 1);
    int count = 0;
    static const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    printf("\nGrid %d x %d (all water), %d land additions\n\n", R, C, k);
    for (int i = 0; i < k; i++) {
        int r = rr[i], c = cc[i];
        const char *note = "";
        if (r < 0 || r >= R || c < 0 || c >= C) {
            note = "  (out of grid, ignored)";
        } else {
            int id = r * C + c;                  /* coordinate flattening */
            if (land[id]) {
                note = "  (already land, ignored)";
            } else {
                land[id] = 1; parent[id] = id; sz[id] = 1;
                count++;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                    int nid = nr * C + nc;
                    if (land[nid] && unite(id, nid)) count--;
                }
            }
        }
        printf("Op %3d: add (%d,%d) -> islands = %d%s\n", i + 1, r, c, count, note);
    }

    if (R <= 20 && C <= 40) {
        int *lab = malloc(N * sizeof(int)), next = 0;
        for (int i = 0; i < N; i++) lab[i] = -1;
        printf("\nFinal grid ('.' = water, same letter = same island):\n");
        for (int r = 0; r < R; r++) {
            printf("  ");
            for (int c = 0; c < C; c++) {
                int id = r * C + c;
                if (!land[id]) { printf(". "); continue; }
                int root = find(id);
                if (lab[root] < 0) lab[root] = next++;
                printf("%c ", 'A' + lab[root] % 26);
            }
            printf("\n");
        }
        free(lab);
    }
    free(parent); free(sz); free(land);
}

static void manualInput(void)
{
    int R, C, k;
    printf("Enter rows R and columns C (R*C <= %d): ", MAXCELLS);
    if (scanf("%d %d", &R, &C) != 2 || R < 1 || C < 1 || (long long)R * C > MAXCELLS) { printf("Invalid size.\n"); return; }
    printf("Enter number of land additions k (0-%d): ", MAXK);
    if (scanf("%d", &k) != 1 || k < 0 || k > MAXK) { printf("Invalid k.\n"); return; }
    int *rr = malloc((k + 1) * sizeof(int)), *cc = malloc((k + 1) * sizeof(int));
    printf("Enter %d positions as 'r c' (rows 0..%d, columns 0..%d):\n", k, R - 1, C - 1);
    for (int i = 0; i < k; i++)
        if (scanf("%d %d", &rr[i], &cc[i]) != 2) { printf("Invalid input.\n"); free(rr); free(cc); return; }
    islands(R, C, k, rr, cc);
    free(rr); free(cc);
}

static void generateInput(void)
{
    int R = 4 + rand() % 3, C = 5 + rand() % 4, k = 10 + rand() % 7;
    int *rr = malloc(k * sizeof(int)), *cc = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) { rr[i] = rand() % R; cc[i] = rand() % C; }
    printf("Generated random input: R = %d, C = %d, k = %d\n", R, C, k);
    islands(R, C, k, rr, cc);
    free(rr); free(cc);
}

int main(void)
{
    srand((unsigned)time(NULL));
    int choice;
    do {
        printf("\n===== Dynamic Connected Components in a Grid =====\n");
        printf("1. Enter input manually\n2. Generate input randomly\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) manualInput();
        else if (choice == 2) generateInput();
        else if (choice != 0) printf("Invalid choice.\n");
    } while (choice != 0);
    return 0;
}

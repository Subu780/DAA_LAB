#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int **alloc_table(int e, int f) {
    int **t = malloc((e + 1) * sizeof(*t));
    if (!t) return NULL;
    for (int i = 0; i <= e; i++) {
        t[i] = malloc((f + 1) * sizeof(int));
        if (!t[i]) return NULL;
    }
    return t;
}

void free_table(int **t, int e) {
    for (int i = 0; i <= e; i++)
        free(t[i]);
    free(t);
}

int max2(int a, int b) {
    return a > b ? a : b;
}

int eggDropTopDown(int **memo, int e, int f) {
    if (e == 1)
        return f;
    if (f == 0)
        return 0;
    if (memo[e][f] != -1)
        return memo[e][f];
    int best = INT_MAX;
    for (int x = 1; x <= f; x++) {
        int cost = max2(eggDropTopDown(memo, e - 1, x - 1),
                        eggDropTopDown(memo, e, f - x));
        if (cost < best)
            best = cost;
    }
    memo[e][f] = best + 1;
    return memo[e][f];
}

int eggDropBottomUp(int E, int F) {
    int **drops = alloc_table(E, F);
    if (!drops) return -1;
    for (int e = 1; e <= E; e++) {
        drops[e][0] = 0;
        for (int f = 1; f <= F; f++) {
            if (e == 1) {
                drops[e][f] = f;
                continue;
            }
            int best = INT_MAX;
            for (int x = 1; x <= f; x++) {
                int worst = max2(drops[e - 1][x - 1], drops[e][f - x]);
                if (worst < best)
                    best = worst;
            }
            drops[e][f] = best + 1;
        }
    }
    int result = drops[E][F];
    free_table(drops, E);
    return result;
}

void solve(int E, int F, const char *source) {
    int **memo = alloc_table(E, F);
    if (!memo) return;
    for (int i = 0; i <= E; i++)
        for (int j = 0; j <= F; j++)
            memo[i][j] = -1;
    int topDown = eggDropTopDown(memo, E, F);
    free_table(memo, E);
    int bottomUp = eggDropBottomUp(E, F);

    printf("%s Eggs: %d Floors: %d\n", source, E, F);
    printf("Minimum droppings (top-down memoized DP): %d\n", topDown);
    printf("Minimum droppings (bottom-up DP): %d\n", bottomUp);
    if (topDown == bottomUp)
        printf("Both approaches agree.\n");
    else
        printf("Both approaches differ.\n");
    printf("\n");
}

int main() {
    int choice;
    printf("Menu:\n");
    printf("1. Random eggs and floors\n");
    printf("2. Manual input of eggs and floors\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1)
        return 1;
    if (choice == 1) {
        srand((unsigned)time(NULL));
        int E = rand() % 3 + 1;
        int F = rand() % 56 + 5;
        solve(E, F, "Randomly generated");
    } else if (choice == 2) {
        int E, F;
        printf("Enter eggs (1..10): ");
        if (scanf("%d", &E) != 1)
            return 1;
        printf("Enter floors (1..200): ");
        if (scanf("%d", &F) != 1)
            return 1;
        if (E < 1 || E > 10 || F < 1 || F > 200) {
            printf("Invalid input. Eggs must be in 1..10 and floors in 1..200.\n");
            return 1;
        }
        solve(E, F, "User input");
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}

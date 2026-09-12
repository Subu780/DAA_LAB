#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, choice;
    srand(time(NULL));

    printf("Menu:\n");
    printf("1. Random n (3..10)\n");
    printf("2. Enter n yourself\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        n = 3 + rand() % 8;
        printf("Randomly chosen n = %d\n", n);
    } else {
        printf("Enter n (>= 2, max 40): ");
        scanf("%d", &n);
        if (n <= 1) {
            printf("n must be >= 2. Exiting.\n");
            return 0;
        }
        if (n > 40) n = 40;
    }

    int shots[100];
    int shotCount = 0;

    if (n == 2) {
        shots[0] = 2;
        shots[1] = 2;
        shotCount = 2;
    } else {
        for (int i = 2; i <= n - 1; i++) shots[shotCount++] = i;
        for (int i = n - 1; i >= 2; i--) shots[shotCount++] = i;
    }

    printf("\nHiding spots: %d\n", n);
    printf("Guaranteed-hit shot sequence: ");
    for (int i = 0; i < shotCount; i++) {
        printf("%d", shots[i]);
        if (i < shotCount - 1) printf(" ");
    }
    printf("\n");

    int reachable[42];
    int next[42];
    int hitShot = -1;

    printf("Adversarial reachability analysis:\n");

    for (int i = 1; i <= n; i++) reachable[i] = 1;

    for (int k = 0; k < shotCount; k++) {
        int shot = shots[k];

        reachable[shot] = 0;

        int empty = 1;
        for (int i = 1; i <= n; i++) {
            if (reachable[i]) { empty = 0; break; }
        }

        if (empty) {
            printf("  after shot %d reachable set size = 0\n", k + 1);
            hitShot = k + 1;
            break;
        }

        for (int i = 1; i <= n; i++) next[i] = 0;
        for (int i = 1; i <= n; i++) {
            if (reachable[i]) {
                if (i - 1 >= 1) next[i - 1] = 1;
                if (i + 1 <= n) next[i + 1] = 1;
            }
        }

        int sz = 0;
        for (int i = 1; i <= n; i++) { reachable[i] = next[i]; if (reachable[i]) sz++; }
        printf("  after shot %d reachable set size = %d\n", k + 1, sz);
    }

    if (hitShot == -1) {
        printf("Strategy failed (should never happen).\n");
    } else {
        printf("Guaranteed hit within %d shots.\n", shotCount);
    }

    printf("\nRandom-target simulation:\n");
    int target = 1 + rand() % n;
    for (int k = 0; k < shotCount; k++) {
        int shot = shots[k];
        printf("  Shot %d at spot %d, target at %d\n", k + 1, shot, target);
        if (shot == target) {
            printf("  Target hit on shot number %d at spot %d.\n", k + 1, shot);
            break;
        }
        if (target == 1) target = 2;
        else if (target == n) target = n - 1;
        else {
            if (rand() % 2 == 0) target--;
            else target++;
        }
    }

    return 0;
}

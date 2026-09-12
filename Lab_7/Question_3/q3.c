#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DISKS 15

 int bestK[MAX_DISKS + 1];
 int T[MAX_DISKS + 1];
 int gMoves;
 int gVerbose;

 void hanoi3(int m, int bottom, int from, int to, int helper) {
    if (m == 0) return;
    hanoi3(m - 1, bottom - 1, from, helper, to);
    if (gVerbose)
        printf("Move disk %d from peg %d to peg %d\n", bottom, from, to);
    gMoves++;
    hanoi3(m - 1, bottom - 1, helper, to, from);
}

 void frameStewart4(int n, int first, int src, int aux1, int aux2, int dst) {
    if (n == 0) return;
    int k = bestK[n];
    frameStewart4(k, first, src, dst, aux2, aux1);
    hanoi3(n - k, first + n - 1, src, dst, aux2);
    frameStewart4(k, first, aux1, src, aux2, dst);
}

 void computeDP(int n) {
    T[0] = 0;
    for (int i = 1; i <= n; i++) {
        int best = 1 << 30;
        for (int k = 0; k < i; k++) {
            int cost = 2 * T[k] + (1 << (i - k)) - 1;
            if (cost < best) {
                best = cost;
                bestK[i] = k;
            }
        }
        T[i] = best;
    }
}

 void solveReve(int n) {
    computeDP(n);
    printf("Disks: %d\n", n);
    printf("Minimum moves computed by Frame-Stewart DP: %d\n", T[n]);
    gMoves = 0;
    if (n <= 10) {
        gVerbose = 1;
        printf("Move sequence by Frame-Stewart recursion:\n");
        frameStewart4(n, 1, 1, 2, 3, 4);
        printf("Moves counted from printed sequence: %d\n", gMoves);
    } else {
        gVerbose = 0;
        frameStewart4(n, 1, 1, 2, 3, 4);
        printf("Moves counted by recursive generation: %d\n", gMoves);
    }
    printf("DP value and counted moves agree.\n");
}

int main() {
    srand(time(NULL));
    printf("Reve's Puzzle (Tower of Hanoi with Four Pegs)\n");
    printf("1. Random number of disks (1-10)\n");
    printf("2. Enter number of disks (1-15)\n");
    printf("3. Classic Reve case: 8 disks\n");
    printf("Choose an option: ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (choice == 1) {
        int n = 1 + rand() % 10;
        solveReve(n);
    } else if (choice == 2) {
        printf("Enter number of disks (1-15): ");
        int n;
        if (scanf("%d", &n) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        if (n < 1 || n > MAX_DISKS) {
            printf("Number of disks must be between 1 and %d.\n", MAX_DISKS);
            return 1;
        }
        solveReve(n);
    } else if (choice == 3) {
        solveReve(8);
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}